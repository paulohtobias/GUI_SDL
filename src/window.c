#include "window.h"

Window *newWindow(char *title, SDL_Rect size, Uint32 flags, int layers){
	Window *window = malloc(sizeof(Window));

	window->title = title;

	if((SDL_WINDOW_MAXIMIZED & flags) == SDL_WINDOW_MAXIMIZED){
		printf("MAXI\n");
		SDL_GetDisplayBounds(0, &size);
	}

	window->sdlwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.w, size.h, flags);
    if(window->sdlwindow == NULL){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error creating window", SDL_GetError(), NULL);
        SDL_Quit();
        exit(1);
    }
	window->renderer = newRenderer(window->sdlwindow);

	window->backgroundColor = COLOR_GREY(240);
	window->bounds = window_getBounds(window);

	window->quit_requested = 0;
	window->mouseState.button = mouse_idle;
	window->mouseState.mPos = getMousePosition();
	window->mouseState.mPosDrag = getMousePosition();
	window->camera = newCamera(window_getBounds(window));

	int i;
	window->layers = layers;
	if(layers <= 0)
		window->layers = 1;

	window->containers = malloc(window->layers * sizeof(Container));
	for(i=0; i<window->layers; i++){
		//window->containers[i] = newContainer(CNT_FIXED, window_getBounds(window));
		window->containers[i] = NULL;
	}

	window->widgets = malloc(window->layers * sizeof(WidgetList));
	for(i=0; i<window->layers; i++){
		window->widgets[i] = newWidgetList();
	}

    return window;
}
void freeWindow(Window *window){
	int i;

	free(window->title);
	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->sdlwindow);
	freeCamera(window->camera);

	//This should be replaced with window_emptyList
	for(i=0; i<window->layers; i++){
		freeList(window->widgets[i]);
	}

	free(window);
}
SDL_Renderer *newRenderer(SDL_Window *window){
    SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL ){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error creating renderer", SDL_GetError(), NULL);
        SDL_Quit();
        exit(1);
    }else{
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
    return renderer;
}
SDL_Rect window_getBounds(Window *window){
	int x, y;
    int width, height;
	SDL_GetWindowPosition(window->sdlwindow, &x, &y);
    SDL_GetWindowSize(window->sdlwindow, &width, &height);
    return region_area(0, 0, width, height);
}
void window_emptyList(Window *window){
    int i;
	for(i=0; i<window->layers; i++){
		freeContainer(window->containers[i]);
		window->containers[i] = NULL;
		//window->containers[i] = newContainer(CNT_FIXED, window_getBounds(window));
	}
	/*
    for(i=0; i<window->layers; i++){
        freeList(window->widgets[i]);
		window->widgets[i] = NULL;
        window->widgets[i] = newWidgetList();
    }*/
	window->camera->limit = window_getBounds(window);
}

///===================----WINDOW WIDGETS----===================///
//Add Container
void window_add_container(Window *window, Container container, int layer){
	//Fixing the layer if necessary.
	if(layer < LAYER_BOTTOM)
		layer = LAYER_BOTTOM;
	else if(layer > LAYER_TOP)
		layer = LAYER_TOP;

	if(window->containers[layer] == NULL){
		init_container(container, window->renderer);
		window->containers[layer] = container;
	}else{
		//Overwrite or print a warning?
	}
}

