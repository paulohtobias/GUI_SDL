#include "gui.h"
#include <math.h>

#define printR(c) SDL_Rect r = c; printf("(%d, %d, %d, %d)\n", r.x, r.y, r.w, r.h);

int main(int argc, char *argv[]){
	Window *window = new_Window("circulo", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);
	
	set_renderer_draw_color(window->renderer, window->background_color);
	SDL_RenderClear(window->renderer);

	set_renderer_draw_color(window->renderer, COLOR_RED);

	double x, y;
	int dx = 1366/2, dy = 705/2; //Centralizing the circle on the screen.
	int r = 100; //radius
	int r2 = r * r;
	for(x=dx - r; x<=dx + r; x+=0.0001){
		y = sqrt((r2) - (x - dx) * (x - dx));
		SDL_RenderDrawPoint(window->renderer, x, y + dy);
		SDL_RenderDrawPoint(window->renderer, x, -y + dy);
	}

	SDL_RenderPresent(window->renderer);


	while(!window->quit_requested){
		if(SDL_WaitEvent(&window->event)){
			window_process_events(window);
			
		}else{
			printf("%s\n", SDL_GetError());
			return 1;
		}
	}
	return 0;
}
