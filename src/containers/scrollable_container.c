#include "containers/scrollable_container.h"

SDL_bool __scontainer_vt_was_init = SDL_FALSE;

void __scontainer_vt_init(){
	if(__scontainer_vt_was_init){
		return;
	}
	
	__gscontainer_widget_vt = __gcontainer_widget_vt;
	__gscontainer_widget_vt.free = __scrollable_container_free;
	__gscontainer_widget_vt.set_bounds = __scrollable_container_set_bounds;
	__gscontainer_widget_vt.process_events = __scrollable_container_process_events;
	__gscontainer_widget_vt.draw = __scrollable_container_draw;
	
	__scontainer_vt_was_init = SDL_TRUE;
}

ScrollableContainer new_ScrollableContainer(){
	return new_ScrollableContainer_max_widgets(CONTAINER_MAX_WIDGETS);
}

ScrollableContainer new_ScrollableContainer_max_widgets(int max){
	ScrollableContainer scrollable_container;

	scrollable_container.container = new_Container_max_widgets(max);
	
	__scontainer_vt_init();
	scrollable_container.container.widget.functions = &__gscontainer_widget_vt;

	scrollable_container.camera = new_Camera(container_get_bounds_origin(&scrollable_container));

	return scrollable_container;
}

void __scrollable_container_free(void *__container){
	__container_free(__container);

	ScrollableContainer *scrollable_container = __container;
	free_Camera(scrollable_container->camera);
	scrollable_container->camera = NULL;
}

void __scrollable_container_set_bounds(void *__container, SDL_Rect bounds){
	__container_set_bounds(__container, bounds);

	ScrollableContainer *scrollable_container = __container;
	camera_set_bounds(scrollable_container->camera, container_get_bounds_origin(scrollable_container));
}

void __scrollable_container_process_events(void *__container, SDL_Event event, Mouse mouse){
	ScrollableContainer *scrollable_container = __container;
	camera_process_events(scrollable_container->camera, event);

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
