#include "basic/mouse.h"

//Return the mouse position on the screen.

Position mouse_get_position(){
	Position mouse_position;
	SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
	return mouse_position;
}

//Check if the mouse is pressed. If the mouse is indeed pressed, then return which button.
//Returns 0 (mouse_idle) otherwise.

MouseButtonState mouse_is_pressed(Mouse mouse){
	if(mouse.button_state >= MOUSE_LEFT_PRESSED && mouse.button_state <= MOUSE_MIDDLE_PRESSED){
		return mouse.button_state;
	}else{
		return 0;
	}
}

//Check if the mouse is released. If the mouse is indeed pressed, then return which button.
//Returns 0 (mouse_idle) otherwise.

MouseButtonState mouse_is_released(Mouse mouse){
	if(mouse.button_state >= MOUSE_LEFT_RELEASED && mouse.button_state <= MOUSE_MIDDLE_RELEASED){
		return mouse.button_state;
	}else{
		return 0;
	}
}

//Check if the mouse is inside the area of bounds.

bool mouse_over(Bounds bounds){
	return position_is_inside_bounds_camera(mouse_get_position(), bounds);
}

bool mouse_over_rect(SDL_Rect bounds){
	return position_is_inside_rect(mouse_get_position(), bounds);
}
