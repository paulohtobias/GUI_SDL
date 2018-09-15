#include "camera.h"

Camera new_Camera(SDL_Rect bounds){
	Camera camera;

	camera.viewport = camera.bounds = camera.limit = bounds;
	camera.__position = camera.position = camera.speed = new_Vector2(0, 0);
	camera.mov_speed = default_camera_speed;
	camera.__update_limit = SDL_FALSE;

	return camera;
}

SDL_Rect camera_get_relative_bounds(Camera *camera, SDL_Rect bounds){
	if (camera != NULL) {
		int px = camera->position.x + camera->__position.x;
		int py = camera->position.y + camera->__position.y;
		bounds.x = camera->viewport.x + (bounds.x - camera->limit.x) - px;
		bounds.y = camera->viewport.y + (bounds.y - camera->limit.y) - py;
	}

	return bounds;
}

SDL_Rect camera_get_drawable_area(Camera *camera, SDL_Rect *dst_bounds){
	SDL_Rect draw_area = *dst_bounds;
	draw_area.x = draw_area.y = 0;
	
	if (camera != NULL) {
		//Up and Left
		int x_offset = MAX(0, camera->viewport.x - dst_bounds->x);
		int y_offset = MAX(0, camera->viewport.y - dst_bounds->y);
		
		draw_area.x = x_offset;
		draw_area.y = y_offset;
		draw_area.w -= x_offset;
		draw_area.h -= y_offset;

		dst_bounds->x += x_offset;
		dst_bounds->y += y_offset;
		dst_bounds->w = MAX(0, dst_bounds->w - draw_area.x);
		dst_bounds->h = MAX(0, dst_bounds->h - draw_area.y);


		//Down and Right
		int rcx, rcy;
		int w_offset = MAX(0, rect_reach_x(*dst_bounds) - rect_reach_x(camera->viewport));
		int h_offset = MAX(0, rect_reach_y(*dst_bounds) - rect_reach_y(camera->viewport));	
		
		draw_area.w -= w_offset;
		draw_area.h -= h_offset;
		dst_bounds->w = MAX(0, dst_bounds->w - w_offset);
		dst_bounds->h = MAX(0, dst_bounds->h - h_offset);
	}

	return draw_area;
}

void __camera_set_update_limit(Camera *camera, SDL_bool update_limit) {
	if (camera != NULL) {
		camera->__update_limit = update_limit;
	}
}

void camera_set_bounds(Camera *camera, SDL_Rect bounds){
	camera->viewport = camera->bounds = bounds;
	
	//Checking if the new bounds is greater than the limit.
	camera_update_limit(camera, camera->bounds);

	camera->__position = camera->position = new_Position(0, 0);
}

void camera_update_limit(Camera *camera, SDL_Rect bounds){
	if(bounds.x < camera->limit.x){
		camera->limit.x = bounds.x;
	}
	
	if(bounds.y < camera->limit.y){
		camera->limit.y = bounds.y;
	}
	
	int brx = rect_reach_x(bounds);
	int lrx = rect_reach_x(camera->limit);
	if(brx > lrx){
		camera->limit.w += brx - lrx;
	}
	
	int bry = rect_reach_y(bounds);
	int lry = rect_reach_y(camera->limit);
	if(bry > lry){
		camera->limit.h += (bry - lry);
	}

	//camera->position = new_Position(0, 0);
}

void camera_process_events(Camera *camera, SDL_Event event){
	//TO-DO: A way to process key events from the active camera even if mouse_over == false
	if (mouse_over_rect(camera->viewport) && camera_active == NULL) {
		//Set the active camera.
		camera_active = camera;
		
		switch(event.type){
			case SDL_MOUSEWHEEL:
				camera->speed.y -= event.wheel.y * camera->mov_speed;
				camera->speed.x -= event.wheel.x * camera->mov_speed;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_UP:
						camera->speed.y -= camera->mov_speed;
						break;
					case SDLK_DOWN:
						camera->speed.y += camera->mov_speed;
						break;
					case SDLK_HOME:
						camera->speed.y = -camera->position.y;
						break;
					case SDLK_END:
						camera->speed.y = camera->limit.h - (camera->position.y + camera->bounds.h);
						break;
					case SDLK_PAGEUP:
						camera->speed.y = -camera->bounds.h;
						break;
					case SDLK_PAGEDOWN:
						camera->speed.y = camera->bounds.h;
						break;
				}
				break;
			default:
				camera->speed.x = 0;
				camera->speed.y = 0;
				break;
		}
	}
}

void camera_set_x_speed(Camera *camera, int x_speed){
	camera->speed.x = x_speed;
}

void camera_set_y_speed(Camera *camera, int y_speed){
	camera->speed.y = y_speed;
}

void camera_set_speed(Camera *camera, Vector2 speed){
	camera->speed = speed;
}

void camera_move(Camera *camera){
	camera->position.x += camera->speed.x;
	camera->position.y += camera->speed.y;

	camera->speed = new_Vector2(0, 0);

	//Checking if position is out of bounds (upper-left).
	if(camera->position.x < 0){
		camera->position.x = 0;
	}
	if(camera->position.y < 0){
		camera->position.y = 0;
	}

	//Checking if position is out of bounds (bottom-right).
	if((camera->position.x + camera->bounds.w) > camera->limit.w){
		camera->position.x = camera->limit.w - camera->bounds.w;
	}
	if((camera->position.y + camera->bounds.h) > camera->limit.h){
		camera->position.y = camera->limit.h - camera->bounds.h;
	}
}
