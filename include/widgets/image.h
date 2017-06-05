/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Image
 * Image library using SDL2
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL_image.h>
#include <string.h>

#include "widgets/basicUI.h"

#define file_size 500

struct Image_{
    char* file;

    Bounds region;
	WidgetState state;

    SDL_Texture *texture;
};
typedef struct Image_* Image;

Image  newImage(char *path, SDL_Rect bounds);
void init_image(Image img, SDL_Renderer *renderer);
void freeImage(Image img);

//Get
SDL_Rect image_getBounds(Image img);

//Set and Update
void image_setSrc(Image img, char *file);
void image_update(Image img, SDL_Renderer *renderer);
void image_setBounds(Image img, SDL_Rect region);
void image_updateBounds(Image img, SDL_Rect region);

//Events
void image_processEvents(SDL_Event event, Mouse mouseState, Image img);
bool image_isFocused(Image img);
bool image_isPressed(Image img);
bool image_isDragged(Image img);
bool image_isReleased(Image img);

//Render
void renderImage(Image img, SDL_Renderer *renderer, Camera camera);

#endif // IMAGE_H
