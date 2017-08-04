#include "gui.h"

bool _gui_was_init = false;

void gui_init(){
    if(_gui_was_init == false){
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
        _gui_was_init = true;
    }
}
