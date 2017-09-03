#include "containers/container.h"

VT_Widget __gcontainer_widget_vt = {
    generic_container_free,
    generic_container_set_bounds,
    generic_container_process_events,
    generic_container_draw
};

VT_Container __gcontainer_vt = {
    generic_container_add_widget,
    generic_container_remove_widget
};

Container new_Container(){
    return new_Container_max_widgets(CONTAINER_MAX_WIDGETS);
}

Container new_Container_max_widgets(int max){
    Container container;
    
    container.widget = new_Widget();
    container.widget_list = new_ArrayList_max_size(max);
    
    container.widget.functions = &__gcontainer_widget_vt;
    container.functions = &__gcontainer_vt;
    
    return container;
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
    ((Container *)container)->functions->add_widget(container, widget);
}

void *container_remove_widget(void *container){
    return ((Container *)container)->functions->remove_widget(container);
}

void container_empty(void *container){
    Container *container_ = container;
    free_ArrayList(container_->widget_list, widget_free);
    container_->widget_list = new_ArrayList();
}


void generic_container_free(void *raw_container){
    generic_widget_free(raw_container);
    
    Container *container = raw_container;
    
    free_ArrayList(container->widget_list, widget_free);
    container->widget_list = NULL;
    container->functions->add_widget = NULL;
    container->functions->remove_widget = NULL;
}

void generic_container_set_bounds(void *raw_container, SDL_Rect bounds){
    Container *container = raw_container;
    
    SDL_Rect container_bounds_old = container_get_bounds_origin(container);
    set_bounds_from_SDL_Rect(&container->widget.bounds, bounds);
    SDL_Rect container_bounds_new = container_get_bounds_origin(container);
    
    Position container_offset;
    container_offset = new_Position(
        container_bounds_new.x - container_bounds_old.x,
        container_bounds_new.y - container_bounds_old.y
    );
    
    int i;
    for(i=0; i<container->widget_list->size; i++){
        void *widget = list_get_index(container->widget_list, i);
        
        SDL_Rect widget_bounds = widget_get_bounds_origin(widget);
        widget_bounds.x += container_offset.x;
        widget_bounds.y += container_offset.y;
        
        widget_set_bounds(widget, widget_bounds);
    }
}

void generic_container_process_events(void *raw_container, SDL_Event event, Mouse mouse){
    Container *container = raw_container;
    
    generic_widget_process_events(container, event, mouse);
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
	
    SDL_Rect container_bounds = container_get_bounds_origin(raw_container);
	SDL_Rect widget_bounds = widget_get_bounds_origin(widget);
	widget_bounds.x += container_bounds.x;
	widget_bounds.y += container_bounds.y;
	widget_set_bounds(widget, widget_bounds);
	
	list_insert_last(container->widget_list, widget);
}

void* generic_container_remove_widget(void *raw_container){
    Container *container = raw_container;
    return list_remove_last(container->widget_list);
}
