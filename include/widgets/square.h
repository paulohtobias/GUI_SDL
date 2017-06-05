/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Square
 * Square library using SDL2
 */

#ifndef SQUARE_H
#define SQUARE_H

#include "widgets/basicUI.h"

struct Square_{
	SDL_Color color;
	Bounds region;
	WidgetState state;
};
typedef struct Square_* Square;

Square newSquare(SDL_Color color, SDL_Rect bounds);
void freeSquare(Square sqr);

//Get
SDL_Rect square_getBounds(Square sqr);

//Set and Update
void square_setColor(Square sqr, SDL_Color color);
void square_setBounds(Square sqr, SDL_Rect region);
void square_updateBounds(Square sqr, SDL_Rect region);

//Events
void square_processEvents(SDL_Event event, Mouse mouseState, Square sqr);
bool square_isFocused(Square sqr);
bool square_isPressed(Square sqr);
bool square_isReleased(Square sqr);
bool square_isDragged(Square sqr);

//Render
void renderSquare(Square sqr, SDL_Renderer *renderer, Camera camera);

#endif //SQUARE_H
