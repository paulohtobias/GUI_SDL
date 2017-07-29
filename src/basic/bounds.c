/**
  * Paulo Henrique Tobias
  * Manga Library
  *
  * Bounds
  * Basic functions and definitions for Position and Size.
  */

#include "basic/bounds.h"

///Constructor
//Creates a new Position from x and y coordinates.
Position new_Position(int x, int y){
    Position position;
    
    position.x = x;
    position.y = y;

    return position;
}

//Creates a new Size from width and height.
Size new_Size(int width, int height){
    Size size;

    size.w = width;
    size.h = height;

    return size;
}

//Creates a new Bounds from <code>Position</code> and <code>Size</code>.
Bounds new_Bounds(Position position, Size size){
    Bounds bounds;

    bounds.origin = position;
    bounds.camera = position;
    bounds.size = size;

    return bounds;
}

//Creates a new Bounds using integers from x, y, width and height.
Bounds new_Bounds_from_integer(int x, int y, int w, int h){
    return new_Bounds(new_Position(x, y), new_Size(w, h));
}

//Creates a new Bounds using an SDL_Rect struct.
Bounds new_Bounds_from_SDL_Rect(SDL_Rect rect){
    return new_Bounds_from_integer(
        rect.x,
        rect.y,
        rect.w,
        rect.h
    );
}

//Creates a new SDL_Rect struct.
SDL_Rect new_rect(int x, int y, int w, int h){
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}


///Extra
//Adds <code>p1</code> to <code>p2</code> and returns the result.
Position position_add(Position p1, Position p2){
    Position p3;
    p3.x = p1.x + p2.x;
    p3.y = p1.y + p2.y;
    return p3;
}

//Subtracts <code>p2</code> from <code>p1</code> and returns the result.
Position position_subtract(Position p1, Position p2){
    Position p3;
    p3.x = p1.x - p2.x;
    p3.y = p1.y - p2.y;
    return p3;
}


///Get
//Get the position relative to parent's origin.
Position get_position_origin(Bounds bounds){
    return bounds.origin;
}

