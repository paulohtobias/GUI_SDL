/**
  * Paulo Henrique Tobias
  * Manga Library
  *
  * Bounds
  * Basic functions and definitions for Position and Size.
  */

#include "basic/bounds.h"

///Constructor
Position new_Position(int x, int y){
    Position position;
    
    position.x = x;
    position.y = y;

    return position;
}
Size new_Size(int width, int height){
    Size size;

    size.w = width;
    size.h = height;

    return size;
}
Bounds new_Bounds(Position position, Size size){
    Bounds bounds;

    bounds.origin = position;
    bounds.camera = position;
    bounds.size = size;

    return bounds;
}
Bounds new_Bounds_integer(int x, int y, int w, int h){
    return new_Bounds(new_Position(x, y), new_Size(w, h));
}
SDL_Rect new_rect(int x, int y, int w, int h){
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}

///Get
//Return the position relative to the camera.
Position get_position_camera(Bounds bounds){
    return bounds.camera;
}

//Get the position relative to parent's origin.
Position get_position_origin(Bounds bounds){
    return bounds.origin;
}

//Get camera position and size in form of SDL_Rect.
SDL_Rect get_bounds_camera(Bounds bounds){
    SDL_Rect rect;

    rect.x = bounds.camera.x;
    rect.y = bounds.camera.y;
    rect.w = bounds.size.w;
    rect.h = bounds.size.h;

    return rect;
}

//Get origin position and size in form of SDL_Rect.
SDL_Rect get_bounds_origin(Bounds bounds){
    SDL_Rect rect;

    rect.x = bounds.origin.x;
    rect.y = bounds.origin.y;
    rect.w = bounds.size.w;
    rect.h = bounds.size.h;

    return rect;
}

//Get the size.
Size get_size(Bounds bounds){
    return bounds.size;
}


///Set
//Set the position relative to origin. Camera position is updated.
void set_position(Bounds *bounds, Position position){
    int x_offset = bounds->camera.x - bounds->origin.x;
    int y_offset = bounds->camera.y - bounds->origin.y;

    bounds->origin = position;
    bounds->camera = position;
    bounds->camera.x += x_offset;
    bounds->camera.y += y_offset;
}

//Set the size.
void set_size(Bounds *bounds, Size size){
    if(size.w > 0){
        bounds->size.w = size.w;
    }
    if(size.h > 0){
        bounds->size.h = size.h;
    }
}

//Set Position and Size.
void set_bounds(Bounds *bounds_dst, SDL_Rect bounds_src){
    Position position = new_Position(bounds_src.x, bounds_src.y);
    Size size = new_Size(bounds_src.w, bounds_src.h);

    set_position(bounds_dst, position);
    set_size(bounds_dst, size);
}


///Update
//Update the position adding the new values to the current position.
void update_position(Bounds *bounds, Position position){
    Position new_pos = new_Position(bounds->origin.x + position.x, bounds->origin.y + position.y);

    set_position(bounds, new_pos);
}

//Update the size adding the new values to the current size.
void update_size(Bounds *bounds, Size size){
    Size new_size = new_Size(bounds->size.w + size.w, bounds->size.h + size.h);

    set_size(bounds, new_size);
}

//Update Position and Size.
void update_bounds(Bounds *bounds_dst, SDL_Rect bounds_src){
    update_position(bounds_dst, new_Position(bounds_src.x, bounds_src.y));
    update_size(bounds_dst, new_Size(bounds_src.w, bounds_src.h));
}
