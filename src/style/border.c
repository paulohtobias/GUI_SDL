#include "style/border.h"

VT_Border __gborder_vt = {
	__border_set_bounds,
	__border_draw
};

Border new_Border(int size, Color color, SDL_Rect widget_bounds){
	return new_Border_all(size, size, size, size, color, widget_bounds);
}

Border new_Border_all(int size_up, int size_down, int size_right, int size_left, Color color, SDL_Rect widget_bounds){
	Border border;
	
	border.functions = &__gborder_vt;
	
	border.size_up = size_up;
	border.size_down = size_down;
	border.size_right = size_right;
	border.size_left = size_left;
	border.color = color;
	
	border_set_bounds(&border, widget_bounds);
	
	return border;
}

Border *new_Border_dynamic(int size, Color color, SDL_Rect widget_bounds){
	return new_Border_all_dynamic(size, size, size, size, color, widget_bounds);
}

Border *new_Border_all_dynamic(int size_up, int size_down, int size_right, int size_left, Color color, SDL_Rect widget_bounds){
	Border *border = malloc(sizeof(Border));
	
	(*border) = new_Border_all(size_up, size_down, size_right, size_left, color, widget_bounds);
	
	return border;
}

void border_set_bounds(void *border, SDL_Rect widget_bounds){
	if(border != NULL){
		((Border *)border)->functions->set_bounds(border, widget_bounds);
	}
}

void border_draw(void *border, SDL_Renderer *renderer, Camera *camera){
	if(border != NULL){
		((Border *)border)->functions->draw(border, renderer, camera);
	}
}


void __border_set_bounds(void *__border, SDL_Rect widget_bounds){
	Border *border = __border;
	
	border->bounds.x = widget_bounds.x - border->size_left;
	border->bounds.w = widget_bounds.w + border->size_left + border->size_right;
	border->bounds.y = widget_bounds.y - border->size_up;
	border->bounds.h = widget_bounds.h + border->size_up + border->size_down;
}

void __border_draw(void *__border, SDL_Renderer *renderer, Camera *camera){
	Border *border = __border;
	
	set_renderer_draw_color(renderer, border->color);
	SDL_RenderFillRect(renderer, &border->bounds);
}
