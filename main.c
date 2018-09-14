#include "gui.h"

int main(int argc, char *argv[]){
    Window *window = new_Window_layers("abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS, 2);

	int i, n = 3;
	ScrollableContainer c = new_ScrollableContainer_max_widgets(n * 5);
	window_add_container(window, &c);
	container_set_bounds(&c, new_rect(30, 50, 1200, 500));
	widget_set_border(&c, new_Border_dynamic(2, COLOR_BLUE, container_get_bounds_global(&c)));

	ScrollableContainer c2 = new_ScrollableContainer_max_widgets(n * 5);
	widget_set_border(&c2, new_Border_dynamic(2, COLOR_BLUE, container_get_bounds_global(&c2)));
	container_set_bounds(&c2, new_rect(300, 300, 300, 150));

	Image imgs[n];
	for(i = 0; i < n; i++){
		int x = 20;
		imgs[i] = new_Image_with_position("Resources/Images/b at.jpg", new_Position(x, 480 * i));
		container_add_widget(&c, &imgs[i]);
	}

	Label lbl[n];
	for(i = 0; i < n; i++){
		lbl[i] = new_Label_with_bounds("./Resources/Images/img.png", new_rect(10, 70 * i + 10, 200, 50));
		//lbl[i] = new_Label_with_position("./Resources/Images/img.png", new_Position(300 * i, 10));
		container_add_widget(&c2, &lbl[i]);
		widget_set_border(lbl + i, new_Border_dynamic(5, COLOR_GREEN, widget_get_bounds_global(lbl + i)));
	}
	label_set_font(&lbl[0], "calibri");
	label_set_font_size(&lbl[0], 32);
	label_set_center(&lbl[0], SDL_TRUE);
	label_set_center(&lbl[1], SDL_TRUE);
	label_set_color(&lbl[1], COLOR_RED);
	label_set_font_size(&lbl[2], 24);
    
    Button btn = new_Button_with_bounds("Botãó", NULL, new_rect(100, 100, 200, 50));
	container_add_widget(&c, &btn);

	container_add_widget(&c, &c2);

	while(!window->quit_requested){
		if(SDL_WaitEvent(&window->event)){
			window_process_events(window);

			window_draw(window);

			printR(c2.camera.bounds);
		}else{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), window->sdlwindow);
			return 1;
		}
	}
	return 0;
}