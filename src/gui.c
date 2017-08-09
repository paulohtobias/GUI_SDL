#include "gui.h"

bool _gui_was_init = false;

void gui_init(){
    if(_gui_was_init == false){
        if(SDL_Init(SDL_INIT_VIDEO) < 0){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error SDL_Init", SDL_GetError(), NULL);
            SDL_Quit();
            exit(1);
        }
        //Initialize SDL_image
        if(IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) < 0){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error IMG_Init", IMG_GetError(), NULL);
            exit(1);
        }
        
        if(TTF_Init() < 0){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error TTF_Init", TTF_GetError(), NULL);
            exit(1);
        }
        
        label_default_style.color = label_default_color;
        snprintf(label_default_style.font, 60, "./Resources/Fonts/%s.ttf", label_default_font);
        //strncpy(label_default_style.font, label_default_font, 60);
        label_default_style.size = label_default_size;
        label_default_style.center = false;
        label_default_style.wrap = false;
        
        _gui_was_init = true;
    }
}
