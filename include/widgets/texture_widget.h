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
} VT_TextureWidget;

///Global virtual tables.
VT_Widget __gtwidget_widget_vt;
VT_TextureWidget __gtwidget_vt;

typedef struct TextureWidget{
	Widget widget;

	SDL_Texture *texture;

	int changed;

	VT_TextureWidget *functions;

} TextureWidget;

TextureWidget new_TextureWidget();

int texture_widget_get_changed(void *t_widget);

void texture_widget_set_changed(void *t_widget, int changed);


void __texture_widget_free(void *t_widget);

void __texture_widget_set_changed(void *__texture_widget, int changed);

void __texture_widget_render_copy(void *__widget, SDL_Renderer *renderer);

void __texture_widget_draw(void *t_widget, SDL_Renderer *renderer);

#endif //TEXTUREWIDGET_H
