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
    image.t_widget.set_changed = generic_image_set_changed;
    image.t_widget.update = generic_image_update;
        
    image.file = NULL;
    image_set_file(&image, file);
    widget_set_bounds((void *)&image, bounds);
    Size size = image.t_widget.widget.bounds.size;
    image.t_widget.set_changed((void *)&image, true);
    if(size.w == 0 && size.h == 0){
        image_set_surface_size(&image);
    }
    
    return image;
}

void image_set_surface_size(Image *image){
    Size size = image->t_widget.widget.bounds.size;
    SDL_Surface *temp = IMG_Load(image->file);
    if(temp == NULL){
        printf("init_image: Error Opening Image <%s>: %s\n", image->file, IMG_GetError());
        image_set_file(image, "./Resources/Images/default_image.png");
        temp = IMG_Load(image->file);
    }
    size.w = temp->w;
    size.h = temp->h;

    SDL_FreeSurface(temp);
    temp = NULL;

    set_size(&image->t_widget.widget.bounds, size);
    image->t_widget.set_changed((void *)image, true);
}

void generic_image_set_changed(void *raw_image, bool changed){
    ((Image *)raw_image)->t_widget.widget.state.changed = changed;
}

void generic_image_update(void *raw_image, SDL_Renderer *renderer){
    Image *image = raw_image;
    
    if(image->t_widget.widget.state.changed == false){
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

void image_set_file(Image *image, char *file){
    if(image->file != NULL){
        free(image->file);
        image->file = NULL;
    }
    image->file = malloc(sizeof(file));
    strcpy(image->file, file);
}
