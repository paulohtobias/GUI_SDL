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

typedef struct Camera_{
    //Camera.
    SDL_Rect bounds;
    SDL_Rect limit;
    
    //Speed and movement.
    int mov_speed;
    Vector2 speed;
    
    //Events
    //TO-DO: mark which events can be processed by the camera.
}Camera;

/**
 * Creates a new Camera.
 * 
 * @param limit the initial bounds and limit for the camera.
 * @return the Camera created.
 */
Camera *new_Camera(SDL_Rect limit);

/**
 * Frees camera from memory.
 * 
 * @param camera the camera to be freed from memory.
 */
void free_Camera(Camera *camera);

/**
 * Returns the distance of <code>camera</code>'s position to its
 * <code>limit</code> position. Use this function instead of acessing the
 * <code>bounds</code> attribute directly because <code>limit</code> position
 * can be diferent from (0,0).
 * 
 * @param camera a <code>Camera</code>
 * @return a <code>Position</code> with the actual distance of the camera to its
 * limit position
 */
Position camera_get_position(Camera *camera);

/**
 * Sets a new position and size for the camera.
 * 
 * If the new bounds is greater than camera limit, then it will also be updated
 * to match the new bounds.
 * 
 * @param camera the camera that will be updated.
 * @param bounds the new bounds of the camera.
 */
void camera_set_bounds(Camera *camera, SDL_Rect bounds);

/**
 * Sets a new limit for the camera.
 * 
 * If the new limit is smaller than camera bounds, then it will also be updated
 * to match the new limit.
 * 
 * @param camera the camera that will be updated.
 * @param limit the new limit of the camera.
 */
void camera_set_limit(Camera *camera, SDL_Rect limit);

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

