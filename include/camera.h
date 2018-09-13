/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Camera
 * Camera module.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "basic/mouse.h"

//Default values for the camera.
#ifndef default_camera_speed
#define default_camera_speed 20
#endif
#ifndef camera_offset
#define camera_offset 20
#endif

typedef struct Camera{
	/**
	 * Region that cover all widgets that are 'watched' by the camera. Relative
	 * to window's origin.
	 */
	SDL_Rect limit;

	///Internal.
	SDL_bool __update_limit;
	
	/**
	 * Region on the screen where the widgets are rendered. Relative to window's
	 * origin.
	 */
	SDL_Rect bounds;
	
	/**
	 * Indicates wich region of <code>limit</code> is being rendered. The size
	 * of this region is given by the <code>bounds</code> attribute.
	 */
	Position position;

	//Speed and movement.
	int mov_speed;
	Vector2 speed;

	//Events
	//TO-DO: mark which events can be processed by the camera.
} Camera;

///Only one camera can be 'scrolled' at a time. This will be it.
Camera *camera_active;


/**
 * Creates a new Camera.
 * 
 * @param limit the initial bounds and limit for the camera.
 * @return the Camera created.
 */
Camera new_Camera(SDL_Rect limit);

/**
 * COMMENT
 * @param camera
 * @param bounds
 * @return 
 */
SDL_Rect camera_get_relative_bounds(Camera *camera, SDL_Rect bounds);

/**
 * Gets the source and destination SDL_Rect to draw something relative to the
 * camera.
 * 
 * @param camera a <code>Camera</code>. Can be <code>NULL</code>.
 * @param dst_bounds an <code>SDL_Rect</code> with the position and size of the
 *                   object relative to the camera. A call to
 *                   <code>camera_get_relative_bounds</code> will be enough in
 *                   most cases. <code>dst_bounds</code> will be updated.
 */
SDL_Rect camera_get_drawable_area(Camera *camera, SDL_Rect *dst_bounds);

void __camera_set_update_limit(Camera *camera, SDL_bool update_limit);

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

