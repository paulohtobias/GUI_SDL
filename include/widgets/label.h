#ifndef LABEL_H
#define LABEL_H

#include "texture_widget.h"
#include <SDL2/SDL_ttf.h>

typedef enum LabelState{
    LABEL_STATE_UNCHANGED,
    LABEL_STATE_CHANGED,
    LABEL_STATE_CENTERED
}LabelState;

typedef struct LabelStyle{
    Color color;
    char font[60];
    int size;
    bool center;
    bool wrap;
}LabelStyle;

#define label_default_color COLOR_BLACK
#define label_default_font "arial"
#define label_default_size 14

LabelStyle label_default_style;

typedef struct Label{
    TextureWidget t_widget;
    
    char *text;
    Size real_size;
    LabelStyle *style;
}Label;

Label new_Label(const char *text);

Label new_Label_with_position(const char *text, Position position);

Label new_Label_with_bounds(const char *text, SDL_Rect bounds);

Size label_get_original_size(Label label);

void label_set_text(Label *label, const char *text);

void label_set_color(Label *label, Color color);

void label_set_font(Label *label, const char *font);

void label_set_size(Label *label, int size);

void label_center(Label *label);

void label_set_style(Label *label, LabelStyle *style);


void generic_label_set_bounds(void *raw_label, SDL_Rect bounds);

void generic_label_set_changed(void *raw_label, bool changed);

void generic_label_render_copy(void *raw_label, SDL_Renderer *renderer);

void generic_label_update(void *raw_label, SDL_Renderer *renderer);

#endif //LABEL_H
