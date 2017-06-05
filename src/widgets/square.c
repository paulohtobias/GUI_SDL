/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Square
 * Square library using SDL2
 */

#include "widgets/square.h"

Square newSquare(SDL_Color color, SDL_Rect bounds){
	Square sqr = malloc(sizeof(struct Square_));

	sqr->color = color;
	resetBounds(&sqr->region, bounds);
	square_setBounds(sqr, bounds);
	sqr->state = newWidgetState();

	return sqr;
}
void freeSquare(Square sqr){
	free(sqr);
}

//Get
SDL_Rect square_getBounds(Square sqr){
	return getBounds(sqr->region);
}

//Set and Update
void square_setColor(Square sqr, SDL_Color color){
	sqr->color = color;
}
void square_setBounds(Square sqr, SDL_Rect region){
	setBounds(&sqr->region, region);
}
void square_updateBounds(Square sqr, SDL_Rect region){
	updateBounds(&sqr->region, region);
}

//Events
void square_processEvents(SDL_Event event, Mouse mouseState, Square sqr){
	basic_widget_processEvents(event, mouseState, &sqr->state, sqr->region);
	if(square_isDragged(sqr)){
		square_updateBounds(sqr, widget_dragPosition(mouseState));
	}
}
bool square_isFocused(Square sqr){
	return widget_isFocused(sqr->state);
}
bool square_isPressed(Square sqr){
	return widget_isPressed(sqr->state);
}
bool square_isReleased(Square sqr){
	return widget_isReleased(sqr->state);
}
bool square_isDragged(Square sqr){
	return widget_isDragged(sqr->state);
}

//Render
void renderSquare(Square sqr, SDL_Renderer *renderer, Camera camera){
	camera_updateWidgetPosition(camera, &sqr->region);
	if( !camera_widget_is_off(camera, square_getBounds(sqr)) ){
        SetRenderDrawColor(renderer, sqr->color);
        SDL_RenderFillRect(renderer, &sqr->region.relative);
    }
}
