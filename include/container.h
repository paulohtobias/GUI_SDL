#ifndef CONTAINER_H
#define CONTAINER_H

#include "widget.h"

typedef enum{
    CNT_FIXED,
    CNT_VBOX,
    CNT_HBOX,
    CNT_TABLE,
    CNT_COUNT
}ContainerType;

#define default_bg_color COLOR_GREY(240)
#define MAX_CONTAINERS 20
struct Container_{
    //The container type
    ContainerType type;

    //Widget List
    WidgetList wlist;

    //Container Attributes
    SDL_Color color;
    //padding
    Bounds region;
    int max_widgets_vertical;
    int max_widgets_horizontal;

    //Camera
    SDL_Renderer *renderer;
    Camera camera;
    //Mouse mouseState;
    //ScrollBar scrollbar;

    //Container Methods
    void (*processEvents)(struct Container_*, SDL_Event, Mouse);
    void (*draw)(struct Container_*, SDL_Renderer *);
    void (*add_widget)(struct Container_*, Widget);
    void (*add_container)(struct Container_*, struct Container_*);

    //Container List
    int size;
    int first;
    int last;
    struct Container_ **clist;
};
typedef struct Container_* Container;

//New and free
Container newContainer(ContainerType type);
void init_container(Container container, SDL_Rect region, SDL_Renderer *renderer);
void freeContainer(Container container);

//Get
SDL_Rect container_getBounds(Container container);

//Set
void container_setBounds(Container container, SDL_Rect region);

//Camera
void container_update_cameraLimit(Container container, Widget widget);

//Generic funtions to add widgets and subcontainers
void container_add_widget_generic(Container container, Widget widget);
void container_add_square(Container container, Square sqr);
void container_add_frame(Container container, Frame frame);
void container_add_image(Container container, Image img);
void container_add_text(Container container, Text txt);
void container_add_button(Container container, Button btn);
void container_add_container_generic(Container container, Container widget);

//Generic functions to process events and render
void container_process_events_generic(Container container, SDL_Event event, Mouse mouseState);
void container_draw_generic(Container container, SDL_Renderer *renderer);

//Include of all Containers here
#include "containers/vbox.h"
#include "containers/hbox.h"

#endif // CONTAINER_H
