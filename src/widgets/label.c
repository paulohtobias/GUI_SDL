#include "widgets/label.h"

Label new_Label(const char *text){
    return new_Label_with_bounds(text, new_rect(0, 0, 0, 0));
}

Label new_Label_with_position(const char *text, Position position){
    return new_Label_with_bounds(text, new_rect(position.x, position.y, 0, 0));
}

Label new_Label_with_bounds(const char *text, SDL_Rect bounds){
    Label label;
    
    label.t_widget = new_TextureWidget();
    
    label.t_widget.set_changed = generic_label_set_changed;
    label.t_widget.render_copy = generic_label_render_copy;
    label.t_widget.update = generic_label_update;
    label.t_widget.widget.set_bounds = generic_label_set_bounds;
        
    label.text = NULL;
    label_set_text(&label, text);
    label.style = &label_default_style;
    widget_set_bounds(&label, bounds);
    label.size_table = NULL;
    label_update_size_table(&label);
    label.t_widget.set_changed(&label, LABEL_STATE_CHANGED);
    
    return label;
}

void label_update_size_table(Label *label){
    int i, len = strlen(label->text);
    TTF_Font *font = TTF_OpenFont(label->style->font, label->style->size);
    
    
    if(label->size_table == NULL){
        label->size_table = malloc(len * sizeof(Size));
    }
    for(i=0; i<len-1; i++){
        char c = label->text[i+1];
        label->text[i+1] = '\0';
        TTF_SizeUTF8(font, label->text, &label->size_table[i].w, &label->size_table[i].h);
        label->text[i+1] = c;
    }
    TTF_SizeUTF8(font, label->text, &label->size_table[i].w, &label->size_table[i].h);
}

Size label_get_original_size(Label label, int index){
    int len = strlen(label.text);
    if(index >= len){
        return new_Size(-1, -1);
    }
    return label.size_table[index];
}

void label_set_text(Label *label, const char *text){
    string_change(&label->text, text);
}

void label_set_color(Label *label, Color color){
    label->style->color = color;
    label->t_widget.set_changed(label, LABEL_STATE_CHANGED);
}

void label_set_font(Label *label, const char *font){
    snprintf(label->style->font, 60, "./Resources/Fonts/%s.ttf", font);
    //strncpy(label->style->font, font, 60);
    label->t_widget.set_changed(label, LABEL_STATE_CHANGED);
}

void label_set_size(Label *label, int size){
    label->style->size = size;
    label->t_widget.set_changed(label, LABEL_STATE_CHANGED);
}

void label_center(Label *label){
    label->style->center = true;
    label->t_widget.set_changed(label, LABEL_STATE_CENTERED);
}

void label_set_style(Label *label, LabelStyle *style){
    label->style = style;
    label->t_widget.set_changed(label, LABEL_STATE_CHANGED);
}


void generic_label_set_bounds(void *raw_label, SDL_Rect bounds){
    Label *label = raw_label;
    
    if(bounds.w > 0 && bounds.h > 0){
        label->t_widget.widget.state.auto_size = false;
        label->t_widget.set_changed(raw_label, LABEL_STATE_CHANGED);
    }
    
    if(label->t_widget.widget.state.auto_size == true){
        //Size size = label_get_original_size(*label);
        Size size = label_get_original_size(*label, strlen(label->text) - 1);
        bounds.w = size.w;
        bounds.h = size.h;
        label->t_widget.set_changed(raw_label, LABEL_STATE_CHANGED);
    }
    
    set_bounds_from_SDL_Rect(&label->t_widget.widget.bounds, bounds);
}

void generic_label_set_changed(void *raw_label, int changed){
    Label *label = raw_label;
    
    //If they're equal, then don't do anything.
	if(label->t_widget.changed == changed){
		return;
	}

	//If either is false, then it should be false.
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
    
    SDL_RenderCopy(renderer, label->t_widget.texture, &limit, &bounds);
}

void generic_label_update(void *raw_label, SDL_Renderer *renderer){
    Label *label = raw_label;
    
    if(label->t_widget.changed == false){
        return;
    }
    
    TTF_Font *ttf_font = TTF_OpenFont(label->style->font, label->style->size);   
    if(ttf_font == NULL){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Error", TTF_GetError(), NULL);
        exit(1);
    }
    SDL_Surface *surface = NULL;
    if(!label->style->wrap){
        surface = TTF_RenderUTF8_Blended(ttf_font, label->text, label->style->color);
    }else{
        int max_width = widget_get_bounds_origin(raw_label).w;
        surface = TTF_RenderUTF8_Blended_Wrapped(ttf_font, label->text, label->style->color, max_width);
    }
    if(surface == NULL){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Surface Error", TTF_GetError(), NULL);

        TTF_Quit();
        SDL_Quit();

        exit(1);
    }
    TTF_CloseFont(ttf_font);
    ttf_font = NULL;
    
    if(label->t_widget.texture != NULL){
        SDL_DestroyTexture(label->t_widget.texture);
        label->t_widget.texture = NULL;
    }
    label->t_widget.texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_FreeSurface(surface);
    surface = NULL;
    
    if(label->t_widget.texture == NULL){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Texture Error", SDL_GetError(), NULL);
        free(label);

        TTF_Quit();
        SDL_Quit();

        exit(1);
    }

    int texture_width, texture_height;
    
    SDL_QueryTexture(label->t_widget.texture, NULL, NULL, &texture_width, &texture_height);
    
    if(label->t_widget.changed == LABEL_STATE_CENTERED){
        //TO-DO
        /*int txt_x = (label->center_area.x + label->center_area.w/2) - (text_getBounds(label).w)/2;
        int txt_y = (label->center_area.y + label->center_area.h/2) - (text_getBounds(label).h)/2;
        if(txt_x < label->center_area.x){
            txt_x = label->center_area.x;
        }
        if(txt_y < label->center_area.y){
            txt_y = label->center_area.y;
        }
        text_setBounds(label, region_position(txt_x, txt_y));
        */
    }
    
    label->t_widget.set_changed(raw_label, LABEL_STATE_UNCHANGED);
}
