/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * TextureWidget
 * Texture Widget module. Structs and functions basic to all GUI widgets that
 * have an SDL_Texture.
 */

#ifndef TEXTUREWIDGET_H
#define TEXTUREWIDGET_H

#include "widget.h"

/**
 * Functions for <code>TextureWidget</code>.
 * 
 * <code>set_changed</code><br>
 * <code>render_copy</code><br>
 * <code>update</code>
 */
typedef struct VT_TextureWidget{
	void (*set_changed)(void *, int);
    void (*render_copy)(void *, SDL_Renderer *);
    void (*update)(void *, SDL_Renderer *);
}VT_TextureWidget;

typedef struct TextureWidget{
    Widget widget;
    
    SDL_Texture *texture;
    
    int changed;
    
	VT_TextureWidget *functions;
    
}TextureWidget;

TextureWidget new_TextureWidget();

void generic_texture_widget_free(void *t_widget);

void generic_texture_widget_set_changed(void *raw_texture_widget, int changed);

void generic_texture_widget_render_copy(void *raw_widget, SDL_Renderer *renderer);

void generic_texture_widget_draw(void *t_widget, SDL_Renderer *renderer, Camera *camera);

#endif //TEXTUREWIDGET_H
