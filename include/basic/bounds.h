/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Bounds
 * Basic functions and definitions for Position and Size.
 */

#ifndef BOUNDS_H
#define BOUNDS_H

#include <stdlib.h>
#include <SDL2/SDL.h>

#ifndef TYPE_BOOL
#define TYPE_BOOL
	typedef int bool;
	#define false 0
	#define true 1
#endif //MOUSE_BOOL

typedef struct Point_{
    int x;
    int y;
}Point;

typedef Point Position;
typedef Point Vector2;

typedef struct Size_{
    int w;  //Width
    int h;  //Height
}Size;

typedef struct Bounds_{
    Position origin;    //Position relative to parent's origin. (Use when calculating position relative to other widgets)
    Position camera;    //Position relative to parent's camera. (this will be the used in most cases)
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


///Reach
//Returns the end point of bounds in X plus camera offset.
int bounds_reach_x_camera(Bounds bounds);
//Returns the end point of bounds in Y plus camera offset.
int bounds_reach_y_camera(Bounds bounds);
#define bounds_reach_x bounds_reach_x_camera
#define bounds_reach_y bounds_reach_y_camera

//Returns the end point of bounds in X.
int bounds_reach_x_origin(Bounds bounds);
//Returns the end point of bounds in Y.
int bounds_reach_y_origin(Bounds bounds);

//Returns the end point of SDL_Rect in X.
int rect_reach_x(SDL_Rect rect);
//Returns the end point of SDL_Rect in Y.
int rect_reach_y(SDL_Rect rect);

//Check if position is inside the area covered by bounds using camera offset.
bool position_is_inside_bounds_camera(Position position, Bounds bounds);
#define position_is_inside_bounds position_is_inside_bounds_camera

//Check if position is inside the area covered by bounds using parent's origin.
bool position_is_inside_bounds_origin(Position position, Bounds bounds);

//Check if position is inside the area covered by SDL_Rect.s
bool position_is_inside_rect(Position position, SDL_Rect rect);

#endif //BOUNDS_H
