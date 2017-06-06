#include "containers/vbox.h"

VBox newVBox(){
    VBox vbox = newContainer(CNT_VBOX);

    vbox->add_widget = vbox_add_widget;
    vbox->add_container = vbox_add_container;
    
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

void vbox_add_container(VBox vbox, Container widget){
    SDL_Rect widget_position;
    widget_position = region_position(vbox->region.real.x, vbox->region.real.y);
    
    if(vbox->size > 0){
        SDL_Rect last_widget_region = widget->region.real;
        widget_position.x = region_reachY(last_widget_region);

    }
    container_setBounds(widget, widget_position);

    container_add_container_generic(vbox, widget);
}