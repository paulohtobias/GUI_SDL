/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Image
 * Image library using SDL2
 */

#ifndef IMAGE_H
#define IMAGE_H

#include "texture_widget.h"
#include <SDL2/SDL_image.h>

typedef struct Image{
    TextureWidget t_widget;
    
    char *file;
}Image;

Image new_Image(char *file);

Image new_Image_with_position(char *file, Position position);

Image new_Image_with_bounds(char *file, SDL_Rect bounds);

Size image_get_original_size(Image image);

void image_set_file(Image *image, char *file);


void generic_image_set_bounds(void *raw_image, SDL_Rect bounds);

void generic_image_set_changed(void *raw_image, int changed);

void generic_image_update(void *raw_image, SDL_Renderer *renderer);

#endif //IMAGE_H

