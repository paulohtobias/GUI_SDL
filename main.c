#include "gui.h"

int main(int argc, char *argv[]){
    Window *window = new_Window("abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);

	int i, n = 3;
	ScrollableContainer c = new_ScrollableContainer_max_widgets(n * 5);
	window_add_container(window, &c);
	container_set_bounds(&c, new_rect(30, 30, 1200, 700));
	printR(widget_get_bounds_global(&c));
	
	Image imgs[n];
	for(i = 0; i < n; i++){
		int x = 20;
		imgs[i] = new_Image_with_position("Resources/Images/b at.jpg", new_Position(x, 480 * i));
		container_add_widget(&c, &imgs[i]);
		printR(widget_get_bounds_global(&imgs[i]));
	}

	Label lbl[n];
	for(i = 0; i < n; i++){
		lbl[i] = new_Label_with_bounds("./Resources/Images/img.png", new_rect(300 * i, 10, 250, 50));
		//lbl[i] = new_Label_with_position("./Resources/Images/img.png", new_Position(300 * i, 10));
		container_add_widget(&c, &lbl[i]);
		widget_set_border(lbl + i, new_Border_dynamic(2, COLOR_GREEN, widget_get_bounds_camera(lbl + i)));
	}
	label_set_color(&lbl[0], COLOR_RED);
	label_set_font(&lbl[1], "calibri");
	label_set_size(&lbl[1], 32);
	label_set_size(&lbl[2], 24);
	label_set_center(&lbl[1], SDL_TRUE);
    
    Button btn = new_Button_with_bounds("Botãó", NULL, new_rect(100, 100, 200, 50));
	container_add_widget(&c, &btn);

	while(!window->quit_requested){
		if(SDL_WaitEvent(&window->event)){
			window_process_events(window);

			window_draw(window);
			
			/**
			set_renderer_draw_color(window->renderer, COLOR_BLUE);
			SDL_RenderDrawLine(window->renderer, 0, 30, 1200, 30);
			SDL_RenderPresent(window->renderer);
			/**/
			
			puts("");
		}else{
			printf("%s\n", SDL_GetError());
			return 1;
		}
	}
	return 0;
}