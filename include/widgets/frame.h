/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Frame
 * Frame library using SDL2
 */

#ifndef FRAME_H
#define FRAME_H

#include "widgets/basicUI.h"
#include "widgets/square.h"

struct Frame_{
	Square border;
	int borderSize;
	Square frame;

	Bounds region;
	WidgetState state;
};
typedef struct Frame_* Frame;

Frame newFrame(SDL_Color frameColor, SDL_Color borderColor, int borderSize, SDL_Rect size);
void freeFrame(Frame frame);

//Get
SDL_Color frame_getColor(Frame frame);
SDL_Color frame_getBorderColor(Frame frame);
SDL_Rect frame_getBounds(Frame frame);

//Set and Update
void frame_setColor(Frame frame, SDL_Color color);
void frame_setBorderColor(Frame frame, SDL_Color color);
void frame_setBorderSize(Frame frame, int borderSize);
void frame_setBounds(Frame frame, SDL_Rect region);
void frame_updateBounds(Frame frame, SDL_Rect region);

//Events
void frame_processEvents(SDL_Event event, Mouse mouseState, Frame frame);
bool frame_isFocused(Frame frame);
bool frame_isPressed(Frame frame);
bool frame_isReleased(Frame frame);
bool frame_isDragged(Frame frame);

//Render
void renderFrame(Frame frame, SDL_Renderer *renderer, Camera camera);

#endif //FRAME_H