void window_add(Window *window, WidgetType type, u_Widget *data, int layer){
	//Fixing the layer if necessary.
	if(layer < LAYER_BOTTOM)
		layer = LAYER_BOTTOM;
	else if(layer > LAYER_TOP)
		layer = LAYER_TOP;

	window->containers[layer]->add_widget(window->containers[layer], newWidget(data, type));

	/*Widget obj = malloc(sizeof(struct Widget_));


	//Setting the object attributes and adding it to the list.
	obj->layer = layer;
	obj->obj_type = type;
	obj->obj_data = data;

	list_add_last(window->widgets[layer], obj);

	//Checking if the object position is "out of bounds" so the camera can reach it too.
	if(region_reachX(widget_getBounds(obj)) > window->camera->limit.w ){
		window->camera->limit.w = region_reachX(widget_getBounds(obj));
	}
	if(region_reachY(widget_getBounds(obj)) > window->camera->limit.h ){
		window->camera->limit.h = region_reachY(widget_getBounds(obj));
	}*/
}
void window_add_square(Window *window, Square sqr, int layer){
	u_Widget *data = malloc(sizeof(u_Widget));
	data->sqr = sqr;
	window_add(window, WGT_SQUARE, data, layer);
}
void window_add_frame(Window *window, Frame frame, int layer){
	u_Widget *data = malloc(sizeof(u_Widget));
	data->frame = frame;
	window_add(window, WGT_FRAME, data, layer);
}
void window_add_image(Window *window, Image img, int layer){
	init_image(img, window->renderer);

	u_Widget *data = malloc(sizeof(u_Widget));
	data->img = img;
	window_add(window, WGT_IMAGE, data, layer);
}
void window_add_text(Window *window, Text txt, int layer){
	init_text(txt, window->renderer);

	u_Widget *data = malloc(sizeof(u_Widget));
	data->txt = txt;
	window_add(window, WGT_TEXT, data, layer);
}
void window_add_button(Window *window, Button btn, int layer){
	init_button(btn, window->renderer);

	u_Widget *data = malloc(sizeof(u_Widget));
	data->btn = btn;
	window_add(window, WGT_BUTTON, data, layer);
}
void window_add_frameChapter(Window *window, FrameChapter frameC, int layer){
    init_frameChapter(frameC, window->renderer);

    u_Widget *data = malloc(sizeof(u_Widget));
	data->frameC = frameC;
	window_add(window, WGT_FRAMECHAPTER, data, layer);
}

void window_processEvents(Window *window){
	if(window->event.type == SDL_QUIT){
		window->quit_requested = 1;
		return;
	}
	int i;

	if(window->event.type == SDL_WINDOWEVENT && window->event.window.event == SDL_WINDOWEVENT_RESIZED){
        camera_updateSize(window->sdlwindow, window->camera);
        //scrollbar_updatePosition(sb, camera);
    }

    //processEvents_camera(window->camera, window->event);

	window->mouseState.mPos = getMousePosition();
	if(mouseReleased(window->mouseState)){
		window->mouseState.button = mouse_idle;
	}
	if(window->event.type == SDL_MOUSEBUTTONDOWN){
		if(window->event.button.button == SDL_BUTTON_LEFT){
			window->mouseState.button = mouse_left_pressed;
			window->mouseState.mPosDrag = getMousePosition();
		}else if(window->event.button.button == SDL_BUTTON_RIGHT){
			window->mouseState.button = mouse_right_pressed;
		}
	}else if( window->mouseState.button == mouse_left_pressed && window->event.type == SDL_MOUSEBUTTONUP){
		if(window->event.button.button == SDL_BUTTON_LEFT){
			window->mouseState.button = mouse_left_released;
		}else if(window->event.button.button == SDL_BUTTON_RIGHT){
			window->mouseState.button = mouse_right_released;
		}
	}

	for(i=0; i<window->layers; i++){
        int j;
		int f, l;
		if(window->containers[i] != NULL){
			if(window->event.type == SDL_WINDOWEVENT && window->event.window.event == SDL_WINDOWEVENT_RESIZED){
				camera_updateSize(window->sdlwindow, window->containers[i]->camera);
			}
			window->containers[i]->processEvents(window->containers[i], window->event, window->mouseState);
		}
	}

	if(window->mouseState.button == mouse_left_pressed){
		window->mouseState.mPosDrag = window->mouseState.mPos;
	}

}

void window_draw(Window *window){

	SetRenderDrawColor(window->renderer, window->backgroundColor);
	SDL_RenderClear(window->renderer);

	int i;
	for(i=0; i<window->layers; i++){
		int j;
		if(window->containers[i] != NULL){
			window->containers[i]->draw(window->containers[i], window->renderer);
		}
		/*if(window->widgets[i] != NULL){
            int f = window->widgets[i]->first;
            int l = window->widgets[i]->last;

			for(j=f; j<=l; j++){
                widget_render(window->widgets[i]->array[j], window->renderer, window->camera);
			}
		}*/
	}

	SDL_RenderPresent(window->renderer);
}
