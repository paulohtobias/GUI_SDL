/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Widget
 * Basic Widget module. Structs and functions basic to all GUI widgets.
 */

#include "widgets/widget.h"

WidgetSate new_WidgetState(){
    WidgetSate state;
    
    state.focus = false;
    state.fixed = true;
    state.dragged = false;
    state.mouse_over = false;
    state.mouse_state = MOUSE_IDLE;
    state.entered_camera = true;
    state.changed = false;
    
    return state;
}

Widget new_Widget(){
    Widget widget;
    
    widget.state = new_WidgetState();
    widget.bounds = new_Bounds_from_integer(0, 0, 0, 0);
    widget.background_color = COLOR_ORANGE;
    widget.foreground_color = COLOR_GREEN;
    
    widget.free = generic_widget_free;
    
    widget.set_bounds = generic_widget_set_bounds;
    
    widget.process_events = generic_widget_process_events;
    widget.draw = generic_widget_draw;
    
    return widget;
}

void widget_free(void *widget){
    ((Widget *)widget)->free(widget);
}

SDL_Rect widget_get_bounds_origin(void *widget){
    return get_bounds_origin(((Widget *)widget)->bounds);
}

SDL_Rect widget_get_bounds_camera(void *widget){
    return get_bounds_camera(((Widget *)widget)->bounds);
}

void widget_set_bounds(void *widget, SDL_Rect bounds){
    ((Widget *)widget)->set_bounds(widget, bounds);
}

void widget_process_events(void *widget, SDL_Event event, Mouse mouse){
    ((Widget *)widget)->process_events(widget, event, mouse);
}

void widget_update_camera_position(void *raw_widget, Camera *camera){
    if(camera != NULL){
        Widget *widget = raw_widget;
        set_position_camera(
            &widget->bounds,
            position_subtract(get_position_origin(widget->bounds), camera_get_position(camera))
        );
    }
}

bool widget_is_inside_camera(void *raw_widget, Camera *camera){
    if(camera == NULL){
        return true;
    }
    Widget *widget = raw_widget;
    return position_is_inside_rect(get_position_camera(widget->bounds), camera_get_bounds(camera));
}

void widget_draw_border(void *raw_widget, SDL_Renderer *renderer){
    Widget *widget = raw_widget;
    
    //TO-DO: Replace all this with a proper border later. This one is a
    //temporary just for testing.
    int size = 5;
    SDL_Rect bounds = get_bounds_camera(widget->bounds);
    bounds.x -= size;
    bounds.y -= size;
    bounds.w += (2 * size);
    bounds.h += (2 * size);
    
    set_renderer_draw_color(renderer, COLOR_BLUE);
    SDL_RenderFillRect(renderer, &bounds);
    
    set_renderer_draw_color(renderer, COLOR_YELLOW/*widget->foreground_color*/);
    bounds = get_bounds_camera(widget->bounds);
    SDL_RenderFillRect(renderer, &bounds);
}

void widget_draw(void *raw_widget, SDL_Renderer *renderer, Camera *camera){
    widget_update_camera_position(raw_widget, camera);
    
    Widget *widget = raw_widget;
    widget->draw(raw_widget, renderer, camera);
}


void generic_widget_free(void *raw_widget){
    Widget *widget = raw_widget;
    
    widget->set_bounds = NULL;
    widget->process_events = NULL;
    widget->draw = NULL;
    widget->free = NULL;
}

void generic_widget_set_bounds(void *raw_widget, SDL_Rect bounds){
    Widget *widget = raw_widget;
    
    set_bounds_from_SDL_Rect(&widget->bounds, bounds);
}

void generic_widget_process_events(void *raw_widget, SDL_Event event, Mouse mouse){
    Widget *widget = raw_widget;
    
    widget->state.mouse_over = false;
    widget->state.mouse_state = MOUSE_IDLE;
    widget->state.dragged = false;
    
    if(mouse_over(widget->bounds)){
        widget->state.mouse_over = true;
        widget->state.mouse_state = mouse.button_state;
        
        if(mouse_is_pressed(mouse)){
            widget->state.focus = true;
            
            //Checking if widget is being dragged.
            if(widget->state.fixed == false &&
               mouse.button_state == MOUSE_LEFT_PRESSED &&
               event.type == SDL_MOUSEMOTION){

                widget->state.dragged = true;
            }
        }
    }
}

void generic_widget_draw(void *raw_widget, SDL_Renderer *renderer, Camera *camera){
    Widget *widget = raw_widget;
    
    if(widget_is_inside_camera(raw_widget, camera)){
        widget_draw_border(widget, renderer);
    }
}
