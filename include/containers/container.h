#ifndef CONTAINER_H
#define CONTAINER_H

#include "widgets/widget.h"
#include "utils/array_list.h"

typedef struct Container{
    Widget widget;
    
    ArrayList *widget_list;
    
    void (*add_widget)(void *, void *);
    void *(*remove_widget)(void *);
}Container;

Container new_Container();

void container_init(void *container, SDL_Renderer *renderer);

void container_free(void *raw_container);

void container_set_bounds(void *raw_container, SDL_Rect bounds);

void container_process_events(void *raw_container, SDL_Event event, Mouse mouse);

void container_draw(void *raw_container, SDL_Renderer *renderer, Camera *camera);

void container_add_widget(void *raw_container, void *widget);

void *container_remove_widget(void *raw_container);

void container_empty(void *container);


void generic_container_init(void *raw_container, SDL_Renderer *renderer);

void generic_container_free(void *raw_container);

void generic_container_set_bounds(void *raw_container, SDL_Rect bounds);

void generic_container_process_events(void *raw_container, SDL_Event event, Mouse mouse);

void generic_container_draw(void *raw_container, SDL_Renderer *renderer, Camera *camera);

void generic_container_add_widget(void *raw_container, void *widget);

void *generic_container_remove_widget(void *raw_container);

#endif //CONTAINER_H
