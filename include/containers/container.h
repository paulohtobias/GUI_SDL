#ifndef CONTAINER_H
#define CONTAINER_H

#include "widgets/widget.h"
#include "utils/array_list.h"

#define CONTAINER_MAX_WIDGETS LIST_DEFAULT_MAX_SIZE

typedef struct VT_Container{
	void (*add_widget)(void *, void *);
	void *(*remove_widget)(void *);
} VT_Container;

typedef struct Container{
	Widget widget;

	ArrayList *widget_list;

	VT_Container *functions;
} Container;

Container new_Container();

Container new_Container_max_widgets(int max);

void container_free(void *__container);

SDL_Rect container_get_bounds_origin(void *container);

SDL_Rect container_get_bounds_camera(void *container);

void container_set_bounds(void *__container, SDL_Rect bounds);

void container_process_events(void *__container, SDL_Event event, Mouse mouse);

void container_draw(void *__container, SDL_Renderer *renderer, Camera *camera);

void container_add_widget(void *__container, void *widget);

void *container_remove_widget(void *__container);

void container_empty(void *container);


void __container_free(void *__container);

void __container_set_bounds(void *__container, SDL_Rect bounds);

void __container_process_events(void *__container, SDL_Event event, Mouse mouse);

void __container_draw(void *__container, SDL_Renderer *renderer, Camera *camera);

void __container_add_widget(void *__container, void *widget);

void *__container_remove_widget(void *__container);

#endif //CONTAINER_H
