#include "containers/hbox.h"

HBox newHBox(){
    HBox hbox = newContainer(CNT_HBOX);

    hbox->add_widget = hbox_add_widget;
    hbox->add_container = hbox_add_container;
    
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

void hbox_add_container(HBox hbox, Container widget){
    SDL_Rect widget_position;
    widget_position = region_position(hbox->region.real.x, hbox->region.real.y);
    
    if(hbox->size > 0){
        SDL_Rect last_widget_region = widget->region.real;
        widget_position.x = region_reachX(last_widget_region);

    }
    container_setBounds(widget, widget_position);

    container_add_container_generic(hbox, widget);
}