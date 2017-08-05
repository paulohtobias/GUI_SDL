#include "gui.h"

int main(int argc, char *argv[]){
    Window *window = new_Window("Titulo", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);
    
    int i, n = 1;
    
    Container c1, c2;
    Image i1, i2;
    i1 = new_Image("img.png");
    i2 = new_Image("palheta2.png");
    
    c1 = new_Container_max_widgets(5);
    c2 = new_Container_max_widgets(5);
    
    container_add_widget(&c1, &i1);
    
    window_add_container(window, &c1);
    
    while(!window->quit_requested){
        if(SDL_PollEvent(&window->event)){
            window_process_events(window);
            
            switch(window->event.type){
                case SDL_KEYDOWN:
                    switch(window->event.key.keysym.sym){
                        case SDLK_RIGHT:
                            update_position_origin(&i1.t_widget.widget.bounds, new_Position(1, 0));
                            break;
                    }
            }
            
            window_draw(window);
        }
    }
    
    return 0;
}
