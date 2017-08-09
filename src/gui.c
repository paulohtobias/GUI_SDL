#include "gui.h"
#include "widgets/button.h"

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
        
        init_look_and_feel();
        
        _gui_was_init = true;
    }
}

void init_look_and_feel(){
    init_look_and_feel_label();
    init_look_and_feel_button();
}

void init_look_and_feel_label(){
    label_default_style.color = label_default_color;
    snprintf(label_default_style.font, 60, "./Resources/Fonts/%s.ttf", label_default_font);
    label_default_style.size = label_default_size;
    label_default_style.center = false;
    label_default_style.wrap = false;
}

void init_look_and_feel_button(){
    button_default_style_idle.label = &label_default_style;
    button_default_style_idle.background = button_default_bg_color_idle;
    button_default_style_idle.border = button_default_border_color_idle;
    
    button_default_style_focused.label = &label_default_style;
    button_default_style_focused.background = button_default_bg_color_focused;
    button_default_style_focused.border = button_default_border_color_focused;
    
    button_default_style_pressed.label = &label_default_style;
    button_default_style_pressed.background = button_default_bg_color_pressed;
    button_default_style_pressed.border = button_default_border_color_pressed;
    
    button_default_style_disabled.background = button_default_bg_color_disabled;
    button_default_style_disabled.border = button_default_border_color_disabled;
    button_default_style_disabled.label = malloc(sizeof(LabelStyle));
    button_default_style_disabled.label->color = label_default_color;
    snprintf(button_default_style_disabled.label->font, 60, "./Resources/Fonts/%s.ttf", label_default_font);
    button_default_style_disabled.label->size = label_default_size;
    button_default_style_disabled.label->center = false;
    button_default_style_disabled.label->wrap = false;
    button_default_style_disabled.label->color = button_default_label_color_disabled;
}
