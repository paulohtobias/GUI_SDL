#include "gui.h"

int main(int argc, char *argv[]){
    Window *window = new_Window("Titulo", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);
    
    int i, n = 1;
    
    Container c1, c2;
    Image i1, i2;
    i1 = new_Image("img.png");
    i2 = new_Image("palheta2.png");
    
    Label l1 = new_Label_with_position("Paulo Henrique Tobias", new_Position(304, 0));
    
    c1 = new_Container_max_widgets(5);
    c2 = new_Container_max_widgets(5);
    
    container_add_widget(&c1, &i1);
    container_add_widget(&c1, &l1);
    /*container_add_widget(&c2, &i2);
    container_set_bounds(&c2, new_rect(0, 0, 300, 450));
    container_add_widget(&c1, &c2);*/
    
    window_add_container(window, &c1);
    
    int sdas = 0;
    int px = 0;
    while(!window->quit_requested){
        if(SDL_PollEvent(&window->event)){
            window_process_events(window);
            
            switch(window->event.type){
                case SDL_KEYDOWN:
                    switch(window->event.key.keysym.sym){
                        case SDLK_RIGHT:
                            container_set_bounds(&c1, new_rect(++px, 0, -1, -1));
                            //update_position_origin(&i1.t_widget.widget.bounds, new_Position(1, 0));
                            break;
                    }
            }
            
            window_draw(window);
        }
    }
    
    return 0;
}
