/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Text
 * Text library using SDL2
 */

#include "widgets/text.h"

//Create and free
Text newText(char *str, SDL_Rect bounds){
	Text txt = malloc(sizeof(struct Text_));

	txt->texture = NULL;
	txt->state = newWidgetState();

	txt->content = calloc(text_content_size, sizeof(char));
	text_setText(txt, str);
	text_setColor(txt, default_text_color);
	text_setFont(txt, default_text_font, default_text_size);
	text_setWrap(txt, false);
	resetBounds(&txt->region, bounds);
	txt->center_area = bounds;

	return txt;
}
Text text_newText(char *str, SDL_Rect bounds, char *font, int txtSize, Uint32 maxWidth, SDL_Color color){
	Text txt = malloc(sizeof(struct Text_));

	txt->texture = NULL;
	txt->state = newWidgetState();

	txt->content = calloc(text_content_size, sizeof(char));
	text_setText(txt, str);
	text_setColor(txt, color);
	text_setFont(txt, font, txtSize);
	text_setWrap(txt, false); //TO-DO: check if maxWidth > 0 here (this width needs to passed to text_process)
	resetBounds(&txt->region, bounds);
	text_setBounds(txt, bounds);

	return txt;
}
void init_text(Text txt, SDL_Renderer *renderer){

	//Getting the width and height that the text will have.
	SDL_Surface *temp;
	TTF_Font *ttf_font = TTF_OpenFont(txt->font, txt->txt_size);
	temp = TTF_RenderUTF8_Blended(ttf_font, txt->content, txt->color);
	if(temp == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Surface Error on init_text", TTF_GetError(), NULL);
		SDL_free(txt);

		TTF_Quit();
		SDL_Quit();

		exit(1);
	}

	SDL_Rect size = text_getBounds(txt);
    size.w = temp->w;
    size.h = temp->h;

	SDL_FreeSurface(temp);
	TTF_CloseFont(ttf_font);
	temp = NULL;
	ttf_font = NULL;

	resetBounds(&txt->region, size);
}
void freeText(Text txt){
	free(txt->content);
    SDL_DestroyTexture(txt->texture);
    free(txt);
}

//Get
SDL_Rect text_getBounds(Text txt){
	return getBounds(txt->region);
}

//Set and Update
void text_setText(Text txt, char *content){
	strcpy(txt->content, content);

	text_setChanged(txt, true);
}
void text_setFont(Text txt, char *font, int txtSize){
	if(font != NULL)
		sprintf(txt->font, "./Resources/Fonts/%s.ttf", font);
	if(txtSize > 0)
		txt->txt_size = txtSize;

	text_setChanged(txt, true);
}
void text_setColor(Text txt, SDL_Color color){
	txt->color = color;
	text_setChanged(txt, true);
}
void text_setWrap(Text txt, bool wrap){
	txt->wrap = wrap;

	text_setChanged(txt, true);
}
void text_setBounds(Text txt, SDL_Rect position){
	setBounds(&txt->region, position);
}
void text_updateBounds(Text txt, SDL_Rect position){
	updateBounds(&txt->region, position);
}
void text_setChanged(Text txt, int state){
	//If they're equal, then don't do anything.
	if(txt->state.wasChanged == state){
		return;
	}

	//If either is false, then it should be false.
	if(txt->state.wasChanged == false || state == false){
		txt->state.wasChanged = state;
		return;
	}

	//Here, neither are false.
	//But if the state is already on TEXT_CENTERED, it needs to
	//keep that state.
	if(txt->state.wasChanged != TEXT_CENTERED){
		txt->state.wasChanged = state;
	}
}

//Extra
void text_center(Text txt, SDL_Rect limit){
    text_setWrap(txt, true);
	txt->center_area = limit;
	text_setChanged(txt, TEXT_CENTERED);
}
void text_process(Text txt, Uint32 maxWidth, SDL_Renderer* renderer){
	if(widget_wasChanged(txt->state) != false){
		SDL_Surface *surface;
		TTF_Font *ttf_font = TTF_OpenFont(txt->font, txt->txt_size);
		if(!txt->wrap){
			surface = TTF_RenderUTF8_Blended(ttf_font, txt->content, txt->color);
		}else{
			if(txt->state.wasChanged == TEXT_CENTERED){
				maxWidth = txt->center_area.w;
			}
			surface = TTF_RenderUTF8_Blended_Wrapped(ttf_font, txt->content, txt->color, maxWidth);
		}
		if(surface == NULL){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Surface Error", TTF_GetError(), NULL);
			SDL_free(txt);

			TTF_Quit();
			SDL_Quit();

			exit(1);
		}
		TTF_CloseFont(ttf_font);
		ttf_font = NULL;

		if(txt->texture != NULL){
			SDL_DestroyTexture(txt->texture);
			txt->texture = NULL;
		}

		txt->texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		surface = NULL;
		if(txt->texture == NULL){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Texture Error", SDL_GetError(), NULL);
			free(txt);

			TTF_Quit();
			SDL_Quit();

			exit(1);
		}

		int newWidth, newHeight;
		SDL_QueryTexture(txt->texture, NULL, NULL, &newWidth, &newHeight);
		txt->region.real.w = txt->region.relative.w = newWidth;
		txt->region.real.h = txt->region.relative.h = newHeight;

		if(txt->state.wasChanged == TEXT_CENTERED){ //TO-DO: Create an option to add "..." if the text is too large.
			int txtX = (txt->center_area.x + txt->center_area.w/2) - (text_getBounds(txt).w)/2;
			int txtY = (txt->center_area.y + txt->center_area.h/2) - (text_getBounds(txt).h)/2;
			if(txtX < txt->region.real.x){
				txtX = txt->region.real.x;
			}
			if(txtY < txt->region.real.y){
				txtY = txt->region.real.y;
			}
			text_setBounds(txt, region_position(txtX, txtY));
		}
		text_setChanged(txt, false);
	}
}

//Events
void text_processEvents(SDL_Event event, Mouse mouseState, Text txt){
	basic_widget_processEvents(event, mouseState, &txt->state, txt->region);
	if(text_isDragged(txt)){
		text_updateBounds(txt, widget_dragPosition(mouseState));
	}
}
bool text_isFocused(Text txt){
	return widget_isFocused(txt->state);
}
bool text_isPressed(Text txt){
	return widget_isPressed(txt->state);
}
bool text_isReleased(Text txt){
	return widget_isReleased(txt->state);
}
bool text_isDragged(Text txt){
	return widget_isDragged(txt->state);
}

//Render
void renderText(Text txt, SDL_Renderer *renderer, Camera camera){
	camera_updateWidgetPosition(camera, &txt->region);

	if( !camera_widget_is_off(camera, text_getBounds(txt)) ){
		if(txt->state.isOnCamera == false){
            txt->state.isOnCamera = true;
        }

		text_process(txt, text_getBounds(txt).w, renderer);
        SDL_RenderCopy(renderer, txt->texture, NULL, &txt->region.relative);
	}else if(txt->state.isOnCamera == true){
        txt->state.isOnCamera = false;

		SDL_DestroyTexture(txt->texture);
        txt->texture = NULL;

		text_setChanged(txt, true);
    }
}
