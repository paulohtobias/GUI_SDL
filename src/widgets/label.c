#include "widgets/label.h"

SDL_bool __label_vt_was_init = SDL_FALSE;

void __label_vt_init(Label *label){
	if(!__label_vt_was_init){
		__glabel_widget_vt = __gtwidget_widget_vt;
		__glabel_widget_vt.free = __label_free;
		__glabel_widget_vt.set_bounds = __label_set_bounds;

		__glabel_twidget_vt = __gtwidget_vt;
		__glabel_twidget_vt.render_copy = __label_render_copy;
		__glabel_twidget_vt.update = __label_update;

		__label_vt_was_init = SDL_TRUE;
	}
	
	label->t_widget.functions = &__glabel_twidget_vt;
	label->t_widget.widget.functions = &__glabel_widget_vt;
}

Label new_Label(const char *text){
	return new_Label_with_bounds(text, new_rect(0, 0, 0, 0));
}

Label new_Label_with_position(const char *text, Position position){
	return new_Label_with_bounds(text, new_rect(position.x, position.y, 0, 0));
}

Label new_Label_with_bounds(const char *text, SDL_Rect bounds){
	Label label;

	label.t_widget = new_TextureWidget();
	__label_vt_init(&label);

	label.text = NULL;
	label.size_table = NULL;
	label.style = &label_default_style;

	label_set_text(&label, text);
	widget_set_bounds(&label, bounds);
	label_update_size_table(&label, NULL);

	return label;
}

void label_update_size_table(Label *label, TTF_Font *font){
	int i, len = strlen(label->text);
	if(font == NULL){
		font = TTF_OpenFont(label_get_font(label), label_get_size(label));
		if(font == NULL){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Error: label_update_size_table", TTF_GetError(), NULL);
			exit(1);
		}
	}

	if(label->size_table != NULL){
		free(label->size_table);
	}
	label->size_table = malloc(len * sizeof(Size));

	for(i = 0; i < len - 1; i++){
		char c = label->text[i + 1];
		label->text[i + 1] = '\0';
		TTF_SizeUTF8(font, label->text, &label->size_table[i].w, &label->size_table[i].h);
		label->text[i + 1] = c;
	}
	TTF_SizeUTF8(font, label->text, &label->size_table[i].w, &label->size_table[i].h);
}

Size label_get_original_size(Label label, int index){
	/*int len = strlen(label.text);
	if(index >= len){
		return new_Size(-1, -1);
	}*/
	return label.size_table[index];
}

void label_set_text(Label *label, const char *text){
	string_change(&label->text, text);
	label_update_size_table(label, NULL);
}

///Internal function used when changing a label's style.
void __label_new_style(Label *label){
	if(label->style == &label_default_style){
		label_set_style(label, malloc(sizeof(LabelStyle)));
		*(label->style) = label_default_style;
	}
}

Color label_get_color(Label* label){
	return label->style->color;
}

void label_set_color(Label *label, Color color){
	__label_new_style(label);
	label->style->color = color;
	label->t_widget.functions->set_changed(label, SDL_TRUE);
}

char *label_get_font(Label* label){
	return label->style->font;
}

void label_set_font(Label *label, const char *font){
	__label_new_style(label);
	snprintf(label->style->font, 60, "./Resources/Fonts/%s.ttf", font);
	label->t_widget.functions->set_changed(label, SDL_TRUE);
}

int label_get_size(Label* label){
	return label->style->size;
}

void label_set_size(Label *label, int size){
	__label_new_style(label);
	label->style->size = size;
	label->t_widget.functions->set_changed(label, SDL_TRUE);
}

SDL_bool label_get_center(Label* label){
	return label->style->center;
}

void label_set_center(Label *label, SDL_bool center){
	__label_new_style(label);
	label->style->center = center;
}

SDL_bool label_get_wrap(Label* label){
	return label->style->wrap;
}

void label_set_wrap(Label *label, SDL_bool wrap){
	__label_new_style(label);
	label->style->wrap = wrap;
	label->t_widget.functions->set_changed(label, SDL_TRUE);
}

void label_set_style(Label *label, LabelStyle *style){
	label->style = style;
	label->t_widget.functions->set_changed(label, SDL_TRUE);
}

