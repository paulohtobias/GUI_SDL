/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Widget
 * Basic Widget module. Structs and functions basic to all GUI widgets.
 */

#ifndef WIDGET_H
#define WIDGET_H

#include "basic/mouse.h"
#include "style/border.h"

/**
 * Functions for <code>Widget</code>.
 * 
 * <code>free</code><br>
 * <code>get_bounds</code><br>
 * <code>set_bounds</code><br>
 * <code>set_border</code><br>
 * <code>process_events</code><br>
 * <code>draw</code><br>
 */
typedef struct VT_Widget{
	void (*free)(void *);
	Bounds (*get_bounds)(void *);
	void (*set_bounds)(void *, SDL_Rect);
	void (*set_border)(void *, void *);

	void (*process_events)(void *, SDL_Event, Mouse);
	void (*draw)(void *, RenderData *);
} VT_Widget;

///Global virtual table.
VT_Widget __gwidget_vt;

///TO-DO: change this to a enum and each state is a bit to use less memory.
typedef struct WidgetSate{
	SDL_bool focus; ///The widget has focus.
	SDL_bool fixed; ///The widget can't be dragged.
	SDL_bool dragged; ///The widget is being dragged.
	SDL_bool mouse_over; ///Mouse cursor is over widget.
	MouseButtonState mouse_state; ///Mouse button information.
	SDL_bool auto_size; ///Widget size is defined automatically.
	SDL_bool entered_camera; ///Widget entered camera bounds.
} WidgetSate;

typedef struct Widget{
	WidgetSate state;
	Bounds bounds;
	
	Border *border;

	//Functions
	VT_Widget *functions;
} Widget;

WidgetSate new_WidgetState();

Widget new_Widget();

void widget_free(void *widget);

SDL_Rect widget_get_bounds_local(void *widget);

SDL_Rect widget_get_bounds_global(void *widget);

SDL_Rect widget_get_bounds_camera(void *widget, Camera *camera);

Bounds widget_get_bounds(void *widget);

void widget_set_bounds(void *widget, SDL_Rect bounds);

void widget_set_border(void *widget, void *border);

void widget_process_events(void *widget, SDL_Event event, Mouse mouse);

SDL_bool widget_is_inside_camera(void *__widget, Camera *camera);

SDL_Rect widget_get_drawable_area(void *__widget, SDL_Rect *dst_bounds, Camera *camera);

void widget_draw(void *__widget, RenderData *data);


void __widget_free(void *__widget);

Bounds __widget_get_bounds(void *__widget);

void __widget_set_bounds(void *__widget, SDL_Rect bounds);

void __widget_set_border(void *__widget, void *border);

void __widget_process_events(void *__widget, SDL_Event event, Mouse mouse);

#endif //WIDGET_H
