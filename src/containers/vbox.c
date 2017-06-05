#include "containers/vbox.h"

VBox newVBox(SDL_Rect region){
    VBox vbox = newContainer(CNT_VBOX, region);

    vbox->add_widget = vbox_add_widget;
    
    return vbox;
}

void vbox_add_widget(VBox vbox, Widget widget){

    SDL_Rect widget_position;
    widget_position = region_position(vbox->region.real.x, vbox->region.real.y);
    
    if(!list_isEmpty(vbox->wlist)){
        SDL_Rect last_widget_region = widget_getRealBounds(vbox->wlist->array[vbox->wlist->last]);
        widget_position.y = region_reachY(last_widget_region);

    }
    widget_setBounds(widget, widget_position);

    container_add_widget_generic(vbox, widget);
}