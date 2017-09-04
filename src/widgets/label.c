#include "widgets/label.h"

VT_Widget __glabel_widget_vt = {
	generic_label_free,
	generic_label_set_bounds,
	generic_widget_process_events,
	generic_texture_widget_draw
};

VT_TextureWidget __glabel_twidget_vt = {
	generic_label_set_changed,
	generic_label_render_copy,
	generic_label_update
};

Label new_Label(const char *text){
	return new_Label_with_bounds(text, new_rect(0, 0, 0, 0));
}

Label new_Label_with_position(const char *text, Position position){
	return new_Label_with_bounds(text, new_rect(position.x, position.y, 0, 0));
}

Label new_Label_with_bounds(const char *text, SDL_Rect bounds){
	Label label;

	label.t_widget = new_TextureWidget();

	label.t_widget.functions = &__glabel_twidget_vt;
	label.t_widget.widget.functions = &__glabel_widget_vt;

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
		font = TTF_OpenFont(label->style->font, label->style->size);
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
		(*label->style) = label_default_style;
	}
}

void label_set_color(Label *label, Color color){
	__label_new_style(label);
	label->style->color = color;
	label->t_widget.functions->set_changed(label, LABEL_STATE_CHANGED);
}

void label_set_font(Label *label, const char *font){
	__label_new_style(label);
	snprintf(label->style->font, 60, "./Resources/Fonts/%s.ttf", font);
	//strncpy(label->style->font, font, 60);
	label->t_widget.functions->set_changed(label, LABEL_STATE_CHANGED);
}

void label_set_size(Label *label, int size){
	__label_new_style(label);
	label->style->size = size;
	label->t_widget.functions->set_changed(label, LABEL_STATE_CHANGED);
}

void label_center(Label *label){
	__label_new_style(label);
	label->style->center = true;
	label->t_widget.functions->set_changed(label, LABEL_STATE_CENTERED);
}

void label_set_style(Label *label, LabelStyle *style){
	label->style = style;
	label->t_widget.functions->set_changed(label, LABEL_STATE_CHANGED);
}

SDL_Rect label_get_center_bounds(Label *label, Size *real_size){
	if(real_size == NULL){
		real_size = malloc(sizeof(SDL_Rect));
		(*real_size) = label_get_original_size(*label, strlen(label->text) - 1);
	}

	SDL_Rect center_bounds = widget_get_bounds_origin(label);
	center_bounds.x = MAX(center_bounds.x, center_bounds.x + (center_bounds.w / 2) - (real_size->w / 2));
	center_bounds.y = MAX(center_bounds.y, center_bounds.y + (center_bounds.h / 2) - (real_size->h / 2));

	return center_bounds;
}

void generic_label_free(void *raw_label){
	Label *label = raw_label;

	widget_free(&label->t_widget);

	free(label->text);
	free(label->size_table);
	if(label->style != &label_default_style){
		free(label->style);
	}
}

void generic_label_set_bounds(void *raw_label, SDL_Rect bounds){
	Label *label = raw_label;

	if(bounds.w > 0 && bounds.h > 0){
		label->t_widget.widget.state.auto_size = false;
		label->t_widget.functions->set_changed(raw_label, LABEL_STATE_CHANGED);
	}

	if(label->t_widget.widget.state.auto_size == true){
		Size size = label_get_original_size(*label, strlen(label->text) - 1);
		bounds.w = size.w;
		bounds.h = size.h;
		label->t_widget.functions->set_changed(raw_label, LABEL_STATE_CHANGED);
	}

	set_bounds_from_SDL_Rect(&label->t_widget.widget.bounds, bounds);
}

void generic_label_set_changed(void *raw_label, int changed){
	Label *label = raw_label;

	//If they're equal, then don't do anything.
	if(label->t_widget.changed == changed){
		return;
	}

	if(label->t_widget.changed == LABEL_STATE_UNCHANGED || changed == LABEL_STATE_UNCHANGED){
		label->t_widget.changed = changed;
		return;
	}

	//Here, neither are false.
	//But if the state is already on LABEL_STATE_CENTERED, it needs to
	//keep that state.
	if(label->t_widget.changed != LABEL_STATE_CENTERED){
		label->t_widget.changed = changed;
	}
}

void generic_label_render_copy(void *raw_label, SDL_Renderer *renderer){
	Label *label = raw_label;

	SDL_Rect bounds = get_bounds_camera(label->t_widget.widget.bounds);
	Size real_size = label_get_original_size(*label, strlen(label->text) - 1);
	SDL_Rect limit;
	limit.x = limit.y = 0;
	limit.w = MIN(real_size.w, bounds.w);
	limit.h = MIN(real_size.h, bounds.h);

	bounds.w = limit.w;
	bounds.h = limit.h;

	if(label->style->center == true){
		bounds = label_get_center_bounds(label, &real_size);
	}

	SDL_RenderCopy(renderer, label->t_widget.texture, &limit, &bounds);
}

void generic_label_update(void *raw_label, SDL_Renderer *renderer){
	Label *label = raw_label;

	if(label->t_widget.changed == LABEL_STATE_UNCHANGED){
		return;
	}

	//Creating the Font.
	TTF_Font *ttf_font = TTF_OpenFont(label->style->font, label->style->size);
	if(ttf_font == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Error: generic_label_update", TTF_GetError(), NULL);
		exit(1);
	}
	label_update_size_table(label, ttf_font);
	Size real_size = label_get_original_size(*label, strlen(label->text) - 1);

	//Creating the Surface.
	SDL_Surface *surface = NULL;
	if(!label->style->wrap){
		surface = TTF_RenderUTF8_Blended(ttf_font, label->text, label->style->color);
	}else{
		int bounds_width = widget_get_bounds_origin(raw_label).w;
		int max_width = MIN(bounds_width, real_size.w);

		surface = TTF_RenderUTF8_Blended_Wrapped(ttf_font, label->text, label->style->color, max_width);
	}
	TTF_CloseFont(ttf_font);
	ttf_font = NULL;

	//Error checking.
	if(surface == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Surface Error: generic_label_update", TTF_GetError(), NULL);

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
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Texture Error: generic_label_update", SDL_GetError(), NULL);
		free(label);

		TTF_Quit();
		SDL_Quit();
		exit(1);
	}

	if(label->t_widget.widget.state.auto_size == true){
		set_size(&label->t_widget.widget.bounds, real_size);
	}
	label->t_widget.functions->set_changed(raw_label, LABEL_STATE_UNCHANGED);
}
