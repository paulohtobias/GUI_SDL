#ifndef SCROLLABLE_CONTAINER_H
#define SCROLLABLE_CONTAINER_H

#include "container.h"

typedef struct ScrollableContainer{
	Container container;

	Camera *camera;
	//TO-DO: ScrollBar
} ScrollableContainer;

ScrollableContainer new_ScrollableContainer();

ScrollableContainer new_ScrollableContainer_max_widgets(int max);

void generic_scrollable_container_free(void *raw_container);

void generic_scrollable_container_set_bounds(void *raw_container, SDL_Rect bounds);

void generic_scrollable_container_process_events(void *raw_container, SDL_Event event, Mouse mouse);

void generic_scrollable_container_draw(void *raw_container, SDL_Renderer *renderer, Camera *camera);

#endif //SCROLLABLE_CONTAINER_H
