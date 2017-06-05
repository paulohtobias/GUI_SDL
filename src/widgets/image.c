/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Image
 * Image library using SDL2
 */

#include "widgets/image.h"

Image  newImage(char* path, SDL_Rect bounds){
    Image  img = malloc(sizeof(struct Image_));

    img->texture = NULL;

    img->file = malloc( file_size);
	img->state = newWidgetState();

    image_setSrc(img, path);
    resetBounds(&img->region, bounds);

    return img;
}
void init_image(Image img, SDL_Renderer *renderer){
    if(image_getBounds(img).w > 0 && image_getBounds(img).h > 0){
        return;
    }
    SDL_Surface *temp = IMG_Load(img->file);
    if(!temp){
        printf("init_image: Error Opening Image <%s>: %s\n", img->file, IMG_GetError());
        strcpy(img->file, "./Resources/Images/default_image.png");
        temp = IMG_Load(img->file);
    }
    SDL_Rect size = image_getBounds(img);
    size.w = temp->w;
    size.h = temp->h;

    SDL_FreeSurface(temp);
    temp = NULL;

    image_setBounds(img, size);
    img->state.wasChanged = true;
}
void freeImage(Image  img){
    free(img->file);
    SDL_DestroyTexture(img->texture);
    free(img);
}

//Get
SDL_Rect image_getBounds(Image  img){
    return getBounds(img->region);
}

//Set and Update
void image_setSrc(Image  img, char* file){
	if(file != NULL){
    	strcpy(img->file, file);
        strcpy(img->file, "./Resources/Images/default_cover.png");
        img->state.wasChanged = true;
	}
}
void image_update(Image img, SDL_Renderer *renderer){
    if(widget_wasChanged(img->state) == true){
        // load the image into memory using SDL_image library function
        int error_count = 0;
        SDL_Surface *surface = IMG_Load(img->file);
        if(!surface){
            img_error:
            //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error opening image", IMG_GetError(), NULL);
            printf("image_update: Error Opening Image <%s>: %s\n", img->file, IMG_GetError());
            strcpy(img->file, "./Resources/Images/default_image.png");
            //img->surface = IMG_Load(img->file);
            surface = IMG_Load(img->file);
        }

        // load the image data into the graphics hardware's memory
        if(img->texture != NULL){
			SDL_DestroyTexture(img->texture);
			img->texture = NULL;
		}
        img->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        surface = NULL;
        if (!img->texture){
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
        img->state.wasChanged = false;
    }
}
void image_setBounds(Image  img, SDL_Rect region){
	//Maybe this is useless and can be removed
    if(region.w<=0 && region.h<=0){
        SDL_QueryTexture(img->texture, NULL, NULL, &region.w, &region.h);
	}

    setBounds(&img->region, region);
}
void image_updateBounds(Image  img, SDL_Rect region){
    updateBounds(&img->region, region);
}

//Events
void image_processEvents(SDL_Event event, Mouse mouseState, Image img){
	basic_widget_processEvents(event, mouseState, &img->state, img->region);
	if(image_isDragged(img)){
		image_updateBounds(img, widget_dragPosition(mouseState));
	}
}
bool image_isFocused(Image  img){
	return widget_isFocused(img->state);
}
bool image_isPressed(Image img){
	return widget_isPressed(img->state);
}
bool image_isReleased(Image img){
	return widget_isReleased(img->state);
}
bool image_isDragged(Image img){
	return widget_isDragged(img->state);
}

//Render
void renderImage(Image  img, SDL_Renderer *renderer, Camera  camera){
    camera_updateWidgetPosition(camera, &img->region);

    if( !camera_widget_is_off(camera, image_getBounds(img)) ){
        if(widget_isOnCamera(img->state) == false){
            img->state.isOnCamera = true;
        }

        image_update(img, renderer);
        SDL_RenderCopy(renderer, img->texture, NULL, &img->region.relative);
    }else if(img->state.isOnCamera == true){
        img->state.isOnCamera = false;
        SDL_DestroyTexture(img->texture);
        img->texture = NULL;
        img->state.wasChanged = true;
    }
}
