#include "style/style.h"

Style new_Style(){
	Style style;
	
	style.background_color = COLOR_PINK;
	style.border = NULL;
	
	return style;
}

Style *new_Style_dinamic(){
	Style *style = malloc(sizeof(Style));
	
	(*style) = new_Style();
	
	return style;
}
