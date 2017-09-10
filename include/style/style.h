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

//TO-DO: create setters and getters fot style

#endif /* STYLE_H */
