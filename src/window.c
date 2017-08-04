#include "window.h"

extern void gui_init();

Window *new_Window(char *title, SDL_Rect size, Uint32 flags){
    return new_Window_layers(title, size, flags, 1);
}

Window *new_Window_layers(char *title, SDL_Rect size, Uint32 flags, int layers){
    Window *window = malloc(sizeof(Window));

	window->title = malloc(sizeof(title));
    strcpy(window->title, title);
    
    gui_init();

	if((SDL_WINDOW_MAXIMIZED & flags) == SDL_WINDOW_MAXIMIZED){
		printf("MAXI\n");
		SDL_GetDisplayBounds(0, &size);
	}

	window->sdlwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.w, size.h, flags);
    
    window->background_color = COLOR_GREY(240);
    if(window->sdlwindow == NULL){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error creating window", SDL_GetError(), NULL);
        SDL_Quit();
        exit(1);
    }
    
	window->renderer = SDL_CreateRenderer(window->sdlwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(window->renderer == NULL){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error creating renderer", SDL_GetError(), NULL);
        SDL_Quit();
        exit(1);
    }
    set_renderer_draw_color(window->renderer, window->background_color);

	window->bounds = window_get_bounds(window);

	window->quit_requested = false;
	window->mouse.button_state = MOUSE_IDLE;
	window->mouse.position = mouse_get_position();
	window->mouse.drag_offset = mouse_get_position();
	window->camera = new_Camera(window->bounds);

	int i;
	window->layers = layers;
	if(layers <= 0)
		window->layers = 1;

	window->container = malloc(window->layers * sizeof(void *));
	for(i=0; i<window->layers; i++){
		window->container[i] = NULL;
	}
    
    return window;
}

void free_Window(Window *window){
    int i;

	free(window->title);
	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->sdlwindow);
	free_Camera(window->camera);

	//This should be replaced with window_emptyList
	for(i=0; i<window->layers; i++){
		container_free(window->container[i]);
	}

	free(window);
}

SDL_Rect window_get_bounds(Window *window){
    int width, height;
    SDL_GetWindowSize(window->sdlwindow, &width, &height);
    return new_rect(0, 0, width, height);
}

void window_empty_containers(Window *window){
    int i;
    for(i=0; i<window->layers; i++){
        if(window->container[i] != NULL){
            container_empty(window->container[i]);
        }
    }
}

void window_add_container(Window *window, void *container){
    int i;
    for(i=0; i<window->layers; i++){
        if(window->container[i] == NULL){
            window_add_container_layer(window, container, i);
            break;
        }
    }
}

void window_add_container_layer(Window *window, void *container, int layer){
    //Fixing the layer if necessary.
	if(layer < LAYER_BOTTOM){
		layer = LAYER_BOTTOM;
	}else if(layer > LAYER_TOP){
		layer = LAYER_TOP;
    }

	if(window->container[layer] == NULL){
		container_init(container, window->renderer);
		window->container[layer] = container;
	}else{
		//Overwrite or print a warning?
	}
}

void window_process_events(Window *window){
    if(window->event.type == SDL_QUIT){
		window->quit_requested = 1;
		return;
	}

	if(window->event.type == SDL_WINDOWEVENT && window->event.window.event == SDL_WINDOWEVENT_RESIZED){
        //scrollbar_updatePosition(sb, camera);
    }
    
    //int i;
}

void window_draw(Window *window){
    set_renderer_draw_color(window->renderer, window->background_color);
	SDL_RenderClear(window->renderer);

	int i;
	for(i=0; i<window->layers; i++){
		if(window->container[i] != NULL){
			container_draw(window->container[i], window->renderer, window->camera);
		}
	}

	SDL_RenderPresent(window->renderer);
}
