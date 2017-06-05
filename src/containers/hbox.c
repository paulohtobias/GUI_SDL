#include "containers/hbox.h"

HBox newHBox(SDL_Rect region){
    HBox hbox = newContainer(CNT_HBOX, region);

    hbox->add_widget = hbox_add_widget;
    
    return hbox;
}

void hbox_add_widget(HBox hbox, Widget widget){
    SDL_Rect widget_position;
    widget_position = region_position(hbox->region.real.x, hbox->region.real.y);
    
    if(!list_isEmpty(hbox->wlist)){
        SDL_Rect last_widget_region = widget_getRealBounds(hbox->wlist->array[hbox->wlist->last]);
        widget_position.x = region_reachX(last_widget_region);

    }
    widget_setBounds(widget, widget_position);

    container_add_widget_generic(hbox, widget);
}