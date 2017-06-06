#ifndef WIDGET_H
#define WIDGET_H

#include "widgets/basicUI.h"
#include "widgets/square.h"
#include "widgets/frame.h"
#include "widgets/image.h"
#include "widgets/text.h"
#include "widgets/button.h"

typedef enum{
	WGT_SQUARE,
	WGT_FRAME,
	WGT_IMAGE,
	WGT_TEXT,
	WGT_TEXTFIELD,
	WGT_BUTTON,
	WGT_COUNT
}WidgetType;

typedef union{
	Square sqr;
	Frame frame;
	Image img;
	Text txt;
	Button btn;
}u_Widget;

struct Widget_{
	int obj_type;
	u_Widget *obj_data;
};
typedef struct Widget_* Widget;

//New and Free
Widget newWidget(u_Widget *data, WidgetType type);
Widget newWidget_from_square(Square sqr);
Widget newWidget_from_frame(Frame frame);
Widget newWidget_from_image(Image img);
Widget newWidget_from_text(Text txt);
//Widget newWidget_from_text_field(TextField txt_field);
Widget newWidget_from_button(Button btn);
void init_widget(Widget widget, SDL_Renderer *renderer);
void freeWidget(Widget obj);

//Bounds
SDL_Rect widget_getBounds(Widget obj);
SDL_Rect widget_getRealBounds(Widget obj);
void widget_setBounds(Widget widget, SDL_Rect region);
void widget_updateBounds(Widget widget, SDL_Rect region);

//Events and Draw
void widget_processEvents(SDL_Event event, Mouse mouseState, Widget obj);
void widget_drag(Widget obj, Mouse mouseState);
void widget_render(Widget obj, SDL_Renderer *renderer, Camera camera);

///===================----LIST----===================///
#define MAX_WIDGETS 250
struct WidgetList_{
	int size;
	int first;
	int last;
	Widget *array;
};
typedef struct WidgetList_* WidgetList;

//New and Free
WidgetList newWidgetList();
void freeList(WidgetList list);

int list_isEmpty(WidgetList list);

//Add
void list_add_first(WidgetList list, Widget obj);
void list_add_last(WidgetList list, Widget obj);

//Remove
Widget list_remove_first(WidgetList list);
Widget list_remove_last(WidgetList list);


#endif //WIDGET_H
