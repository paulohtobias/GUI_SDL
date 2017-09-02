#include "containers/scrollable_container.h"

VT_Widget __gscontainer_widget_vt = {
	generic_scrollable_container_free,
	generic_scrollable_container_set_bounds,
	generic_scrollable_container_process_events,
	generic_scrollable_container_draw
};

ScrollableContainer new_ScrollableContainer(){
    return new_ScrollableContainer_max_widgets(CONTAINER_MAX_WIDGETS);
}

ScrollableContainer new_ScrollableContainer_max_widgets(int max){
    ScrollableContainer scrollable_container;
    
    scrollable_container.container = new_Container_max_widgets(max);
    scrollable_container.container.widget.functions = &__gscontainer_widget_vt;
    
    scrollable_container.camera = new_Camera(container_get_bounds_origin(&scrollable_container));
    
    return scrollable_container;
}

void generic_scrollable_container_free(void *raw_container){
    generic_container_free(raw_container);
    
    ScrollableContainer *scrollable_container = raw_container;
    free_Camera(scrollable_container->camera);
    scrollable_container->camera = NULL;
}

void generic_scrollable_container_set_bounds(void *raw_container, SDL_Rect bounds){
    generic_container_set_bounds(raw_container, bounds);
    
    ScrollableContainer *scrollable_container = raw_container;
    camera_set_bounds(scrollable_container->camera, container_get_bounds_origin(scrollable_container));
}

void generic_scrollable_container_process_events(void *raw_container, SDL_Event event, Mouse mouse){
    ScrollableContainer *scrollable_container = raw_container;
    camera_process_events(scrollable_container->camera, event);
    
    generic_container_process_events(raw_container, event, mouse);
}

void generic_scrollable_container_draw(void *raw_container, SDL_Renderer *renderer, Camera *camera){
	ScrollableContainer *scrollable_container = raw_container;
    
    int i;
    for(i=0; i<scrollable_container->container.widget_list->size; i++){
		void *widget = list_get_index(scrollable_container->container.widget_list, i);
		widget_update_camera_position(widget, scrollable_container->camera);
        widget_draw(widget, renderer, scrollable_container->camera);
    }
}
