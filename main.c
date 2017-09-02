#include "gui.h"
#include "containers/scrollable_container.h"

int main(int argc, char *argv[]) {
	Window *window = new_Window("Janela!", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);

	int i, n = 500;
	ScrollableContainer c = new_ScrollableContainer_max_widgets(n);
	SDL_Rect *r = &c.camera->bounds;
	window_add_container(window, &c);

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