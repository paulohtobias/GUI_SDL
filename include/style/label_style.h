#ifndef LABEL_STYLE_H
#define LABEL_STYLE_H

#include "style.h"

#define label_default_color COLOR_BLACK
#define label_default_font "arial"
#define label_default_size 14
#define label_default_reach_table_cache_max_size 1024

typedef struct LabelStyle{
	Style style;
	Color color;
	char font[60];
	int size;
	bool center;
	bool wrap;
} LabelStyle;

LabelStyle label_default_style;

void init_look_and_feel_label();

#endif /* LABEL_STYLE_H */
