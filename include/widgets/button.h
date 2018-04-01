#ifndef BUTTON_H
#define BUTTON_H

#include "containers/container.h"
#include "rectangle.h"
#include "label.h"
#include "image.h"
#include "style/button_style.h"

///Global virtual tables.
VT_Widget __gbutton_widget_vt;

typedef struct Button{
	Container container;

	Rectangle *rectangle;
	Label *label;
	Image *image;

	ButtonStyle *style_idle;
	ButtonStyle *style_focused;
	ButtonStyle *style_pressed;
	ButtonStyle *style_disabled;
} Button;

Button new_Button(const char *text, const char *image);

Button new_Button_with_position(const char *text, const char *image, Position position);

Button new_Button_with_bounds(const char *text, const char *image, SDL_Rect bounds);


void __button_free(void *__button);

void __button_set_bounds(void *__button, SDL_Rect bounds);

void __button_process_events(void *__button, SDL_Event event, Mouse mouse);

#endif //BUTTON_H
