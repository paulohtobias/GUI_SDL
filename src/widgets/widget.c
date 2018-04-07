/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Widget
 * Basic Widget module. Structs and functions basic to all GUI widgets.
 */

#include "widgets/widget.h"

SDL_bool __widget_vt_was_init = SDL_FALSE;

void __widget_vt_init(){
	if(__widget_vt_was_init){
		return;
	}
	
	__gwidget_vt.free = __widget_free;
	__gwidget_vt.get_bounds = __widget_get_bounds;
	__gwidget_vt.set_bounds = __widget_set_bounds;
	__gwidget_vt.set_border =__widget_set_border;
	__gwidget_vt.process_events = __widget_process_events;
	__gwidget_vt.draw = __widget_draw;
	
	__widget_vt_was_init = SDL_TRUE;
}

WidgetSate new_WidgetState(){
	WidgetSate state;

	state.focus = SDL_FALSE;
	state.fixed = SDL_TRUE;
	state.dragged = SDL_FALSE;
	state.mouse_over = SDL_FALSE;
	state.mouse_state = MOUSE_IDLE;
	state.entered_camera = SDL_TRUE;
	state.auto_size = SDL_TRUE;

	return state;
}

Widget new_Widget(){
	__widget_vt_init();
	
	Widget widget;

	widget.functions = &__gwidget_vt;
	
	widget.state = new_WidgetState();
	widget.bounds = new_Bounds_from_integer(0, 0, 0, 0);
	widget.border = NULL;

	return widget;
}

void widget_free(void *widget){
	((Widget *) widget)->functions->free(widget);
}

SDL_Rect widget_get_bounds_origin(void *widget){
	return get_bounds_origin(widget_get_bounds(widget));
}

SDL_Rect widget_get_bounds_camera(void *widget){
	return get_bounds_camera(widget_get_bounds(widget));
}

Bounds widget_get_bounds(void *widget){
	return ((Widget *) widget)->functions->get_bounds(widget);
}

void widget_set_bounds(void *widget, SDL_Rect bounds){
	((Widget *) widget)->functions->set_bounds(widget, bounds);
}

void widget_set_border(void *widget, void *border){
	((Widget *) widget)->functions->set_border(widget, border);
}

void widget_process_events(void *widget, SDL_Event event, Mouse mouse){
	((Widget *) widget)->functions->process_events(widget, event, mouse);
}

void widget_update_camera_position(void *__widget, Camera *camera){
	if(camera != NULL){
		Widget *widget = __widget;
		set_position_camera(
			&widget->bounds,
			position_subtract(get_position_origin(widget->bounds), camera_get_position(camera))
			);
	}
}

SDL_bool widget_is_inside_camera(void *__widget, Camera *camera){
	if(camera == NULL){
		return SDL_TRUE;
	}
	Widget *widget = __widget;
	return position_is_inside_rect(get_position_camera(widget->bounds), camera_get_bounds(camera));
}

void widget_draw(void *__widget, SDL_Renderer *renderer, Camera *camera){
	//widget_update_camera_position(__widget, camera);

	Widget *widget = __widget;
	widget->functions->draw(__widget, renderer, camera);
}


void __widget_free(void *__widget){
}

Bounds __widget_get_bounds(void *__widget){
	return ((Widget *) __widget)->bounds;
}

void __widget_set_bounds(void *__widget, SDL_Rect bounds){
	Widget *widget = __widget;

	if(bounds.w > 0 && bounds.h > 0){
		widget->state.auto_size = SDL_FALSE;
	}
	set_bounds_from_SDL_Rect(&widget->bounds, bounds);
	border_set_bounds(widget->border, widget_get_bounds_camera(widget));
}

void __widget_set_border(void *__widget, void *border){
	Widget *widget = __widget;
	
	border_set_bounds(border, widget_get_bounds_camera(widget));
	widget->border = border;
}

void __widget_process_events(void *__widget, SDL_Event event, Mouse mouse){
	Widget *widget = __widget;

	widget->state.mouse_over = SDL_FALSE;
	widget->state.mouse_state = MOUSE_IDLE;
	widget->state.dragged = SDL_FALSE;

	if(mouse_over(widget->bounds)){
		widget->state.mouse_over = SDL_TRUE;
		widget->state.focus = SDL_TRUE;

		if(mouse_is_pressed(mouse)){
			widget->state.mouse_state = mouse.button_state;

			//Checking if widget is being dragged.
			if(widget->state.fixed == SDL_FALSE &&
				mouse.button_state == MOUSE_LEFT_PRESSED &&
				event.type == SDL_MOUSEMOTION){

				widget->state.dragged = SDL_TRUE;
			}
		}
	}
}

void __widget_draw(void *__widget, SDL_Renderer *renderer, Camera *camera){
	Widget *widget = __widget;

	if(widget_is_inside_camera(__widget, camera)){
		border_draw(widget->border, renderer, camera);
	}
}
