#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL_ttf.h>
#include "texture_widget.h"
#include "style/label_style.h"

///Global virtual tables.
VT_Widget __glabel_widget_vt;
VT_TextureWidget __glabel_twidget_vt;

typedef struct Label{
	TextureWidget t_widget;

	char *text;
	Size *size_table;
	
	LabelStyle *style;
} Label;

Label new_Label(const char *text);

Label new_Label_with_position(const char *text, Position position);

Label new_Label_with_bounds(const char *text, SDL_Rect bounds);

void label_update_size_table(Label *label, TTF_Font *font);

Size label_get_original_size(Label label, int index);

void label_set_text(Label *label, const char *text);

Color label_get_color(Label *label);

void label_set_color(Label *label, Color color);

char *label_get_font(Label *label);

void label_set_font(Label *label, const char *font);

int label_get_font_size(Label *label);

void label_set_font_size(Label *label, int size);

SDL_bool label_get_center(Label *label);

void label_set_center(Label *label, SDL_bool center);

SDL_bool label_get_wrap(Label *label);

void label_set_wrap(Label *label, SDL_bool wrap);

void label_set_style(Label *label, LabelStyle *style);

SDL_Rect label_get_center_bounds(Label *label, SDL_Rect area);


void __label_free(void *__label);

void __label_set_bounds(void *__label, SDL_Rect bounds);

void __label_render_copy(void *__label, RenderData *data);

void __label_update(void *__label, SDL_Renderer *renderer);

#endif //LABEL_H
