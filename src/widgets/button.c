#include "widgets/button.h"

VT_Widget __gbutton_widget_vt = {
    __button_free,
    __button_set_bounds,
    __button_process_events,
    __container_draw
};

Button new_Button(const char *text, const char *image_file){
	return new_Button_with_bounds(text, image_file, new_rect(0, 0, 0, 0));
}

Button new_Button_with_position(const char *text, const char *image_file, Position position){
	return new_Button_with_bounds(text, image_file, new_rect(position.x, position.y, 0, 0));
}

Button new_Button_with_bounds(const char *text, const char *image_file, SDL_Rect bounds){
	Button button;

	button.container = new_Container_max_widgets(3);

    button.container.widget.functions = &__gbutton_widget_vt;
	button.style_idle = &button_default_style_idle;
	button.style_focused = &button_default_style_focused;
	button.style_pressed = &button_default_style_pressed;
	button.style_disabled = &button_default_style_disabled;

	button.rectangle = malloc(sizeof(Rectangle));
	*button.rectangle = new_Rectangle_with_bounds(button_default_style_idle.bg_color, bounds);
	button.rectangle->t_widget.widget.border = new_Border_dynamic(2, COLOR_BLUE, bounds); //TO-DO: pass the button_default values to the function.
	
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
}
