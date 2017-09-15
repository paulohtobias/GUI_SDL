#ifndef STYLE_H
#define STYLE_H

#include "border.h"

typedef struct Style{
	Color background_color;
	Border *border;
	
	//Function
	void (*free)(void *);
}Style;

Style new_Style();

Style *new_Style_dinamic();

Color style_get_background_color(Style *style);

void style_set_background_color(Style *style, Color color);

Border *style_get_border(Style *style);

void style_set_border(Style *style, Border *border);

#endif /* STYLE_H */
