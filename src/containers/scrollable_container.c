#include "containers/scrollable_container.h"

SDL_bool __scontainer_vt_was_init = SDL_FALSE;

void __scontainer_vt_init(ScrollableContainer *container){
	if(!__scontainer_vt_was_init){
		__gscontainer_widget_vt = __gcontainer_widget_vt;
		__gscontainer_widget_vt.free = __scrollable_container_free;
		__gscontainer_widget_vt.set_bounds = __scrollable_container_set_bounds;
		__gscontainer_widget_vt.process_events = __scrollable_container_process_events;
		__gscontainer_widget_vt.draw = __scrollable_container_draw;
		__gscontainer_container_vt.add_widget = __scrollable_container_add_widget;
		__gscontainer_container_vt.remove_widget = __scrollable_container_remove_widget;

		__scontainer_vt_was_init = SDL_TRUE;
	}
	
	container->container.widget.functions = &__gscontainer_widget_vt;
	container->container.functions = &__gscontainer_container_vt;
}

ScrollableContainer new_ScrollableContainer(){
	return new_ScrollableContainer_max_widgets(CONTAINER_MAX_WIDGETS);
}

ScrollableContainer new_ScrollableContainer_max_widgets(int max){
	ScrollableContainer scrollable_container;

	scrollable_container.container = new_Container_max_widgets(max);
	__scontainer_vt_init(&scrollable_container);

	scrollable_container.camera = new_Camera(container_get_bounds_origin(&scrollable_container));

	return scrollable_container;
}

void __scrollable_container_free(void *__container){
	__container_free(__container);

	ScrollableContainer *scrollable_container = __container;
	free_Camera(scrollable_container->camera);
}

void __scrollable_container_set_bounds(void *__container, SDL_Rect bounds){
	__container_set_bounds(__container, bounds);

	ScrollableContainer *scrollable_container = __container;
	
	//TO-DO: check to see if this really do what it's intended to do.
	camera_set_bounds(scrollable_container->camera, container_get_bounds_origin(scrollable_container));
}

void __scrollable_container_process_events(void *__container, SDL_Event event, Mouse mouse){
	ScrollableContainer *scrollable_container = __container;
	
	Camera *c = scrollable_container->camera;
	camera_process_events(scrollable_container->camera, event);
	camera_move(scrollable_container->camera);

	__container_process_events(__container, event, mouse);
}

void __scrollable_container_draw(void *__container, SDL_Renderer *renderer, Camera *camera){
	ScrollableContainer *scrollable_container = __container;

	int i;
	for(i = 0; i < scrollable_container->container.widget_list->size; i++){
		void *widget = list_get_index(scrollable_container->container.widget_list, i);
		widget_update_camera_position(widget, scrollable_container->camera);
		widget_draw(widget, renderer, scrollable_container->camera);
	}
}

void __scrollable_container_add_widget(void *__container, void *widget){
	__container_add_widget(__container, widget);
	
	ScrollableContainer *container = __container;
	
	//Checking to see if the widget is 'out of bounds' in order to update its
	//camera limits.
	camera_update_limit(container->camera, widget_get_bounds_origin(widget));
}

void *__scrollable_container_remove_widget(void *__container){
	ScrollableContainer *container = __container;
	//return list_remove_last(container->widget_list);
}
