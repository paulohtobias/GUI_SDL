#ifndef BORDER_H
#define BORDER_H

#include "basic/bounds.h"
#include "basic/color.h"

typedef struct VT_Border{
	void (*free)(void *);
	void (*set_bounds)(void *, SDL_Rect);
	void (*draw)(void *, SDL_Renderer *);
}VT_Border;

/**
 * Information about a border's style.
 */
typedef struct Border{
    Uint8 size_up;
    Uint8 size_down;
    Uint8 size_right;
    Uint8 size_left;
    Color color;
	SDL_Rect bounds;
	//TO-DO: a value to draw only the border or the whole rectangle
	
	//Functions
	VT_Border *functions;
}Border;

Border new_Border(int size, Color color, SDL_Rect widget_bounds);

Border new_Border_all(int size_up, int size_down, int size_right, int size_left,
				  Color color, SDL_Rect widget_bounds);

Border *new_Border_dynamic(int size, Color color, SDL_Rect widget_bounds);

Border *new_Border_all_dynamic(int size_up, int size_down, int size_right, int size_left,
				  Color color, SDL_Rect widget_bounds);

void border_free(void *border);

void border_set_bounds(void *border, SDL_Rect widget_bounds);

void border_draw(void *border, SDL_Renderer *renderer);


void __border_free(void *__border);

void __border_set_bounds(void *__border, SDL_Rect widget_bounds);

void __border_draw(void *__border, SDL_Renderer *renderer);

//TO-DO: create a border draw function that draws only the border.

#endif /* BORDER_H */
