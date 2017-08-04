#include "containers/container.h"

Container new_Container(){
    return new_Container_max_widgets(CONTAINER_MAX_WIDGETS);
}

Container new_Container_max_widgets(int max){
    Container container;
    
    container.widget = new_Widget();
    container.widget_list = new_ArrayList_max_size(max);
    
    container.widget.init = generic_container_init;
    container.widget.free = generic_container_free;
    container.widget.set_bounds = generic_container_set_bounds;
    container.widget.process_events = generic_container_process_events;
    container.widget.draw = generic_container_draw;
    container.add_widget = generic_container_add_widget;
    container.remove_widget = generic_container_remove_widget;
    
    return container;
}

void container_init(void *container, SDL_Renderer *renderer){
    widget_init(container, renderer);
}

void container_free(void *container){
    widget_free(container);
}

SDL_Rect container_get_bounds_origin(void *container){
    return widget_get_bounds_origin(container);
}

SDL_Rect container_get_bounds_camera(void *container){
    return widget_get_bounds_camera(container);
}

void container_set_bounds(void *container, SDL_Rect bounds){
    widget_set_bounds(container, bounds);
}

void container_process_events(void *container, SDL_Event event, Mouse mouse){
    widget_process_events(container, event, mouse);
}

void container_draw(void *container, SDL_Renderer *renderer, Camera *camera){
    widget_draw(container, renderer, camera);
}

void container_add_widget(void *container, void *widget){
    ((Container *)container)->add_widget(container, widget);
}

void *container_remove_widget(void *container){
    return ((Container *)container)->remove_widget(container);
}

void container_empty(void *container){
    Container *container_ = container;
    free_ArrayList(container_->widget_list, widget_free);
    container_->widget_list = new_ArrayList();
}


void generic_container_init(void *raw_container, SDL_Renderer *renderer){
    Container *container = raw_container;
    
    int i;
    for(i=0; i<container->widget_list->size; i++){
        widget_init(list_get_index(container->widget_list, i), renderer);
    }
}

void generic_container_free(void *raw_container){
    Container *container = raw_container;
    
    int i;
    for(i=0; i<container->widget_list->size; i++){
        widget_free(list_get_index(container->widget_list, i));
    }
}

void generic_container_set_bounds(void *raw_container, SDL_Rect bounds){
    Container *container = raw_container;
    
    int i;
    for(i=0; i<container->widget_list->size; i++){
        widget_set_bounds(list_get_index(container->widget_list, i), bounds);
    }
}

void generic_container_process_events(void *raw_container, SDL_Event event, Mouse mouse){
    Container *container = raw_container;
    
    int i;
    for(i=0; i<container->widget_list->size; i++){
        widget_process_events(list_get_index(container->widget_list, i), event, mouse);
    }
}

void generic_container_draw(void *raw_container, SDL_Renderer *renderer, Camera *camera){
    Container *container = raw_container;
    
    int i;
    for(i=0; i<container->widget_list->size; i++){
        widget_draw(list_get_index(container->widget_list, i), renderer, camera);
    }
}

void generic_container_add_widget(void *raw_container, void *widget){
    Container *container = raw_container;
    list_insert_last(container->widget_list, widget);
}

void* generic_container_remove_widget(void *raw_container){
    Container *container = raw_container;
    return list_remove_last(container->widget_list);
}
