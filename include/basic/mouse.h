/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Mouse
 * Basic functions and definitions for mouse.
 */

#ifndef MOUSE_H
#define MOUSE_H

#include "basic/bounds.h"

typedef enum MouseButtonState{
	MOUSE_IDLE,
	MOUSE_LEFT_PRESSED,
	MOUSE_RIGHT_PRESSED,
	MOUSE_MIDDLE_PRESSED,
	MOUSE_LEFT_RELEASED,
	MOUSE_RIGHT_RELEASED,
	MOUSE_MIDDLE_RELEASED
} MouseButtonState;

typedef struct Mouse{
	MouseButtonState button_state;
	Position position;
	Position drag_offset;
} Mouse;

//Return the mouse position on the screen.
Position mouse_get_position();

//Check if the mouse is pressed. If the mouse is indeed pressed, then return which button.
//Returns 0 (mouse_idle) otherwise.
MouseButtonState mouse_is_pressed(Mouse mouse);

//Check if the mouse is released. If the mouse is indeed pressed, then return which button.
//Returns 0 (mouse_idle) otherwise.
MouseButtonState mouse_is_released(Mouse mouse);

//Check if the mouse is inside the area of bounds.
SDL_bool mouse_over(Bounds bounds);
SDL_bool mouse_over_rect(SDL_Rect bounds);

#endif //MOUSE_H
