#include "gui.h"

int main(int argc, char *argv[]){
    Window *window = new_Window("Titulo", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);
    
    int i, n = 3000;
    Container c = new_Container_max_widgets(n);
    container_set_bounds((void*)&c, window_get_bounds(window));
    
    if(argc > 1){
        n = atoi(argv[1]);
    }
    printf("n: %d\n", n);
    
    Image im[n];
    for(i=0; i<n; i++){
        im[i] = new_Image_with_position("img.png", new_Position(300 * i, 0));
        container_add_widget((void*)&c, (void*)&im[i]);
    }
    
    window_add_container(window, (void*)&c);
    
    while(!window->quit_requested){
        if(SDL_PollEvent(&window->event)){
            window_process_events(window);
            window_draw(window);
        }
    }
    
    return 0;
}
