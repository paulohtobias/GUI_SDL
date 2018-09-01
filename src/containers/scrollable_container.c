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

	scrollable_container.camera = new_Camera(container_get_bounds_local(&scrollable_container));

	return scrollable_container;
}

void __scrollable_container_free(void *__container){
	__container_free(__container);
	
	//TO-DO: free the scrollbar
}

void __scrollable_container_set_bounds(void *__container, SDL_Rect bounds){
	ScrollableContainer *container = __container;
	
	__container_set_bounds(__container, bounds);
	
	container->camera.limit = container_get_bounds_global(container);
	container->camera.bounds = container->camera.limit;
}

void __scrollable_container_process_events(void *__container, SDL_Event event, Mouse mouse){
	ScrollableContainer *container = __container;
	
	camera_process_events(&container->camera, event);
	camera_move(&container->camera);

	__container_process_events(__container, event, mouse);
}

void __scrollable_container_draw(void *__container, RenderData *data){
	ScrollableContainer *container = __container;

	int i;
	RenderData new_data = *data;
	new_data.camera = &container->camera;
	for(i = 0; i < container->container.widget_list->size; i++){
		void *widget = list_get_index(container->container.widget_list, i);
		widget_draw(widget, &new_data);
	}
}

void __scrollable_container_add_widget(void *__container, void *__widget){
	ScrollableContainer *container = __container;
	Widget *widget = __widget;
	
	//Adds the widget to the list.
	__container_add_widget(__container, __widget);
	
	//Checking to see if the widget is 'out of bounds' in order to update its
	//camera limits.
	camera_update_limit(&container->camera, widget_get_bounds_global(widget));
}

void *__scrollable_container_remove_widget(void *__container){
	ScrollableContainer *container = __container;
	//return list_remove_last(container->widget_list);
}
