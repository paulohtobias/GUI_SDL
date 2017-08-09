/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Image
 * Image library using SDL2
 */

#include "widgets/image.h"

Image new_Image(char *file){
    return new_Image_with_bounds(file, new_rect(0, 0, 0, 0));
}

Image new_Image_with_position(char *file, Position position){
    return new_Image_with_bounds(file, new_rect(position.x, position.y, 0, 0));
}

Image new_Image_with_bounds(char *file, SDL_Rect bounds){
    Image image;
    
    image.t_widget = new_TextureWidget();
    
    image.t_widget.update = generic_image_update;
    image.t_widget.widget.set_bounds = generic_image_set_bounds;
        
    image.file = NULL;
    
    image_set_file(&image, file);
    widget_set_bounds(&image, bounds);
    
    return image;
}

Size image_get_original_size(Image image){
    Size size = image.t_widget.widget.bounds.size;
    
    SDL_Surface *temp = IMG_Load(image.file);
    if(temp == NULL){
        printf("image_get_original_size: %s\n", IMG_GetError());
        size.w = 0;
        size.h = 0;
        return size;
    }
    size.w = temp->w;
    size.h = temp->h;

    SDL_FreeSurface(temp);
    temp = NULL;

    return size;
}

void image_set_file(Image *image, char *file){
    string_change(&image->file, file);
}


void generic_image_set_bounds(void *raw_image, SDL_Rect bounds){
    Image *image = raw_image;
    
    if(bounds.w > 0 && bounds.h > 0){
        image->t_widget.widget.state.auto_size = false;
        image->t_widget.set_changed(raw_image, true);
    }
    
    if(image->t_widget.widget.state.auto_size == true){
        Size size = image_get_original_size(*image);
        bounds.w = size.w;
        bounds.h = size.h;
        image->t_widget.set_changed(raw_image, true);
    }
    
    set_bounds_from_SDL_Rect(&image->t_widget.widget.bounds, bounds);
}

void generic_image_update(void *raw_image, SDL_Renderer *renderer){
    Image *image = raw_image;
    
    if(!image->t_widget.changed){
        return;
    }
    
    //load the image into memory using SDL_image library function
    int error_count = 0;
    SDL_Surface *surface = IMG_Load(image->file);
    if(!surface){
        img_error:
        //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error opening image", IMG_GetError(), NULL);
        printf("image_update: Error Opening Image <%s>: %s\n", image->file, IMG_GetError());
        image_set_file(image, "./Resources/Images/default_image.png");
        //img->surface = IMG_Load(img->file);
        surface = IMG_Load(image->file);
    }

    // load the image data into the graphics hardware's memory
    if(image->t_widget.texture != NULL){
        SDL_DestroyTexture(image->t_widget.texture);
        image->t_widget.texture = NULL;
    }
    image->t_widget.texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = NULL;
    if(image->t_widget.texture == NULL){
        if(error_count == 0){
            error_count++;
            goto img_error;
        }
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error creating image texture", SDL_GetError(), NULL);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        exit(1);
    }
    //image_setBounds(img, image_getBounds(img));
    image->t_widget.set_changed(raw_image, false);
}
