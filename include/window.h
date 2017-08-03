#ifndef WINDOW_H
#define WINDOW_H

#include "containers/container.h"

#define WINDOW_DEFAULT_FLAGS (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE)
#define LAYER_BOTTOM 0
#define LAYER_TOP window->layers - 1

typedef struct{
    //Window info
    char *title;
    SDL_Window *sdlwindow;
    SDL_Renderer *renderer;
    SDL_Color background_color;
    SDL_Rect bounds;

    SDL_Event event;
    bool quit_requested;

    //Mouse
    Mouse mouse;

    //Camera and Scrollbar
    Camera *camera;
    //ScrollBar

    int layers;
    //Container layers.
    void **container;
}Window;

Window *new_Window(char *title, SDL_Rect size, Uint32 flags);

Window *new_Window_layers(char *title, SDL_Rect size, Uint32 flags, int layers);

void free_Window(Window *window);

SDL_Rect window_get_bounds(Window *window);

void window_empty_containers(Window *window);

void window_add_container(Window *window, void *container);

void window_add_container_layer(Window *window, void *container, int layer);

void window_process_events(Window *window);

void window_draw(Window *window);

#endif //WINDOW_H
