/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Widget
 * Basic Widget module. Structs and functions basic to all GUI widgets.
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <basic/bounds.h>
#include <basic/mouse.h>
#include <basic/color.h>
#include "camera.h"

/**
 * Functions for <code>Widget</code>.
 * 
 * <code>free</code><br>
 * <code>set_bounds</code><br>
 * <code>process_events</code><br>
 * <code>draw</code><br>
 */
typedef struct VT_Widget{
	void (*free)();
	void (*set_bounds)(void *, SDL_Rect);

	void (*process_events)(void *, SDL_Event, Mouse);
	void (*draw)(void *, SDL_Renderer *, Camera *);
} VT_Widget;

///TO-DO: change this to a enum and each state is a bit to use less memory.

typedef struct WidgetSate{
	bool focus; ///The widget has focus.
	bool fixed; ///The widget can't be dragged.
	bool dragged; ///The widget is being dragged.
	bool mouse_over; ///Mouse cursor is over widget.
	MouseButtonState mouse_state; ///Mouse button information.
	bool auto_size; ///Widget size is defined automatically.
	bool entered_camera; ///Widget entered camera bounds.
} WidgetSate;

typedef struct Widget{
	WidgetSate state;
	Bounds bounds;

	Color background_color;

	//Functions
	VT_Widget *functions;
} Widget;

WidgetSate new_WidgetState();

Widget new_Widget();

void widget_free(void *widget);

SDL_Rect widget_get_bounds_origin(void *widget);

SDL_Rect widget_get_bounds_camera(void *widget);

void widget_set_bounds(void *widget, SDL_Rect bounds);

void widget_process_events(void *widget, SDL_Event event, Mouse mouse);

void widget_update_camera_position(void *raw_widget, Camera *camera);

bool widget_is_inside_camera(void *raw_widget, Camera *camera);

void widget_draw_border(void *raw_widget, SDL_Renderer *renderer);

void widget_draw(void *raw_widget, SDL_Renderer *renderer, Camera *camera);


void generic_widget_free(void *raw_widget);

void generic_widget_set_bounds(void *raw_widget, SDL_Rect bounds);

void generic_widget_process_events(void *raw_widget, SDL_Event event, Mouse mouse);

void generic_widget_draw(void *raw_widget, SDL_Renderer *renderer, Camera *camera);

#endif //WIDGET_H
