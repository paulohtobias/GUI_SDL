/**
  * Paulo Henrique Tobias
  * Manga Library
  *
  * Region
  * Basic functions and definitions for Position and Size.
  */

#ifndef REGION_H
#define REGION_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifndef TYPE_BOOL
#define TYPE_BOOL
	typedef int bool;
	#define false 0
	#define true 1
#endif //TYPE_BOOL

typedef struct Position_{
    int x;
    int y;
}Position;

typedef struct Size_{
    int w;  //Width
    int h;  //Height
}Size;

typedef struct Bounds_{
    Position camera;    //Position relative to parent's camera (this will be the used in most cases).
    Position origin;    //Position relative to parent's origin.
    Size size;
}Bounds;

///Contructor
//TO-DO: create various forms of creating new Bounds here.

///Get
//Return the position relative to the camera.
Position get_relative_position(Bounds bounds);
#define get_position get_position

//Get the position relative to parent's origin.
Position get_real_position(Bounds bounds);

//Get the size.
Size get_size(Bounds bounds);

//Get camera position and size in form of SDL_Rect.
SDL_Rect get_bounds(Bounds bounds);


///Set
//Set the position relative to origin. Camera position is updated.
void set_position(Bounds *bounds, Position position);

//Set the size.
void set_size(Bounds *bounds, Size size);

//Set Position and Size.
void set_bounds(Bounds *bounds_dst, SDL_Rect bounds_src);

//Update

#endif //REGION_H
