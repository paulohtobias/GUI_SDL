#include "widgets/rectangle.h"

SDL_bool __rectangle_vt_was_init = SDL_FALSE;

void __rectangle_vt_init(){
	if(__rectangle_vt_was_init){
		return;
	}
	
	__grectangle_widget_vt = __gtwidget_widget_vt;
	__grectangle_widget_vt.set_bounds = __rectangle_set_bounds;
	
	__grectangle_vt = __gtwidget_vt;
	__grectangle_vt.update = __rectangle_update;
	
	__rectangle_vt_was_init = SDL_TRUE;
}

Rectangle new_Rectangle(Color color){
	return new_Rectangle_with_bounds(color, new_rect(0, 0, 0, 0));
}

Rectangle new_Rectangle_with_position(Color color, Position position){
	return new_Rectangle_with_bounds(color, new_rect(position.x, position.y, 0, 0));
}

Rectangle new_Rectangle_with_bounds(Color color, SDL_Rect bounds){
	Rectangle rectangle;
	
	rectangle.t_widget = new_TextureWidget();

	__rectangle_vt_init();
	rectangle.t_widget.widget.functions = &__grectangle_widget_vt;
	rectangle.t_widget.functions = &__grectangle_vt;
	
	rectangle_set_color(&rectangle, color);
	widget_set_bounds(&rectangle, bounds);

	return rectangle;
}

void rectangle_set_color(void *__rectangle, Color color){
	Rectangle *rectangle = __rectangle;
	
	rectangle->color = color;
	
	texture_widget_set_changed(rectangle, SDL_TRUE);
}


void __rectangle_set_bounds(void *__rectangle, SDL_Rect bounds){
	__widget_set_bounds(__rectangle, bounds);
	texture_widget_set_changed(__rectangle, SDL_TRUE);
}

void __rectangle_update(void *__rectangle, SDL_Renderer *renderer){
	Rectangle *rectangle = __rectangle;

	if(!rectangle->t_widget.changed){
		return;
	}

	if(rectangle->t_widget.texture != NULL){
		SDL_DestroyTexture(rectangle->t_widget.texture);
		rectangle->t_widget.texture = NULL;
	}

	Size size = rectangle->t_widget.widget.bounds.size;
	if(size.w == 0 || size.h == 0){
		return;
	}

	rectangle->t_widget.texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		size.w, size.h);

	if(rectangle->t_widget.texture == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error creating image texture",
			SDL_GetError(), NULL);

		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		exit(1);
	}
	SDL_SetTextureBlendMode(rectangle->t_widget.texture, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, rectangle->t_widget.texture);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	set_renderer_draw_color(renderer, rectangle->color);
	SDL_RenderFillRect(renderer, NULL);

	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);

	texture_widget_set_changed(__rectangle, SDL_FALSE);
}
