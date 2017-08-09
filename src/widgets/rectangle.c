#include "widgets/rectangle.h"

Rectangle new_Rectangle(Color color){
    return new_Rectangle_with_bounds(color, new_rect(0, 0, 0, 0));
}

Rectangle new_Rectangle_with_position(Color color, Position position){
    return new_Rectangle_with_bounds(color, new_rect(position.x, position.y, 0, 0));
}

Rectangle new_Rectangle_with_bounds(Color color, SDL_Rect bounds){
    Rectangle rectangle = new_TextureWidget();
    
    rectangle.widget.background_color = color;
    rectangle.widget.set_bounds = generic_rectangle_set_bounds;
    rectangle.update = generic_rectangle_update;
    
    widget_set_bounds(&rectangle, bounds);
    
    return rectangle;
}

void generic_rectangle_set_bounds(void *raw_rectangle, SDL_Rect bounds){
    generic_widget_set_bounds(raw_rectangle, bounds);
    ((Rectangle *)raw_rectangle)->set_changed(raw_rectangle, true);
}

void generic_rectangle_update(void *raw_rectangle, SDL_Renderer *renderer){
    Rectangle *rectangle = raw_rectangle;
    
    if(!rectangle->changed){
        return;
    }
    
    // load the image data into the graphics hardware's memory
    if(rectangle->texture != NULL){
        SDL_DestroyTexture(rectangle->texture);
        rectangle->texture = NULL;
    }
    
    Size size = rectangle->widget.bounds.size;
    if(size.w == 0 || size.h == 0){
        return;
    }
    
    rectangle->texture = SDL_CreateTexture(renderer,
                                           SDL_PIXELFORMAT_RGBA8888,
                                           SDL_TEXTUREACCESS_TARGET,
                                           size.w, size.h);
    
    if(rectangle->texture == NULL){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error creating image texture",
                                 SDL_GetError(), NULL);
        
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        exit(1);
    }
    //image_setBounds(img, image_getBounds(img));
    SDL_SetTextureBlendMode(rectangle->texture, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, rectangle->texture);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    set_renderer_draw_color(renderer, rectangle->widget.background_color);
    SDL_RenderFillRect(renderer, NULL);
    
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    
    rectangle->set_changed(raw_rectangle, false);
}
