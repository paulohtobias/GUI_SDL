#include "gui.h"

int main(int argc, char *argv[]) {
	Window *window = new_Window("Caralhou!", new_Size(800, 600), WINDOW_DEFAULT_FLAGS);

	Container c = new_Container();
	window_add_container(window, &c);

	int i, n = 200;
	Image img[n];
	for(i=0; i<n; i++){
		img[i] = new_Image_with_position("./Resources/Images/img.png", new_Position(300*i, 0));
		container_add_widget(&c, &img[i]);
	}

	while (!window->quit_requested) {
		if (SDL_PollEvent(&window->event)) {
			window_process_events(window);
            
			window_draw(window);
		}
	}
	return 0;
}