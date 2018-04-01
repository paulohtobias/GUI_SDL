#ifndef SCROLLABLE_CONTAINER_H
#define SCROLLABLE_CONTAINER_H

#include "container.h"

///Global virtual table.
VT_Widget __gscontainer_widget_vt;

typedef struct ScrollableContainer{
	Container container;

	Camera *camera;
	//TO-DO: ScrollBar
} ScrollableContainer;

ScrollableContainer new_ScrollableContainer();

ScrollableContainer new_ScrollableContainer_max_widgets(int max);

void __scrollable_container_free(void *__container);

void __scrollable_container_set_bounds(void *__container, SDL_Rect bounds);

void __scrollable_container_process_events(void *__container, SDL_Event event, Mouse mouse);

void __scrollable_container_draw(void *__container, SDL_Renderer *renderer, Camera *camera);

#endif //SCROLLABLE_CONTAINER_H
