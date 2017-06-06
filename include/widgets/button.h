/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Button
 * Button library using SDL2
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "widgets/frame.h"
#include "widgets/text.h"
#include "widgets/image.h"

#define default_button_borderSize 1
#define default_button_textColor_idle COLOR_BLACK
#define default_button_textColor_focused COLOR_BLACK
#define default_button_textColor_pressed COLOR_BLACK
#define default_button_textColor_disabled COLOR_GREY(131)
#define default_button_frameColor_idle COLOR_GREY(225)
#define default_button_frameColor_focused COLOR_GREY(225)
#define default_button_frameColor_pressed COLOR_RGB(204, 228, 247)
#define default_button_frameColor_disabled COLOR_GREY(204)
#define default_button_borderColor_idle COLOR_GREY(173)
#define default_button_borderColor_focused COLOR_RGB(0, 120, 215)
#define default_button_borderColor_pressed COLOR_RGB(0, 84, 153)
#define default_button_borderColor_disabled COLOR_GREY(191)

struct Button_{
	Frame frame;
	Text txt;
	Image img;

	//Color
	//Text
	SDL_Color buttonColorTextIdle;
	SDL_Color buttonColorTextFocused;
	SDL_Color buttonColorTextPressed;
	SDL_Color buttonColorTextDisabled;
	//Frame
	SDL_Color buttonColorIdle;
	SDL_Color buttonColorFocused;
	SDL_Color buttonColorPressed;
	SDL_Color buttonColorDisabled;
	//Border
	SDL_Color buttonColorBorderIdle;
	SDL_Color buttonColorBorderFocused;
	SDL_Color buttonColorBorderPressed;
	SDL_Color buttonColorBorderDisabled;

	Bounds region;
	WidgetState state;
};
typedef struct Button_* Button;

Button newButton(char *text, char *img_path, SDL_Rect size);
void init_button(Button btn, SDL_Renderer *renderer);
void freeButton(Button btn);

//Get
int button_getBorderSize(Button  btn);
SDL_Rect button_getBounds(Button btn);

//Set and Update
void button_setBorderSize(Button btn, int borderSize);
void button_setBounds(Button btn, SDL_Rect region);
void button_updateBounds(Button btn, SDL_Rect region);
void button_Idle(Button btn);
void button_Focus(Button btn);
void button_Press(Button btn);
//button_Activate(Button btn);
//button_Deactivate(Button btn);
void button_setColorIdle(Button  btn, SDL_Color text, SDL_Color frame, SDL_Color border);
void button_setColorFocused(Button  btn, SDL_Color text, SDL_Color frame, SDL_Color border);
void button_setColorPressed(Button  btn, SDL_Color text, SDL_Color frame, SDL_Color border);
void button_setColorDisabled(Button  btn, SDL_Color text, SDL_Color frame, SDL_Color border);

//Events
void button_processEvents(SDL_Event event, Mouse mouseState, Button btn);
bool button_isFocused(Button btn);
bool button_isPressed(Button btn);
bool button_isReleased(Button btn);
bool button_isDragged(Button btn);
//bool button_isActive(Button btn);

//Render
void renderButton(Button btn, SDL_Renderer *renderer, Camera camera);

#endif //BUTTON_H
