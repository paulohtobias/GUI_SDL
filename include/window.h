#ifndef WINDOW_H
#define WINDOW_H

#include "container.h"

#define WINDOW_DEFAULT_FLAGS (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE)
#define LAYER_BOTTOM 0
#define LAYER_TOP window->layers - 1

typedef struct{
	//Window info
	char *title;
	SDL_Window *sdlwindow;
	SDL_Renderer *renderer;
	SDL_Color backgroundColor;
	SDL_Rect bounds;

	SDL_Event event;
	int quit_requested;

	//Mouse
	Mouse mouseState;

	//Camera and Scrollbar
	Camera camera;
	//ScrollBar

	//Containers
	int layers;
	Container *containers;

}Window;

Window *newWindow(char *title, SDL_Rect size, Uint32 flags, int layers);
void freeWindow(Window *window);
SDL_Renderer *newRenderer(SDL_Window *window);
SDL_Rect window_getBounds(Window *window);
void window_emptyList(Window *window);

///===================----WINDOW CONTAINERS----===================///
void window_add_container(Window *window, Container container, int layer);

void window_processEvents(Window *window);

void window_draw(Window *window);

#endif //WINDOW_H
