#include "widgets/texture_widget.h"
#include "utils/exception.h"

TextureWidget new_TextureWidget(){
    TextureWidget t_widget;
    
    t_widget.widget = new_Widget();
    
    t_widget.texture = NULL;
    t_widget.set_changed = NULL;
    t_widget.update = NULL;
    t_widget.render_copy = generic_texture_widget_render_copy;
    t_widget.widget.draw = generic_texture_widget_draw;
    t_widget.widget.free = generic_texture_widget_free;
    
    return t_widget;
}

void generic_texture_widget_free(void *raw_texture_widget){
    TextureWidget *t_widget = raw_texture_widget;

    widget_free(&t_widget->widget);
    
    SDL_DestroyTexture(t_widget->texture);
    
    t_widget->set_changed = NULL;
    t_widget->render_copy = NULL;
    t_widget->update = NULL;
}

void generic_texture_widget_render_copy(void *raw_widget, SDL_Renderer *renderer){
    TextureWidget *t_widget = raw_widget;
    SDL_Rect bounds = get_bounds_camera(t_widget->widget.bounds);
    SDL_RenderCopy(renderer, t_widget->texture, NULL, &bounds);
}

void generic_texture_widget_draw(void *raw_texture_widget, SDL_Renderer *renderer, Camera *camera){
    TextureWidget *t_widget = raw_texture_widget;
    
    if(widget_is_inside_camera(raw_texture_widget, camera)){
        if (t_widget->widget.state.entered_camera == false) {
            t_widget->widget.state.entered_camera = true;
        }

        t_widget->update(raw_texture_widget, renderer);
        
        t_widget->render_copy(raw_texture_widget, renderer);
    }else if(t_widget->widget.state.entered_camera == true){
        t_widget->widget.state.entered_camera = false;

        SDL_DestroyTexture(t_widget->texture);
        t_widget->texture = NULL;

        t_widget->set_changed(raw_texture_widget, true);
    }
}