SDL_Rect label_get_center_bounds(Label *label, SDL_Rect *center_bounds, Size *real_size){
	if(real_size == NULL){
		real_size = malloc(sizeof(SDL_Rect));
		(*real_size) = label_get_original_size(*label, strlen(label->text) - 1);
	}

	//SDL_Rect center_bounds = widget_get_bounds_camera(label);
	center_bounds->x = MAX(center_bounds->x, center_bounds->x + (center_bounds->w / 2) - (real_size->w / 2));
	center_bounds->y = MAX(center_bounds->y, center_bounds->y + (center_bounds->h / 2) - (real_size->h / 2));
    /*center_bounds->w = real_size->w;
    center_bounds->h = real_size->h;*/

	return *center_bounds;
}

void __label_free(void *__label){
	Label *label = __label;

	__texture_widget_free(&label->t_widget);

	free(label->text);
	free(label->size_table);
	if(label->style != &label_default_style){
		free(label->style);
	}
}

void __label_set_bounds(void *__label, SDL_Rect bounds){
	Label *label = __label;

	if(bounds.w > 0 && bounds.h > 0){
		label->t_widget.widget.state.auto_size = SDL_FALSE;
	}

	if(label->t_widget.widget.state.auto_size == SDL_TRUE){
		Size size = label_get_original_size(*label, strlen(label->text) - 1);
		bounds.w = size.w;
		bounds.h = size.h;
	}

	set_bounds_from_SDL_Rect(&label->t_widget.widget.bounds, bounds);
	border_set_bounds(label->t_widget.widget.border, widget_get_bounds_camera(label));
}

void __label_render_copy(void *__label, SDL_Renderer *renderer){
	Label *label = __label;

	Size real_size = label_get_original_size(*label, strlen(label->text) - 1);
	SDL_Rect bounds;
	SDL_Rect draw_area = widget_get_drawable_area(label, &bounds);
	draw_area.w = MIN(real_size.w, bounds.w);
	draw_area.h = MIN(real_size.h, bounds.h);

	bounds.w = draw_area.w;
	bounds.h = draw_area.h;
	
	if (label_get_center(label) == SDL_TRUE) {
		label_get_center_bounds(label, &bounds, &real_size);
	}
	
	border_set_bounds(label->t_widget.widget.border, bounds);
	border_draw(label->t_widget.widget.border, renderer);
	SDL_RenderCopy(renderer, label->t_widget.texture, &draw_area, &bounds);
}

void __label_update(void *__label, SDL_Renderer *renderer){
	Label *label = __label;

	if(label->t_widget.changed == SDL_FALSE){
		return;
	}

	//Creating the Font.
	TTF_Font *ttf_font = TTF_OpenFont(label_get_font(label), label_get_size(label));
	if(ttf_font == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Error: __label_update", TTF_GetError(), NULL);
		exit(1);
	}
	label_update_size_table(label, ttf_font);
	Size real_size = label_get_original_size(*label, strlen(label->text) - 1);

	//Creating the Surface.
	SDL_Surface *surface = NULL;
	if(!label_get_wrap(label)){
		surface = TTF_RenderUTF8_Blended(ttf_font, label->text, label_get_color(label));
	}else{
		int bounds_width = widget_get_bounds_local(__label).w;
		int max_width = MIN(bounds_width, real_size.w);

		surface = TTF_RenderUTF8_Blended_Wrapped(ttf_font, label->text, label_get_color(label), max_width);
	}
	TTF_CloseFont(ttf_font);
	ttf_font = NULL;

	//Error checking.
	if(surface == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Surface Error: __label_update", TTF_GetError(), NULL);

		TTF_Quit();
		SDL_Quit();

		exit(1);
	}

	//Updating the Texture.
	if(label->t_widget.texture != NULL){
		SDL_DestroyTexture(label->t_widget.texture);
		label->t_widget.texture = NULL;
	}
	label->t_widget.texture = SDL_CreateTextureFromSurface(renderer, surface);

	//Freeing the surface from memory.
	SDL_FreeSurface(surface);
	surface = NULL;

	//Error checking.
	if(label->t_widget.texture == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Texture Error: __label_update", SDL_GetError(), NULL);
		free(label);

		TTF_Quit();
		SDL_Quit();
		exit(1);
	}

	if(label->t_widget.widget.state.auto_size == SDL_TRUE){
		bounds_set_size(&label->t_widget.widget.bounds, real_size);
	}
	label->t_widget.functions->set_changed(__label, SDL_FALSE);
}
