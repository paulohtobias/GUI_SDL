#include "widgets/button.h"

SDL_bool __button_vt_was_init = SDL_FALSE;

void __button_vt_init(){
	if(__button_vt_was_init){
		return;
	}
	
	__gbutton_widget_vt = __gcontainer_widget_vt;
	__gbutton_widget_vt.free = __button_free;
	__gbutton_widget_vt.set_bounds = __button_set_bounds;
	__gbutton_widget_vt.process_events = __button_process_events;
	
	__button_vt_was_init = SDL_TRUE;
}

Button new_Button(const char *text, const char *image_file){
	return new_Button_with_bounds(text, image_file, new_rect(0, 0, 0, 0));
}

Button new_Button_with_position(const char *text, const char *image_file, Position position){
	return new_Button_with_bounds(text, image_file, new_rect(position.x, position.y, 0, 0));
}

Button new_Button_with_bounds(const char *text, const char *image_file, SDL_Rect bounds){
	Button button;

	button.container = new_Container_max_widgets(3);

	__button_vt_init();
    button.container.widget.functions = &__gbutton_widget_vt;
	button.style_idle = &button_default_style_idle;
	button.style_focused = &button_default_style_focused;
	button.style_pressed = &button_default_style_pressed;
	button.style_disabled = &button_default_style_disabled;

	button.rectangle = malloc(sizeof(Rectangle));
	*button.rectangle = new_Rectangle_with_bounds(button_default_style_idle.bg_color, bounds);
	
	container_add_widget(&button, button.rectangle);

	button.image = NULL;
	if(image_file != NULL){
		button.image = malloc(sizeof(Image));
		*button.image = new_Image_with_bounds(image_file, bounds);
		container_add_widget(&button, button.image);
	}
	
	button.label = NULL;
	if(text != NULL){
		button.label = malloc(sizeof(Label));
		(*button.label) = new_Label_with_bounds(text, bounds);
		label_set_style(button.label, button_default_style_idle.label_style);
		container_add_widget(&button, button.label);
	}

	widget_set_bounds(&button, bounds);

	return button;
}


void __button_free(void *__button){
    
}

void __button_set_bounds(void *__button, SDL_Rect bounds){
    Button *button = __button;
    
    widget_set_bounds(button->rectangle, bounds);
    if(button->image != NULL){
        widget_set_bounds(button->image, bounds);
    }
    if(button->label != NULL){
        widget_set_bounds(button->label, bounds);
    }
    
    set_bounds_from_SDL_Rect(&button->container.widget.bounds, bounds);
}

void __button_process_events(void *__button, SDL_Event event, Mouse mouse){
	Button *button = __button;
	
	__container_process_events(__button, event, mouse);
	
	ButtonStyle *current_style = button->style_idle;
	if(button->container.widget.state.mouse_state == MOUSE_LEFT_PRESSED){
		current_style = button->style_pressed;
	}else if(button->container.widget.state.mouse_over){
		current_style = button->style_focused;
	}
	
	rectangle_set_color(button->rectangle, current_style->bg_color);
	widget_set_border(button->rectangle, current_style->border);
	
	if(button->label != NULL){
		label_set_style(button->label, current_style->label_style);
	}
}
