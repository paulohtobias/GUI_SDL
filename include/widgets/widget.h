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

typedef struct WidgetSate_{
    ///The widget has focus.
    bool focus;
    
    ///The widget can't be dragged.
    bool fixed;
    
    ///The widget is being dragged.
    bool dragged;
    
    ///Mouse cursor is over widget.
    bool mouse_over;
    
    ///Mouse button information.
    MouseButtonState mouse_state;
    
    ///Widget entered camera bounds.
    bool entered_camera;
    
    ///Widget attribute was changed. Used in internal functions only.
    bool changed;
}WidgetSate;

typedef struct Widget_{
    WidgetSate state;
    Bounds bounds;
    
    Color foreground_color;
    Color background_color;
    
    //Functions
    void (*set_bounds)(void *, Bounds);
    Bounds (*get_bounds_with_border)(void *);
    
    void (*process_events)(void *, SDL_Event, Mouse);
    void (*draw)(void *, SDL_Renderer *, Camera *);
    
    void (*free)();
}Widget;

WidgetSate new_WidgetState();

Widget *new_Widget(Bounds bounds, Color color);

Widget *cast_Widget(void *object);

void generic_widget_set_bounds(void *widget, Bounds bounds);

void generic_widget_process_events(void *widget, SDL_Event event, Mouse mouse);

void widget_update_camera_position(Widget *widget, Camera *camera);

void widget_draw_border(void *widget, SDL_Renderer *renderer);

void generic_widget_draw(void *widget, SDL_Renderer *renderer, Camera *camera);

void generic_widget_pass();

#endif //WIDGET_H
