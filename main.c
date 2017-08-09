#include "gui.h"

int main(int argc, char *argv[]){
    Window *window = new_Window("Game of Thrones", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);
    
    Container c1 = new_Container();
    
    Image bg = new_Image("img.png");
    Image img = new_Image("seph.jpg");
	Rectangle r = new_Rectangle_with_bounds(COLOR_RGBA(240,240, 240,200), widget_get_bounds_origin(&img));
    
    container_add_widget(&c1, &bg);
    container_add_widget(&c1, &img);
	container_add_widget(&c1, &r);
    
    window_add_container(window, &c1);
    
    while(!window->quit_requested){
        if(SDL_PollEvent(&window->event)){
            window_process_events(window);
            window_draw(window);
        }
    }
    
    return 0;
}
