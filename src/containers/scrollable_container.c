#include "containers/scrollable_container.h"

ScrollableContainer new_ScrollableContainer(){
    return new_ScrollableContainer_max_widgets(CONTAINER_MAX_WIDGETS);
}

ScrollableContainer new_ScrollableContainer_max_widgets(int max){
    ScrollableContainer scrollable_container;
    
    scrollable_container.container = new_Container_max_widgets(max);
    scrollable_container.container.widget.free = generic_scrollable_container_free;
    scrollable_container.container.widget.set_bounds = generic_scrollable_container_set_bounds;
    scrollable_container.container.widget.process_events = generic_scrollable_container_process_events;
    scrollable_container.container.widget.draw = generic_scrollable_container_draw;
    
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
    generic_scrollable_container_draw(raw_container, renderer, ((ScrollableContainer *)raw_container)->camera);
}
