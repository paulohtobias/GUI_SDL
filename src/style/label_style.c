#include "style/label_style.h"

void init_look_and_feel_label(){
	label_default_style.color = label_default_color;
	label_default_style.size = label_default_size;
	label_default_style.center = SDL_FALSE;
	label_default_style.wrap = SDL_FALSE;
	label_style_set_font(&label_default_style, label_default_font);
}

TTF_Font *label_style_set_font(LabelStyle *style, const char *font) {
	TTF_Font *ttf_font = NULL;
	char *file = str_from_file(".config/fonts");
	char *font_path = strtok(file, ";");
	size_t font_len = strlen(font);
	while (font_path != NULL) {
		style->font = malloc(strlen(font_path) + font_len + 6);
		sprintf(style->font, "%s/%s.ttf", font_path, font);

		printf("Loading %s\n", style->font);
		ttf_font = TTF_OpenFont(style->font, style->size);

		if (ttf_font != NULL) {
			break;
		}

		free(style->font);

		font_path = strtok(NULL, ";");
	}

	free(file);

	return ttf_font;
}
