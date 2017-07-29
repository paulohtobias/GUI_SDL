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

#ifndef TYPE_BOOL
#define TYPE_BOOL
typedef int bool;
#define false 0
#define true 1
#endif //MOUSE_BOOL

typedef enum MouseButtonState_{
    MOUSE_IDLE,
    MOUSE_LEFT_PRESSED,
    MOUSE_RIGHT_PRESSED,
    MOUSE_MIDDLE_PRESSED,
    MOUSE_LEFT_RELEASED,
    MOUSE_RIGHT_RELEASED,
    MOUSE_MIDDLE_RELEASED
}MouseButtonState;

typedef struct Mouse_{
    MouseButtonState button_state;
    Position position;
    Position drag_offset;
}Mouse;

//Return the mouse position on the screen.
Position mouse_get_position();

//Check if the mouse is pressed. If the mouse is indeed pressed, then return which button.
//Returns 0 (mouse_idle) otherwise.
MouseButtonState mouse_is_pressed(Mouse mouse);

//Check if the mouse is released. If the mouse is indeed pressed, then return which button.
//Returns 0 (mouse_idle) otherwise.
MouseButtonState mouse_is_released(Mouse mouse);

//Check if the mouse is inside the area of bounds.
bool mouse_over(Bounds bounds);
bool mouse_over_rect(SDL_Rect bounds);

#endif //MOUSE_H
