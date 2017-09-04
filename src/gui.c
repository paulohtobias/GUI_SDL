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
		if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG)){
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
