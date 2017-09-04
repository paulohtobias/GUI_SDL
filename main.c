#include "gui.h"

#define printR(c) SDL_Rect r = c; printf("(%d, %d, %d, %d)\n", r.x, r.y, r.w, r.h);

int main(int argc, char *argv[]){
	Window *window = new_Window("abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);

	int i, n = 5;
	ScrollableContainer c = new_ScrollableContainer_max_widgets(n);
	window_add_container(window, &c);

	Label lbl[n];
	for(i = 0; i < n; i++){
		lbl[i] = new_Label_with_position("./Resources/Images/img.png", new_Position(300 * i, 0));
		container_add_widget(&c, &lbl[i]);
	}
	label_set_color(&lbl[0], COLOR_RED);
	label_set_font(&lbl[1], "calibri");
	label_set_size(&lbl[2], 18);
	label_center(&lbl[1]);

	while(!window->quit_requested){
		if(SDL_PollEvent(&window->event)){
			window_process_events(window);

			window_draw(window);
		}
	}
	return 0;
}