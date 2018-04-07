#ifndef BUTTON_STYLE_H
#define BUTTON_STYLE_H

#include "label_style.h"
#include "style/border.h"

#define button_default_border_size 1
#define button_default_label_color_disabled COLOR_GREY(131)
#define button_default_bg_color_idle COLOR_GREY(225)
#define button_default_bg_color_focused COLOR_GREY(225)
#define button_default_bg_color_pressed COLOR_RGB(204, 228, 247)
#define button_default_bg_color_disabled COLOR_GREY(204)
#define button_default_border_color_idle COLOR_GREY(173)
#define button_default_border_color_focused COLOR_RGB(0, 120, 215)
#define button_default_border_color_pressed COLOR_RGB(0, 84, 153)
#define button_default_border_color_disabled COLOR_GREY(191)

//TO-DO: fix button style
typedef struct ButtonStyle{
	Color bg_color;
	Border *border; ///A pointer to the button widget border style.
	LabelStyle *label_style;
} ButtonStyle;

ButtonStyle button_default_style_idle;
ButtonStyle button_default_style_focused;
ButtonStyle button_default_style_pressed;
ButtonStyle button_default_style_disabled;

void init_look_and_feel_button();

void free_button_style(void *__button_style);

#endif /* BUTTON_STYLE_H */
