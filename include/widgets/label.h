#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL_ttf.h>
#include "texture_widget.h"
#include "style/label_style.h"

typedef struct Label{
	TextureWidget t_widget;

	char *text;
	Size *size_table;
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

int label_get_size(Label *label);

void label_set_size(Label *label, int size);

bool label_get_center(Label *label);

void label_set_center(Label *label, bool center);

bool label_get_wrap(Label *label);

void label_set_wrap(Label *label, bool wrap);

void label_set_style(Label *label, LabelStyle *style);

SDL_Rect label_get_center_bounds(Label *label, Size *real_size);


void generic_label_free(void *raw_label);

void generic_label_set_bounds(void *raw_label, SDL_Rect bounds);

void generic_label_render_copy(void *raw_label, SDL_Renderer *renderer);

void generic_label_update(void *raw_label, SDL_Renderer *renderer);

#endif //LABEL_H
