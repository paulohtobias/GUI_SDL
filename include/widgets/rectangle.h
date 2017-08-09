#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "texture_widget.h"

typedef TextureWidget Rectangle;

Rectangle new_Rectangle(Color color);

Rectangle new_Rectangle_with_position(Color color, Position position);

Rectangle new_Rectangle_with_bounds(Color color, SDL_Rect bounds);

void generic_rectangle_set_bounds(void *raw_rectangle, SDL_Rect bounds);

void generic_rectangle_update(void *raw_rectangle, SDL_Renderer *renderer);

#endif //RECTANGLE_H
