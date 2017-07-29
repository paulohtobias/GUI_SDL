#include "widgets/widget.h"

char *_error_widget_message;

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

Widget *new_Widget(Bounds bounds, Color color){
    Widget *widget = malloc(sizeof(Widget));
    
    widget->state = new_WidgetState();
    widget->bounds = bounds;
    widget->background_color = color;
    widget->foreground_color = color;
    
    widget->init = generic_widget_init;
    widget->free = generic_widget_free;
    
    widget->set_bounds = generic_widget_set_bounds;
    widget->get_bounds_with_border = NULL;
    
    widget->process_events = generic_widget_process_events;
    widget->draw = generic_widget_draw;
    
    return widget;
}

Widget *cast_Widget(void *object){
    Widget **widget = malloc(sizeof(Widget*));
    memcpy(widget, object, sizeof(Widget*));
    
    //If object were already a Widget*
    if((*widget)->free == NULL){
        (*widget) = object;
    }
    
    return (*widget);
}

void generic_widget_init(void *widget, SDL_Renderer *renderer){
    //Only used for widgets with a SDL_Texture.
    return;
}

void generic_widget_free(void *widget){
    Widget *widget_ = cast_Widget(widget);
    
    widget_->get_bounds_with_border = NULL;
    widget_->set_bounds = NULL;
    widget_->process_events = NULL;
    widget_->draw = NULL;
    widget_->init = NULL;
    widget_->free = NULL;
    
    free(widget_);
}

void generic_widget_set_bounds(void *widget, Bounds bounds){
    Widget *widget_ = cast_Widget(widget);
    
    widget_->bounds = bounds;
}

void generic_widget_process_events(void *widget, SDL_Event event, Mouse mouse){
    Widget *widget_ = cast_Widget(widget);
    
    widget_->state.mouse_over = false;
    widget_->state.mouse_state = MOUSE_IDLE;
    widget_->state.dragged = false;
    
    if(mouse_over(widget_->bounds)){
        widget_->state.mouse_over = true;
        widget_->state.mouse_state = mouse.button_state;
        
        if(mouse_is_pressed(mouse)){
            widget_->state.focus = true;
            
            //Checking if widget is being dragged.
            if(widget_->state.fixed == false &&
               mouse.button_state == MOUSE_LEFT_PRESSED &&
               event.type == SDL_MOUSEMOTION){

                widget_->state.dragged = true;
            }
        }
    }
}

void widget_update_camera_position(Widget *widget, Camera *camera){
    if(camera != NULL){
        set_position_camera(
            &widget->bounds,
            position_subtract(get_position_origin(widget->bounds), camera_get_position(camera))
        );
    }
}

void widget_draw_border(void *widget, SDL_Renderer *renderer){
    Widget *widget_ = cast_Widget(widget);
    
    //TO-DO: Replace all this with a proper border later. This one is a
    //temporary just for testing.
    int size = 5;
    SDL_Rect bounds = get_bounds_camera(widget_->bounds);
    bounds.x -= size;
    bounds.y -= size;
    bounds.w += (2 * size);
    bounds.h += (2 * size);
    
    set_renderer_draw_color(renderer, COLOR_BLUE);
    SDL_RenderFillRect(renderer, &bounds);
    
    set_renderer_draw_color(renderer, COLOR_YELLOW/*widget_->foreground_color*/);
    bounds = get_bounds_camera(widget_->bounds);
    SDL_RenderFillRect(renderer, &bounds);
}

void generic_widget_draw(void *widget, SDL_Renderer *renderer, Camera *camera){
    Widget *widget_ = cast_Widget(widget);
    
    widget_update_camera_position(widget_, camera);
    
    if(rect_is_inside_rect(get_bounds_camera(widget_->bounds), camera->bounds)){
        widget_draw_border(widget_, renderer);
    }
}
