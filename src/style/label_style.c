#include "style/label_style.h"

void init_look_and_feel_label(){
	label_default_style.color = label_default_color;
	snprintf(label_default_style.font, 60, "./Resources/Fonts/%s.ttf", label_default_font);
	label_default_style.size = label_default_size;
	label_default_style.center = false;
	label_default_style.wrap = false;
}
