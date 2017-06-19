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

#ifndef default_camera_speed
    #define default_camera_speed 20
#endif

typedef struct Camera_{
    //Camera.
    SDL_Rect bounds;
    SDL_Rect limit;
    
    //Speed and movement.
    int mov_speed;
    Vector speed;
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
 * @param camera the camera to be freed from memory.
 */
void free_Camera(Camera *camera);


#endif //CAMERA_H

