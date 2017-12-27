/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Widget
 * Basic Widget module. Structs and functions basic to all GUI widgets.
 */

#include "widgets/widget.h"

VT_Widget __gwidget_vt = {
	__widget_free,
	__widget_set_bounds,
	__widget_process_events,
	__widget_draw
};

WidgetSate new_WidgetState(){
	WidgetSate state;

	state.focus = false;
	state.fixed = true;
	state.dragged = false;
	state.mouse_over = false;
	state.mouse_state = MOUSE_IDLE;
	state.entered_camera = true;
	state.auto_size = true;

	return state;
}

Widget new_Widget(){
	Widget widget;

	widget.functions = &__gwidget_vt;
	
	widget.state = new_WidgetState();
	widget.bounds = new_Bounds_from_integer(0, 0, 0, 0);
	widget.style = NULL;

	return widget;
}

void widget_free(void *widget){
	((Widget *) widget)->functions->free(widget);
}

SDL_Rect widget_get_bounds_origin(void *widget){
	return get_bounds_origin(((Widget *) widget)->bounds);
}

SDL_Rect widget_get_bounds_camera(void *widget){
	return get_bounds_camera(((Widget *) widget)->bounds);
}

void widget_set_bounds(void *widget, SDL_Rect bounds){
	((Widget *) widget)->functions->set_bounds(widget, bounds);
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

bool widget_is_inside_camera(void *__widget, Camera *camera){
	if(camera == NULL){
		return true;
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
	Widget *widget = __widget;

	widget->functions->set_bounds = NULL;
	widget->functions->process_events = NULL;
	widget->functions->draw = NULL;
	widget->functions->free = NULL;
}

void __widget_set_bounds(void *__widget, SDL_Rect bounds){
	Widget *widget = __widget;

	if(bounds.w > 0 && bounds.h > 0){
		widget->state.auto_size = false;
	}
	set_bounds_from_SDL_Rect(&widget->bounds, bounds);
}

void __widget_process_events(void *__widget, SDL_Event event, Mouse mouse){
	Widget *widget = __widget;

	widget->state.mouse_over = false;
	widget->state.mouse_state = MOUSE_IDLE;
	widget->state.dragged = false;

	if(mouse_over(widget->bounds)){
		widget->state.mouse_over = true;
		widget->state.focus = true;

		if(mouse_is_pressed(mouse)){
			widget->state.mouse_state = mouse.button_state;

			//Checking if widget is being dragged.
			if(widget->state.fixed == false &&
				mouse.button_state == MOUSE_LEFT_PRESSED &&
				event.type == SDL_MOUSEMOTION){

				widget->state.dragged = true;
			}
		}
	}
}

void __widget_draw(void *__widget, SDL_Renderer *renderer, Camera *camera){
	Widget *widget = __widget;

	if(widget_is_inside_camera(__widget, camera) && widget->style != NULL){
		border_draw(style_get_border(widget->style), renderer, camera);
	}
}
