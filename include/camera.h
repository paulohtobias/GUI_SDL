/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Camera
 * Camera module.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <basic/bounds.h>

//Default values for the camera.
#ifndef default_camera_speed
#define default_camera_speed 20
#endif
#ifndef camera_offset
#define camera_offset 20
#endif

typedef struct Camera{
	SDL_Rect limit; ///Relative to window's origin.
	SDL_Rect bounds; ///TO-DO: make ut relative to limit.

	//Speed and movement.
	int mov_speed;
	Vector2 speed;

	//Events
	//TO-DO: mark which events can be processed by the camera.
} Camera;

/**
 * Creates a new Camera.
 * 
 * @param limit the initial bounds and limit for the camera.
 * @return the Camera created.
 */
Camera new_Camera(SDL_Rect limit);

SDL_Rect camera_get_relative_bounds(Camera *camera, SDL_Rect bounds);

/**
 * Sets a new position and size for the camera.
 * 
 * If the new bounds is greater than camera limit, then its limits will grow to
 * match the new bounds.
 * 
 * @param camera the camera that will be updated.
 * @param bounds the new bounds of the camera.
 */
void camera_set_bounds(Camera *camera, SDL_Rect bounds);

/**
 * Sets a new limit for the camera.
 * 
 * If the new limit is smaller than camera bounds, then its bounds will shrink
 * to match the new limit.
 * 
 * @param camera the camera that will be updated.
 * @param limit the new limit of the camera.
 */
void camera_set_limit(Camera *camera, SDL_Rect limit);

/**
 * Resize the camera's limit if bounds is not inside it.
 * 
 * @param camera a <code>Camera</code>
 * @param bounds an <code>SDL_Rect</code>
 */
void camera_update_limit(Camera *camera, SDL_Rect bounds);

/**
 * Process the events for the camera, such as scroll and keyboard presses that
 * move the camera.
 * 
 * If the event is a "move camera" type of event (scrolling the
 * window, pressing the arrow keys, etc), then the camera X and Y speed will
 * increase/decrease their values.
 * 
 * @param camera the camera that will have the events processed.
 * @param event the SDL_Event containing information of the event.
 */
void camera_process_events(Camera *camera, SDL_Event event);

/**
 * Sets the X speed of the camera.
 * 
 * @param camera the camera that will have the x speed changed.
 * @param x_speed the new value for camera's x speed.
 */
void camera_set_x_speed(Camera *camera, int x_speed);

/**
 * Sets the Y speed of the camera.
 * 
 * @param camera the camera that will have the y speed changed.
 * @param y_speed the new value for camera's y speed.
 */
void camera_set_y_speed(Camera *camera, int y_speed);

/**
 * Sets the speed of the camera.
 * 
 * @param camera the camera that will have the speed changed.
 * @param speed the new value for camera's speed.
 */
void camera_set_speed(Camera *camera, Vector2 speed);

/**
 * Move the camera (i.e change its position) according to its speed.
 * 
 * @param camera the camera that will be moved.
 */
void camera_move(Camera *camera);

#endif //CAMERA_H

