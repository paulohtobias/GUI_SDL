#include "camera.h"

//Creates a new Camera.
Camera *new_Camera(SDL_Rect limit){
	Camera *camera = malloc(sizeof(Camera));

	camera->bounds = camera->limit = limit;
	camera->mov_speed = default_camera_speed;
	camera->speed = new_Vector2(0, 0);

	return camera;
}

//Frees camera from memory.
void free_Camera(Camera *camera){
	free(camera);
}

//Returns the distance of camera's position to its limit position.
Position camera_get_position(Camera *camera){
	Position position;
	position.x = camera->bounds.x - camera->limit.x;
	position.y = camera->bounds.y - camera->limit.y;
	return position;
}

//Returns the position and size of camera.
SDL_Rect camera_get_bounds(Camera *camera){
	return camera->bounds;
}

//Sets a new position and size for the camera.
void camera_set_bounds(Camera *camera, SDL_Rect bounds){
	//Setting the X position.
	camera->bounds.x = bounds.x;
	//Checking if the new bounds is greater than the limit.
	if(camera->bounds.x > camera->limit.x){
		camera->limit.x = camera->bounds.x;
	}

	//Setting the Y position.
	camera->bounds.y = bounds.y;
	//Checking if the new bounds is greater than the limit.
	if(camera->bounds.y > camera->limit.y){
		camera->limit.y = camera->bounds.y;
	}

	//Setting the width.
	if(bounds.w > 0){
		camera->bounds.w = bounds.w;
	}
	//Checking if the new bounds is greater than the limit.
	if(rect_reach_x(camera->bounds) > rect_reach_x(camera->limit)){
		camera->limit.w = rect_reach_x(camera->bounds);
	}

	//Setting the height.
	if(bounds.h > 0){
		camera->bounds.h = bounds.h;
	}
	//Checking if the new bounds is greater than the limit.
	if(rect_reach_y(camera->bounds) > rect_reach_y(camera->limit)){
		camera->limit.h = rect_reach_y(camera->bounds);
	}
}

//Sets a new limit for the camera.
void camera_set_limit(Camera *camera, SDL_Rect limit){
	//Setting the X position.
	camera->limit.x = limit.x;
	//Checking if the new limit is smaller than the bounds.
	if(camera->limit.x > camera->bounds.x){
		camera->bounds.x = camera->limit.x;
	}

	//Setting the Y position.
	camera->limit.y = limit.y;
	//Checking if the new limit is smaller than the bounds.
	if(camera->limit.y > camera->bounds.y){
		camera->bounds.y = camera->limit.y;
	}

	//Setting the width.
	if(limit.w > 0){
		camera->limit.w = limit.w;
	}
	//Checking if the new limit is smaller than the bounds.
	if(rect_reach_x(camera->limit) < rect_reach_x(camera->bounds)){
		camera->bounds.w = camera->limit.w - camera->bounds.x;
	}

	//Setting the height.
	if(limit.h > 0){
		camera->limit.h = limit.h;
	}
	//Checking if the new limit is smaller than the bounds.
	if(rect_reach_x(camera->limit) < rect_reach_x(camera->bounds)){
		camera->bounds.h = camera->limit.h - camera->bounds.y;
	}
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
	if(brx > lrx + camera_offset){
		camera->limit.w += brx - lrx;
	}
	
	int bry = rect_reach_y(bounds);
	int lry = rect_reach_y(camera->limit);
	if(bry > lry + camera_offset){
		camera->limit.h += bry - lry;
	}
}

//Process the events for the camera, such as scroll and keyboard presses that
//move the camera.
void camera_process_events(Camera *camera, SDL_Event event){
	switch(event.type){
		case SDL_MOUSEWHEEL:
			camera->speed.y -= event.wheel.y * camera->mov_speed;
			camera->speed.x += event.wheel.x * camera->mov_speed;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_UP:
					camera->speed.y -= event.wheel.y * camera->mov_speed;
					break;
				case SDLK_DOWN:
					camera->speed.y += event.wheel.y * camera->mov_speed;
					break;
				case SDLK_END:
					camera->speed.y = (camera->limit.h - camera->bounds.h) - camera->bounds.y;
					break;
				case SDLK_HOME:
					camera->speed.y = camera->limit.y - camera->bounds.y;
					break;
			}
			break;
		default:
			camera->speed.x = 0;
			camera->speed.y = 0;
			break;
	}
}

//Sets the X speed of the camera.
void camera_set_x_speed(Camera *camera, int x_speed){
	camera->speed.x = x_speed;
}

//Sets the Y speed of the camera.
void camera_set_y_speed(Camera *camera, int y_speed){
	camera->speed.y = y_speed;
}

//Sets the speed of the camera.
void camera_set_speed(Camera *camera, Vector2 speed){
	camera->speed = speed;
}

//Move the camera (i.e change its position) according to its speed.
void camera_move(Camera *camera){
	camera->bounds.x += camera->speed.x;
	camera->bounds.y += camera->speed.y;

	camera->speed = new_Vector2(0, 0);

	//Checking if position is out of bounds (upper-left).
	if(camera->bounds.x < camera->limit.x){
		camera->bounds.x = camera->limit.x;
	}
	if(camera->bounds.y < camera->limit.y){
		camera->bounds.y = camera->limit.y;
	}

	//Checking if position is out of bounds (bottom-right).
	if(rect_reach_x(camera->bounds) > rect_reach_x(camera->limit)){
		camera->bounds.x = rect_reach_x(camera->limit) - camera->bounds.w;
	}
	if(rect_reach_y(camera->bounds) > rect_reach_y(camera->limit)){
		camera->bounds.y = rect_reach_y(camera->limit) - camera->bounds.h;
	}
}
