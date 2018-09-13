#include "window.h"

extern void gui_init();

Window *new_Window(char *title, SDL_Rect bounds, Uint32 flags){
	return new_Window_layers(title, bounds, flags, 1);
}

Window *new_Window_layers(char *title, SDL_Rect bounds, Uint32 flags, int layers){
	Window *window = malloc(sizeof(Window));

	window->title = NULL;
	string_change(&window->title, title);

	gui_init();

	if((SDL_WINDOW_MAXIMIZED & flags) == SDL_WINDOW_MAXIMIZED){
		SDL_GetDisplayBounds(0, &bounds);
	}

	window->sdlwindow = SDL_CreateWindow(title, bounds.x, bounds.y, bounds.w, bounds.h, flags);

	window->background_color = COLOR_GREY(240);
	if(window->sdlwindow == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error creating window", SDL_GetError(), NULL);
		SDL_Quit();
		exit(1);
	}

	window->render_data = malloc(sizeof *window->render_data);
	window->render_data->camera = malloc(sizeof *window->render_data->camera);
	*window->render_data->camera = new_Camera(new_rect(0, 0, 0, 0));
	window->render_data->renderer = SDL_CreateRenderer(window->sdlwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(window->render_data->renderer == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error creating renderer", SDL_GetError(), NULL);
		SDL_Quit();
		exit(1);
	}
	set_renderer_draw_color(window->render_data->renderer, window->background_color);

	window->bounds = window_get_bounds(window);
	camera_set_bounds(window->render_data->camera, window->bounds);

	window->quit_requested = SDL_FALSE;
	window->mouse.button_state = MOUSE_IDLE;
	window->mouse.position = mouse_get_position();
	window->mouse.drag_offset = mouse_get_position();

	int i;
	window->layers = layers;
	if(layers <= 0)
		window->layers = 1;

	window->container = malloc(window->layers * sizeof(void *));
	if(window->container == NULL){
		printf("window->container = malloc(window->layers * sizeof(void *));\n");
		exit(1);
	}
	for(i = 0; i < window->layers; i++){
		window->container[i] = NULL;
	}

	return window;
}

void free_Window(Window *window){
	int i;

	free(window->title);
	SDL_DestroyRenderer(window->render_data->renderer);
	SDL_DestroyWindow(window->sdlwindow);

	//This should be replaced with window_emptyList
	for(i = 0; i < window->layers; i++){
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
	for(i = 0; i < window->layers; i++){
		if(window->container[i] != NULL){
			container_empty(window->container[i]);
		}
	}
}

void window_add_container(Window *window, void *container){
	int i;
	for(i = 0; i < window->layers; i++){
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
		container_set_bounds(container, window_get_bounds(window));
		window->container[layer] = container;
		((Widget*) container)->rendering_camera = window->render_data->camera;
	}else{
		//Overwrite or print a warning?
	}
}

void window_process_events(Window *window){
	if(window->event.type == SDL_QUIT){
		window->quit_requested = 1;
		return;
	}

	if(window->event.type == SDL_WINDOWEVENT){
		if(window->event.window.event == SDL_WINDOWEVENT_RESIZED){
			window->bounds = window_get_bounds(window);
			camera_set_bounds(window->render_data->camera, window->bounds);
		}
	}

	window->mouse.position = mouse_get_position();
	if(mouse_is_released(window->mouse)){
		window->mouse.button_state = MOUSE_IDLE;
	}
	if(window->event.type == SDL_MOUSEBUTTONDOWN){
		if(window->event.button.button == SDL_BUTTON_LEFT){
			window->mouse.button_state = MOUSE_LEFT_PRESSED;
			window->mouse.drag_offset = mouse_get_position();
		}else if(window->event.button.button == SDL_BUTTON_RIGHT){
			window->mouse.button_state = MOUSE_RIGHT_PRESSED;
		}
	}else if(window->mouse.button_state == MOUSE_LEFT_PRESSED && window->event.type == SDL_MOUSEBUTTONUP){
		if(window->event.button.button == SDL_BUTTON_LEFT){
			window->mouse.button_state = MOUSE_LEFT_RELEASED;
		}else if(window->event.button.button == SDL_BUTTON_RIGHT){
			window->mouse.button_state = MOUSE_RIGHT_RELEASED;
		}
	}

	camera_active = NULL;
	int i;
	for(i = 0; i < window->layers; i++){
		if(window->container[i] != NULL){
			container_process_events(window->container[i], window->event, window->mouse);
		}
	}

	if(window->mouse.button_state == MOUSE_LEFT_PRESSED){
		window->mouse.drag_offset = window->mouse.position;
	}
}

void window_draw(Window *window){
	set_renderer_draw_color(window->render_data->renderer, window->background_color);
	SDL_RenderClear(window->render_data->renderer);

	int i;
	for(i = 0; i < window->layers; i++){
		if(window->container[i] != NULL){
			container_draw(window->container[i], window->render_data);
		}
	}

	SDL_RenderPresent(window->render_data->renderer);
}
