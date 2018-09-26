#ifndef LABEL_STYLE_H
#define LABEL_STYLE_H

#include <SDL2/SDL_ttf.h>
#include "utils/utils.h"
#include "basic/color.h"

#define label_default_color COLOR_BLACK
#define label_default_font "arial"
#define label_default_size 14
#define label_default_reach_table_cache_max_size 1024

typedef struct LabelStyle{
	Color color;
	char *font;
	int size;
	SDL_bool center;
	SDL_bool wrap;
} LabelStyle;

LabelStyle label_default_style;

void init_look_and_feel_label();

TTF_Font *label_style_set_font(LabelStyle *style, const char *font);

#endif /* LABEL_STYLE_H */