//Get the position relative to the camera.
Position get_position_camera(Bounds bounds){
    return bounds.camera;
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

//Get camera position and size in form of SDL_Rect.
SDL_Rect get_bounds_camera(Bounds bounds){
    SDL_Rect rect;

    rect.x = bounds.camera.x;
    rect.y = bounds.camera.y;
    rect.w = bounds.size.w;
    rect.h = bounds.size.h;

    return rect;
}

//Get the size.
Size get_size(Bounds bounds){
    return bounds.size;
}


///Set
//Sets the new position relative to origin
void set_position_origin(Bounds *bounds, Position position){
    int camera_offset_x = bounds->camera.x - bounds->origin.x;
    int camera_offset_y = bounds->camera.y - bounds->origin.y;

    bounds->origin = position;
    bounds->camera = position;
    bounds->camera.x += camera_offset_x;
    bounds->camera.y += camera_offset_y;
}

//Set the position relative to camera. Origin position is <b>NOT</b> updated.
void set_position_camera(Bounds *bounds, Position position){
    bounds->camera = position;
}

//Set both origin and camera to the same value.
void reset_position(Bounds *bounds, Position position){
    bounds->origin = position;
    bounds->camera = position;
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

//Sets the new Position and Size of bounds_dst from a SDL_Rect struct.
void set_bounds_from_SDL_Rect(Bounds *bounds_dst, SDL_Rect bounds_src){
    Position position = new_Position(bounds_src.x, bounds_src.y);
    Size size = new_Size(bounds_src.w, bounds_src.h);

    set_position_origin(bounds_dst, position);
    set_size(bounds_dst, size);
}


///Update
//Update the origin position by adding the new values to the current position.
void update_position_origin(Bounds *bounds, Position position){
    Position new_pos = new_Position(
        bounds->origin.x + position.x,
        bounds->origin.y + position.y
    );

    set_position_origin(bounds, new_pos);
}

//Update the camera position by adding the new values to the current position.
void update_position_camera(Bounds *bounds, Position position){
    Position new_pos = new_Position(
        bounds->camera.x + position.x,
        bounds->camera.y + position.y
    );

    set_position_camera(bounds, new_pos);
}

//Update the size adding the new values to the current size.
void update_size(Bounds *bounds, Size size){
    Size new_size = new_Size(
        bounds->size.w + size.w,
        bounds->size.h + size.h
    );

    set_size(bounds, new_size);
}

//Updates the Position and Size of bounds_dst from a SDL_Rect struct.
void update_bounds(Bounds *bounds_dst, SDL_Rect bounds_src){
    Position position = new_Position(bounds_src.x, bounds_src.y);
    Size size = new_Size(bounds_src.w, bounds_src.h);
    
    update_position_origin(bounds_dst, position);
    update_size(bounds_dst, size);
}

//Update the SDL_Rect.
void update_rect(SDL_Rect *dst, SDL_Rect src){
    dst->x += src.x;
    dst->y += src.y;
    dst->w += src.w;
    dst->h += src.h;
}


///Reach
//Returns the end point of bounds in X using origin position.
int bounds_reach_x_origin(Bounds bounds){
    return bounds.origin.x + bounds.size.w;
}

//Returns the end point of bounds in Y using origin position.
int bounds_reach_y_origin(Bounds bounds){
    return bounds.origin.y + bounds.size.h;
}

//Returns the end point of bounds in X using camera position.
int bounds_reach_x_camera(Bounds bounds){
    return bounds.camera.x + bounds.size.w;
}

//Returns the end point of bounds in Y using camera position.
int bounds_reach_y_camera(Bounds bounds){
    return bounds.camera.y + bounds.size.h;
}

//Returns the end point of rect in X using origin position.
int rect_reach_x(SDL_Rect rect){
    return rect.x + rect.w;
}

//Returns the end point of rect in Y using origin position.
int rect_reach_y(SDL_Rect rect){
    return rect.y + rect.h;
}

//Check if point is inside the area covered by bounds using origin position.
bool position_is_inside_bounds_origin(Point point, Bounds bounds){
    return (point.x >= bounds.origin.x && point.x <= bounds_reach_x_origin(bounds) && //origin.x <= pos.x <= reach_x_origin
            point.y >= bounds.origin.y && point.y <= bounds_reach_y_origin(bounds));  //origin.y <= pos.y <= reach_y_origin
}

//Check if point is inside the area covered by bounds using camera position.
bool position_is_inside_bounds_camera(Point point, Bounds bounds){
    return (point.x >= bounds.camera.x && point.x <= bounds_reach_x_camera(bounds) && //camera.x <= pos.x <= reach_x_camera
            point.y >= bounds.camera.y && point.y <= bounds_reach_y_camera(bounds));  //camera.y <= pos.y <= reach_y_camera
}

//Check if point is inside the area covered by SDL_Rect.
bool position_is_inside_rect(Point point, SDL_Rect rect){
    return (point.x >= rect.x && point.x <= rect_reach_x(rect) && //rect.x <= pos.x <= rect_reach_x
            point.y >= rect.y && point.y <= rect_reach_y(rect));  //rect.y <= pos.y <= rect_reach_y
}

//Checks if the area covered by rect1 is inside the area covered by rect2.
bool rect_is_inside_rect(SDL_Rect rect1, SDL_Rect rect2){
    return (rect1.x >= rect2.x && rect1.y >= rect2.y &&
            rect_reach_x(rect1) < rect_reach_x(rect2) && rect_reach_y(rect1) < rect_reach_y(rect2));
}

//Checks if the area covered by bounds1 using origin position is inside the area
//covered by bounds2 using origin position.
bool bounds_origin_is_inside_bounds_origin(Bounds bounds1, Bounds bounds2){
    return (rect_is_inside_rect(get_bounds_origin(bounds1), get_bounds_origin(bounds2)));
}

//Checks if the area covered by bounds1 using origin position is inside the area
//covered by bounds2 using camera position.
bool bounds_origin_is_inside_bounds_camera(Bounds bounds1, Bounds bounds2){
    return (rect_is_inside_rect(get_bounds_origin(bounds1), get_bounds_camera(bounds2)));
}

//Checks if the area covered by bounds1 using camera position is inside the area
//covered by bounds2 using origin position.
bool bounds_camera_is_inside_bounds_origin(Bounds bounds1, Bounds bounds2){
    return (rect_is_inside_rect(get_bounds_camera(bounds1), get_bounds_camera(bounds2)));
}

//Checks if the area covered by bounds1 using camera position is inside the area
//covered by bounds2 using camera position.
bool bounds_camera_is_inside_bounds_caemera(Bounds bounds1, Bounds bounds2){
    return (rect_is_inside_rect(get_bounds_camera(bounds1), get_bounds_camera(bounds2)));
}