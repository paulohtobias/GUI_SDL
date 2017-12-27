#include "style/style.h"

Style new_Style(){
	Style style;
	
	style.background_color = COLOR_PINK;
	style.border = NULL;
	
	return style;
}

Style *new_Style_dynamic(){
	Style *style = malloc(sizeof(Style));
	
	(*style) = new_Style();
	
	return style;
}

Color style_get_background_color(Style *style){
	return style->background_color;
}

void style_set_background_color(Style *style, Color color){
	if(style != NULL){
		style->background_color = color;
	}
}

Border *style_get_border(Style *style){
	if(style != NULL){
		return style->border;
	}
	return NULL;
}

void style_set_border(Style *style, Border *border){
	if(style != NULL){
		style->border = border;
	}
}
