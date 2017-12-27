#include "widgets/button.h"

VT_Widget __gbutton_widget_vt = {
    generic_button_free,
    generic_button_set_bounds,
    generic_container_process_events,
    generic_container_draw
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
	*button.rectangle = new_Rectangle_with_bounds(button_default_style_idle.style.background_color, bounds);
	style_set_border(button.rectangle->widget.style, new_Border_dynamic(2, COLOR_BLUE, bounds)); //pass the button_default values to the function.
	
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


void generic_button_free(void *raw_button){
    
}

void generic_button_set_bounds(void *raw_button, SDL_Rect bounds){
    Button *button = raw_button;
    
    widget_set_bounds(button->rectangle, bounds);
    if(button->image != NULL){
        widget_set_bounds(button->image, bounds);
    }
    if(button->label != NULL){
        widget_set_bounds(button->label, bounds);
    }
    
    set_bounds_from_SDL_Rect(&button->container.widget.bounds, bounds);
}

void generic_button_process_events(void *raw_button, SDL_Event event, Mouse mouse){
	Button *button = raw_button;
	
	generic_container_process_events(raw_button, event, mouse);
	
	ButtonStyle *current_style = button->style_idle;
	if(button->container.widget.state.mouse_state == MOUSE_LEFT_PRESSED){
		*((Style *)button->rectangle->widget.style) = button->style_pressed->style;
	}
}
