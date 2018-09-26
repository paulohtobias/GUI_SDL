#include "style/button_style.h"

void __init_button_style(ButtonStyle *button_style, Color border_color, Color bg_color, Color text_color){
	button_style->bg_color = bg_color;
	button_style->border = new_Border_dynamic(button_default_border_size, border_color, new_rect(0, 0, 0, 0));
	button_style->label_style = malloc(sizeof(LabelStyle));
    *button_style->label_style = label_default_style;
	button_style->label_style->color = text_color;
    button_style->label_style->center = SDL_TRUE;
}

void init_look_and_feel_button(){
	__init_button_style(&button_default_style_idle, button_default_border_color_idle, button_default_bg_color_idle, label_default_color);
	__init_button_style(&button_default_style_focused, button_default_border_color_focused, button_default_bg_color_focused, label_default_color);
	__init_button_style(&button_default_style_pressed, button_default_border_color_pressed, button_default_bg_color_pressed, label_default_color);
	__init_button_style(&button_default_style_disabled, button_default_border_color_disabled, button_default_bg_color_disabled, button_default_label_color_disabled);
}

void __free_button_style(void *__button_style){
	ButtonStyle *button_style = __button_style;
	
	border_free(button_style->border);
	free(button_style->label_style);
}
