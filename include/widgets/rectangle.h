#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "texture_widget.h"

typedef struct Rectangle{
	TextureWidget t_widget;
	
	Color color;
}Rectangle;

Rectangle new_Rectangle(Color color);

Rectangle new_Rectangle_with_position(Color color, Position position);

Rectangle new_Rectangle_with_bounds(Color color, SDL_Rect bounds);


void __rectangle_set_bounds(void *__rectangle, SDL_Rect bounds);

void __rectangle_update(void *__rectangle, SDL_Renderer *renderer);

#endif //RECTANGLE_H
