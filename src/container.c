#include "container.h"

//New and free
Container newContainer(ContainerType type, SDL_Rect region){
    Container container = malloc(sizeof(struct Container_));

    int i;
    //Type
    container->type = type;

    //WidgetList
    container->wlist = newWidgetList();

    //Container Attributes
    container->color = default_bg_color;
    resetBounds(&container->region, region);
    container->max_widgets_vertical = MAX_WIDGETS;
    container->max_widgets_horizontal = MAX_WIDGETS;

    //Events and Mouse State
    container->renderer = NULL;
    container->camera = newCamera(container->region.real);
    //container->mouseState = newMouseState();

    //Container Methods
    container->add_widget = container_add_widget_generic;
    container->add_container = container_add_container_generic;
    container->processEvents = container_process_events_generic;
    container->draw = container_draw_generic;

    //Container List
    container->size = 0;
    container->first = 0;
    container->last = 0;
    container->clist = malloc(MAX_CONTAINERS * sizeof(Container));
    for(i=0; i<MAX_CONTAINERS; i++){
        container->clist[i] = NULL;
    }

    return container;
}
void init_container(Container container, SDL_Renderer *renderer){
    int i;
}
void freeContainer(Container container){
    if(container == NULL)
        return;

    int i;

    //Widget List
    freeList(container->wlist);
    container->wlist = NULL;

    //Camera
    container->renderer = NULL;
    freeCamera(container->camera);
    container->camera = NULL;

    //Methods
    container->add_widget = NULL;
    container->add_container = NULL;
    container->processEvents = NULL;
    container->draw = NULL;

    //Container List
    for(i=container->first; i<=container->last; i++){
        freeContainer(container->clist[i]);
        container->clist[i] = NULL;
    }
    free(container->clist);
    container->clist = NULL;

    free(container);
}

//Generic funtions to add widgets and subcontainers
void container_add_widget_generic(Container container, Widget widget){

    init_widget(widget, container->renderer);

    list_add_last(container->wlist, widget);

	//Checking if the object position is "out of bounds" so the camera can reach it too.
	container_update_cameraLimit(container, widget);
}
void container_add_square(Container container, Square sqr){
    container->add_widget(container, newWidget_from_square(sqr));
}
void container_add_frame(Container container, Frame frame){
    container->add_widget(container, newWidget_from_frame(frame));
}
void container_add_image(Container container, Image img){
    container->add_widget(container, newWidget_from_image(img));
}
void container_add_text(Container container, Text txt){
    container->add_widget(container, newWidget_from_text(txt));
}
void container_add_button(Container container, Button btn){
    container->add_widget(container, newWidget_from_button(btn));
}
void container_add_frameChapter(Container container, FrameChapter frameC){
    container->add_widget(container, newWidget_from_frameChapter(frameC));
}

void container_add_container_generic(Container container, Container widget){
}

//Get
SDL_Rect container_getBounds(Container container){
    return getBounds(container->region);
}

//Set
void container_setBounds(Container container, SDL_Rect region){

    SDL_Rect diff;
    SDL_Rect old = container->region.real;
    diff.x = region.x - old.x;
    diff.y = region.y - old.y;
    diff.w = 0;
    diff.h = 0;

    setBounds(&container->region, region);

    if(!list_isEmpty(container->wlist)){
        int i;
        int first = container->wlist->first;
        int last = container->wlist->last;
        for(i=first; i<=last; i++){
            widget_updateBounds(container->wlist->array[i], diff);
        }
    }

}

//Camera
void container_update_cameraLimit(Container container, Widget widget){
    camera_updateLimit(container->camera, widget_getRealBounds(widget));
}


//Generic functions to process events and render.
void container_process_events_generic(Container container, SDL_Event event, Mouse mouseState){
    processEvents_camera(container->camera, event);

    //Call the recursive function to all the subcontainers in clist

    int i;
    int first = container->wlist->first;
    int last = container->wlist->last;
    for(i=first; i<=last; i++){
        widget_processEvents(event, mouseState, container->wlist->array[i]);
        //Checking if the object position is "out of bounds" so the camera can reach it too.
        container_update_cameraLimit(container, container->wlist->array[i]);
    }
    if(mouseOver(container->region)){
        camera_move(container->camera);
    }
}
void container_draw_generic(Container container, SDL_Renderer *renderer){
    //Call the recursive function to all the subcontainers in clist

    int i;
    int first = container->wlist->first;
    int last = container->wlist->last;

    for(i=first; i<=last; i++){
        widget_render(container->wlist->array[i], renderer, container->camera);
    }
}
