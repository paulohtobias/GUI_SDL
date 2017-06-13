/**
  * Paulo Henrique Tobias
  * Manga Library
  *
  * Bounds
  * Basic functions and definitions for Position and Size.
  */

#ifndef BOUNDS_H
#define BOUNDS_H

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
    Position origin;    //Position relative to parent's origin.
    Position camera;    //Position relative to parent's camera (this will be the used in most cases).
    Size size;
}Bounds;

///Constructor
Position new_Position(int x, int y);
Size new_Size(int width, int height);
Bounds new_Bounds(Position position, Size size);
Bounds new_Bounds_integer(int x, int y, int w, int h);
SDL_Rect new_rect(int x, int y, int w, int h);

///Get
//Return the position relative to the camera.
Position get_position_camera(Bounds bounds);
#define get_position get_position_camera

//Get the position relative to parent's origin.
Position get_position_origin(Bounds bounds);

//Get camera position and size in form of SDL_Rect.
SDL_Rect get_bounds_camera(Bounds bounds);
#define get_bounds get_bounds_camera

//Get origin position and size in form of SDL_Rect.
SDL_Rect get_bounds_origin(Bounds bounds);

//Get the size.
Size get_size(Bounds bounds);


///Set
//Set the position relative to origin. Camera position is updated.
void set_position(Bounds *bounds, Position position);

//Set the size.
void set_size(Bounds *bounds, Size size);

//Set Position and Size.
void set_bounds(Bounds *bounds_dst, SDL_Rect bounds_src);


///Update
//Update the position adding the new values to the current position.
void update_position(Bounds *bounds, Position position);

//Update the size adding the new values to the current size.
void update_size(Bounds *bounds, Size size);

//Update Position and Size.
void update_bounds(Bounds *bounds_dst, SDL_Rect bounds_src);

#endif //BOUNDS_H
