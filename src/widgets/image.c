/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Image
 * Image library using SDL2
 */

#include "widgets/image.h"

SDL_bool __image_vt_was_init = SDL_FALSE;

void __image_vt_init(Image *image){
	if(!__image_vt_was_init){
		__gimage_widget_vt = __gtwidget_widget_vt;
		__gimage_widget_vt.free = __image_free;
		__gimage_widget_vt.set_bounds = __image_set_bounds;

		__gimage_vt = __gtwidget_vt;
		__gimage_vt.update = __image_update;

		__image_vt_was_init = SDL_TRUE;
	}
	
	image->t_widget.widget.functions = &__gimage_widget_vt;
	image->t_widget.functions = &__gimage_vt;
}

Image new_Image(const char *file){
	return new_Image_with_bounds(file, new_rect(0, 0, 0, 0));
}

Image new_Image_with_position(const char *file, Position position){
	return new_Image_with_bounds(file, new_rect(position.x, position.y, 0, 0));
}

Image new_Image_with_bounds(const char *file, SDL_Rect bounds){
	Image image;

	image.t_widget = new_TextureWidget();
	__image_vt_init(&image);

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

void image_set_file(Image *image, const char *file){
	string_change(&image->file, file);
}

void __image_free(void *__image){
	Image *image = __image;
	
	__texture_widget_free(&image->t_widget);
	
	free(image->file);
}

void __image_set_bounds(void *__image, SDL_Rect bounds){
	Image *image = __image;

	if(bounds.w > 0 && bounds.h > 0){
		image->t_widget.widget.state.auto_size = SDL_FALSE;
		image->t_widget.functions->set_changed(__image, SDL_TRUE);
	}

	if(image->t_widget.widget.state.auto_size == SDL_TRUE){
		Size size = image_get_original_size(*image);
		bounds.w = size.w;
		bounds.h = size.h;
		image->t_widget.functions->set_changed(__image, SDL_TRUE);
	}

	set_bounds_from_SDL_Rect(&image->t_widget.widget.bounds, bounds);
	border_set_bounds(image->t_widget.widget.border, widget_get_bounds_camera(image));
}

void __image_update(void *__image, SDL_Renderer *renderer){
	Image *image = __image;

	if(!image->t_widget.changed){
		return;
	}

	//load the image into memory using SDL_image library function    
	SDL_Surface *surface = IMG_Load(image->file);

	if(!surface){
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error opening image", IMG_GetError(), NULL);
		printf("image_update: Error Opening Image <%s>: %s\n", image->file, IMG_GetError());
		exit(1);
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
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error creating image texture", SDL_GetError(), NULL);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		exit(1);
	}
	//image_setBounds(img, image_getBounds(img));
	image->t_widget.functions->set_changed(__image, SDL_FALSE);
}
