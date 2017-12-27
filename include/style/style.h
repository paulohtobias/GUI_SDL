#ifndef STYLE_H
#define STYLE_H

#include "border.h"

typedef struct Style{
	//TO-DO: a pointer to the default widget style and some functions (new, set and copy).
	
	Color background_color;
	Border *border;
	
	//Function
	void (*free)(void *);
}Style;

Style new_Style();

Style *new_Style_dynamic();

Color style_get_background_color(Style *style);

void style_set_background_color(Style *style, Color color);

Border *style_get_border(Style *style);

void style_set_border(Style *style, Border *border);

#endif /* STYLE_H */
