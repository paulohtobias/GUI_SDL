#include "gui.h"

int main(int argc, char *argv[]){
    Window *windw = new_Window("abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);

	int i, n = 3;
	ScrollableContainer c = new_ScrollableContainer_max_widgets(n * 5);
	window_add_container(windw, &c);

	Label lbl[n];
	for(i = 0; i < n; i++){
		lbl[i] = new_Label_with_position("./Resources/Images/img.png", new_Position(300 * i, 0));
		//container_add_widget(&c, &lbl[i]);
	}
	label_set_color(&lbl[0], COLOR_RED);
	label_set_font(&lbl[1], "calibri");
	label_set_size(&lbl[2], 18);
	label_set_center(&lbl[1], SDL_TRUE);
    
    Button btn = new_Button_with_bounds("Botãó", NULL, new_rect(100, 100, 200, 50));
	//container_add_widget(&c, &btn);
	
	Image imgs[n];
	for(i = 0; i < n; i++){
		imgs[i] = new_Image_with_position("Resources/Images/b at.jpg", new_Position(20, 480 * i));
		container_add_widget(&c, &imgs[i]);
	}

	while(!windw->quit_requested){
		if(SDL_WaitEvent(&windw->event)){
			window_process_events(windw);

			window_draw(windw);
		}else{
			printf("%s\n", SDL_GetError());
			return 1;
		}
	}
	return 0;
}