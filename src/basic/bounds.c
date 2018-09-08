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

	bounds.local = position;
	bounds.global = position;
	bounds.size = size;

	return bounds;
}

Bounds new_Bounds_from_integer(int x, int y, int w, int h){
	return new_Bounds(new_Position(x, y), new_Size(w, h));
}

Bounds new_Bounds_from_SDL_Rect(SDL_Rect rect){
	return new_Bounds_from_integer(
		rect.x,
		rect.y,
		rect.w,
		rect.h
	);
}

SDL_Rect new_rect(int x, int y, int w, int h){
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	return rect;
}


///Operations
Position position_add(Position p1, Position p2){
	Position p3;
	
	p3.x = p1.x + p2.x;
	p3.y = p1.y + p2.y;
	
	return p3;
}

Position position_subtract(Position p1, Position p2){
	Position p3;
	
	p3.x = p1.x - p2.x;
	p3.y = p1.y - p2.y;
	
	return p3;
}

SDL_Rect rect_add(SDL_Rect rect1, SDL_Rect rect2){
	return new_rect(
	    rect1.x + rect2.x,
	    rect1.y + rect2.y,
	    rect1.w + rect2.w,
	    rect1.h + rect2.h
	);
}


///Get
SDL_Rect get_bounds_local(Bounds bounds){
	SDL_Rect rect;

	rect.x = bounds.local.x;
	rect.y = bounds.local.y;
	rect.w = bounds.size.w;
	rect.h = bounds.size.h;

	return rect;
}

SDL_Rect get_bounds_global(Bounds bounds){
	SDL_Rect rect;

	rect.x = bounds.global.x;
	rect.y = bounds.global.y;
	rect.w = bounds.size.w;
	rect.h = bounds.size.h;

	return rect;
}


///Set
void bounds_set_position_local(Bounds *bounds, Position position){
	Position offset = position_subtract(position, bounds->local);

	bounds->local = position;
	bounds->global.x += offset.x;
	bounds->global.y += offset.y;
}

void bounds_set_position_global(Bounds *bounds, Position position){
	Position offset = position_subtract(position, bounds->global);

	bounds->global = position;
	bounds->local.x += offset.x;
	bounds->local.y += offset.y;
}

void bounds_set_size(Bounds *bounds, Size size){
	if(size.w > 0){
		bounds->size.w = size.w;
	}
	if(size.h > 0){
		bounds->size.h = size.h;
	}
}

void set_bounds_from_SDL_Rect(Bounds *bounds_dst, SDL_Rect bounds_src){
	Position position = new_Position(bounds_src.x, bounds_src.y);
	Size size = new_Size(bounds_src.w, bounds_src.h);

	bounds_set_position_local(bounds_dst, position);
	bounds_set_size(bounds_dst, size);
}


///Update
void bounds_update_position(Bounds *bounds, Position position){
	bounds->local.x += position.x;
	bounds->local.y += position.y;
	bounds->global.x += position.x;
	bounds->global.y += position.y;
}

void bounds_update_size(Bounds *bounds, Size size){
	Size new_size = new_Size(
	    bounds->size.w + size.w,
	    bounds->size.h + size.h
	);

	bounds_set_size(bounds, new_size);
}

void update_bounds(Bounds *bounds_dst, SDL_Rect bounds_src){
	Position position = new_Position(bounds_src.x, bounds_src.y);
	Size size = new_Size(bounds_src.w, bounds_src.h);

	bounds_update_position(bounds_dst, position);
	bounds_update_size(bounds_dst, size);
}

void update_rect(SDL_Rect *dst, SDL_Rect src){
	dst->x += src.x;
	dst->y += src.y;
	
	int value = dst->w + src.w;
	if (value > 0) {
		dst->w = value;
	}
	
	value = dst->h + src.h;
	if (value > 0) {
		dst->h = value;
	}
}


///Reach
int bounds_reach_x_local(Bounds bounds){
	return bounds.local.x + bounds.size.w;
}

int bounds_reach_y_local(Bounds bounds){
	return bounds.local.y + bounds.size.h;
}

int bounds_reach_x_global(Bounds bounds){
	return bounds.global.x + bounds.size.w;
}

int bounds_reach_y_global(Bounds bounds){
	return bounds.global.y + bounds.size.h;
}

int rect_reach_x(SDL_Rect rect){
	return rect.x + rect.w;
}

int rect_reach_y(SDL_Rect rect){
	return rect.y + rect.h;
}


///Area
SDL_bool position_is_inside_bounds_local(Point point, Bounds bounds){
	return (point.x >= bounds.local.x && point.x <= bounds_reach_x_local(bounds) && //origin.x <= pos.x <= reach_x_origin
		point.y >= bounds.local.y && point.y <= bounds_reach_y_local(bounds)); //origin.y <= pos.y <= reach_y_origin
}

SDL_bool position_is_inside_bounds_global(Point point, Bounds bounds){
	return (point.x >= bounds.global.x && point.x <= bounds_reach_x_global(bounds) && //camera.x <= pos.x <= reach_x_camera
		point.y >= bounds.global.y && point.y <= bounds_reach_y_global(bounds)); //camera.y <= pos.y <= reach_y_camera
}

SDL_bool position_is_inside_rect(Point point, SDL_Rect rect){
	return (point.x >= rect.x && point.x <= rect_reach_x(rect) && //rect.x <= pos.x <= rect_reach_x
		point.y >= rect.y && point.y <= rect_reach_y(rect)); //rect.y <= pos.y <= rect_reach_y
}

SDL_bool rect_is_inside_rect(SDL_Rect rect1, SDL_Rect rect2){
	return (rect1.x >= rect2.x && rect1.y >= rect2.y &&
		rect_reach_x(rect1) < rect_reach_x(rect2) && rect_reach_y(rect1) < rect_reach_y(rect2));
}

SDL_bool rect_intersects_rect(SDL_Rect rect1, SDL_Rect rect2){
	return !(rect_reach_x(rect1) < rect2.x || rect_reach_y(rect1) < rect2.y ||
	         rect_reach_x(rect2) < rect1.x || rect_reach_y(rect2) < rect1.y);
}

SDL_bool bounds_is_inside_bounds(Bounds bounds1, Bounds bounds2){
	return (rect_is_inside_rect(get_bounds_global(bounds1), get_bounds_global(bounds2)));
}

SDL_Rect bounds_get_center(Size size, SDL_Rect area){
	SDL_Rect center_bounds;

	center_bounds.x = area.x + (area.w / 2) - (size.w / 2);
	center_bounds.y = area.y + (area.h / 2) - (size.h / 2);
	center_bounds.w = size.w;
	center_bounds.h = size.h;

	return center_bounds;
}
