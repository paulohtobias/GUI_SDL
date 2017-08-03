#include "window.h"
#include "widgets/image.h"

int main(int argc, char *argv[]){
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error SDL_Init", SDL_GetError(), NULL);
        SDL_Quit();
        exit(1);
    }
    //Initialize SDL_image
    if( IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) < 0 ){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error IMG_Init", IMG_GetError(), NULL);
        exit(1);
    }
    
    Window *window = new_Window("Titulo", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);
    
    Container c = new_Container();
    container_set_bounds((void*)&c, window_get_bounds(window));
    
    Image i = new_Image("img.png");
    container_add_widget((void*)&c, (void*)&i);
    
    window_add_container(window, (void*)&c);
    
    while(!window->quit_requested){
        if(SDL_PollEvent(&window->event)){
            window_process_events(window);
            window_draw(window);
        }
    }
    
    return 0;
}
