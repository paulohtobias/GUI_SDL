#include "widgets/rectangle.h"

VT_Widget __grectangle_widget_vt = {
	__texture_widget_free,
	__rectangle_set_bounds,
	__widget_process_events,
	__texture_widget_draw
};

VT_TextureWidget __grectangle_vt = {
	__texture_widget_set_changed,
	__texture_widget_render_copy,
	__rectangle_update
};

Rectangle new_Rectangle(Color color){
	return new_Rectangle_with_bounds(color, new_rect(0, 0, 0, 0));
}

Rectangle new_Rectangle_with_position(Color color, Position position){
	return new_Rectangle_with_bounds(color, new_rect(position.x, position.y, 0, 0));
}

Rectangle new_Rectangle_with_bounds(Color color, SDL_Rect bounds){
	Rectangle rectangle = new_TextureWidget();

	rectangle.widget.style = new_Style_dynamic();
	style_set_background_color(rectangle.widget.style, color);
	rectangle.widget.functions = &__grectangle_widget_vt;
	rectangle.functions = &__grectangle_vt;

	widget_set_bounds(&rectangle, bounds);

	return rectangle;
}

void __rectangle_set_bounds(void *__rectangle, SDL_Rect bounds){
	__widget_set_bounds(__rectangle, bounds);
	((Rectangle *) __rectangle)->functions->set_changed(__rectangle, SDL_TRUE);
}

void __rectangle_update(void *__rectangle, SDL_Renderer *renderer){
	Rectangle *rectangle = __rectangle;

	if(!rectangle->changed){
		return;
	}

	if(rectangle->texture != NULL){
		SDL_DestroyTexture(rectangle->texture);
		rectangle->texture = NULL;
	}

	Size size = rectangle->widget.bounds.size;
	if(size.w == 0 || size.h == 0){
		return;
	}

	rectangle->texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		size.w, size.h);

	if(rectangle->texture == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error creating image texture",
			SDL_GetError(), NULL);

		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		exit(1);
	}
	SDL_SetTextureBlendMode(rectangle->texture, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, rectangle->texture);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	set_renderer_draw_color(renderer, style_get_background_color(rectangle->widget.style));
	SDL_RenderFillRect(renderer, NULL);

	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);

	rectangle->functions->set_changed(__rectangle, SDL_FALSE);
}
