/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Text
 * Text library using SDL2
 */

#ifndef TEXT_H
#define TEXT_H

#include "widgets/basicUI.h"
#include <string.h>

#define text_content_size 500
#define default_text_color COLOR_BLACK
#define default_text_font "arial"
#define default_text_size 14

struct Text_{
	char *content;
	char font[200];
	int txt_size;
	SDL_Color color;
	bool wrap;

	Bounds region;
	SDL_Rect center_area; //The area which the text will be centered in if asked to.
	WidgetState state;

	SDL_Texture *texture;
};
typedef struct Text_* Text;

//Create and free
Text newText(char *str, SDL_Rect bounds);
Text text_newText(char *str, SDL_Rect bounds, char *font, int txtSize, Uint32 maxWidth, SDL_Color color);
void init_text(Text txt, SDL_Renderer *renderer);
void freeText(Text txt);

//Get
SDL_Rect text_getBounds(Text txt);

//Set and Update
void text_setText(Text txt, char *content);
void text_setFont(Text txt, char *font, int txtSize);
void text_setColor(Text txt, SDL_Color color);
void text_setWrap(Text txt, bool wrap);
void text_setBounds(Text txt, SDL_Rect position);
void text_updateBounds(Text txt, SDL_Rect position);
void text_setChanged(Text txt, int state);

//Extra
void text_process(Text txt, Uint32 maxWidth, SDL_Renderer *renderer);
#define TEXT_CENTERED 2 //This will be used in text_process
void text_center(Text txt, SDL_Rect limit);

//Events
void text_processEvents(SDL_Event event, Mouse mouseState, Text txt);
bool text_isFocused(Text txt);
bool text_isPressed(Text txt);
bool text_isReleased(Text txt);
bool text_isDragged(Text txt);

//Render
void renderText(Text txt, SDL_Renderer *renderer, Camera camera);

#endif //TEXT_H
