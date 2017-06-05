#include "widget.h"

Widget newWidget(u_Widget *data, WidgetType type){
	Widget widget = malloc(sizeof(struct Widget_));

	widget->obj_type = type;
	widget->obj_data = data;

	return widget;
}

Widget newWidget_from_square(Square sqr){
	u_Widget *data = malloc(sizeof(u_Widget));
	data->sqr = sqr;

	return newWidget(data, WGT_SQUARE);
}
Widget newWidget_from_frame(Frame frame){
	u_Widget *data = malloc(sizeof(u_Widget));
	data->frame = frame;

	return newWidget(data, WGT_FRAME);
}
Widget newWidget_from_image(Image img){
	u_Widget *data = malloc(sizeof(u_Widget));
	data->img = img;

	return newWidget(data, WGT_IMAGE);
}
Widget newWidget_from_text(Text txt){
	u_Widget *data = malloc(sizeof(u_Widget));
	data->txt = txt;

	return newWidget(data, WGT_TEXT);
}
//Widget newWidget_from_text_field(TextField txt_field);
Widget newWidget_from_button(Button btn){
	u_Widget *data = malloc(sizeof(u_Widget));
	data->btn = btn;

	return newWidget(data, WGT_BUTTON);
}
Widget newWidget_from_frameChapter(FrameChapter frameC){
	u_Widget *data = malloc(sizeof(u_Widget));
	data->frameC = frameC;

	return newWidget(data, WGT_FRAMECHAPTER);
}
void init_widget(Widget widget, SDL_Renderer *renderer){
    if(widget == NULL){
        return;
    }

    switch (widget->obj_type) {
		case WGT_IMAGE:
			init_image(widget->obj_data->img, renderer);
			break;
		case WGT_TEXT:
			init_text(widget->obj_data->txt, renderer);
			break;
		case WGT_BUTTON:
			init_button(widget->obj_data->btn, renderer);
			break;
        case WGT_FRAMECHAPTER:
            init_frameChapter(widget->obj_data->frameC, renderer);
            break;
        default:
            break;
	}
}
void freeWidget(Widget obj){
	if(obj == NULL){
		return;
	}
	switch (obj->obj_type) {
		case WGT_SQUARE:
			freeSquare(obj->obj_data->sqr);
			break;
		case WGT_FRAME:
			freeFrame(obj->obj_data->frame);
			break;
		case WGT_IMAGE:
			freeImage(obj->obj_data->img);
			break;
		case WGT_TEXT:
			freeText(obj->obj_data->txt);
			break;
		case WGT_BUTTON:
			freeButton(obj->obj_data->btn);
			break;
        case WGT_FRAMECHAPTER:
            freeFrameChapter(obj->obj_data->frameC);
            break;
	}
	free(obj->obj_data);
	free(obj);
}

//Bounds
SDL_Rect widget_getBounds(Widget obj){
	if(obj == NULL){
		return region_area(0,0,0,0);
	}
	switch(obj->obj_type){
		case WGT_SQUARE:
			return square_getBounds(obj->obj_data->sqr);
		case WGT_FRAME:
			return frame_getBounds(obj->obj_data->frame);
		case WGT_IMAGE:
			return image_getBounds(obj->obj_data->img);
		case WGT_TEXT:
			return text_getBounds(obj->obj_data->txt);
		case WGT_BUTTON:
			return button_getBounds(obj->obj_data->btn);
        case WGT_FRAMECHAPTER:
            return frameChapter_getBounds(obj->obj_data->frameC);
		default:
			return region_area(0,0,0,0);
	}
}
SDL_Rect widget_getRealBounds(Widget obj){
	if(obj == NULL){
		return region_area(0,0,0,0);
	}
	switch(obj->obj_type){
		case WGT_SQUARE:
			return obj->obj_data->sqr->region.real;
		case WGT_FRAME:
			return obj->obj_data->frame->region.real;
		case WGT_IMAGE:
			return obj->obj_data->img->region.real;
		case WGT_TEXT:
			return obj->obj_data->txt->region.real;
		case WGT_BUTTON:
			return obj->obj_data->btn->region.real;
        case WGT_FRAMECHAPTER:
            return obj->obj_data->frameC->region.real;
		default:
			return region_area(0,0,0,0);
	}
}
void widget_setBounds(Widget widget, SDL_Rect region){
	if(widget == NULL){
		return;
	}
	switch(widget->obj_type){
		case WGT_SQUARE:
			square_setBounds(widget->obj_data->sqr, region);
			break;
		case WGT_FRAME:
			frame_setBounds(widget->obj_data->frame, region);
			break;
		case WGT_IMAGE:
			image_setBounds(widget->obj_data->img, region);
			break;
		case WGT_TEXT:
			text_setBounds(widget->obj_data->txt, region);
			break;
		case WGT_BUTTON:
			button_setBounds(widget->obj_data->btn, region);
			break;
        case WGT_FRAMECHAPTER:
            frameChapter_setBounds(widget->obj_data->frameC, region);
			break;
	}
}
void widget_updateBounds(Widget widget, SDL_Rect region){
	if(widget == NULL){
		return;
	}
	switch(widget->obj_type){
		case WGT_SQUARE:
			square_updateBounds(widget->obj_data->sqr, region);
			break;
		case WGT_FRAME:
			frame_updateBounds(widget->obj_data->frame, region);
			break;
		case WGT_IMAGE:
			image_updateBounds(widget->obj_data->img, region);
			break;
		case WGT_TEXT:
			text_updateBounds(widget->obj_data->txt, region);
			break;
		case WGT_BUTTON:
			button_updateBounds(widget->obj_data->btn, region);
			break;
        case WGT_FRAMECHAPTER:
            frameChapter_updateBounds(widget->obj_data->frameC, region);
			break;
	}
}

//Events and Draw
void widget_processEvents(SDL_Event event, Mouse mouseState, Widget obj){
	if(obj == NULL){
		return;
	}
    switch(obj->obj_type) {
        case WGT_SQUARE:
            square_processEvents(event, mouseState, obj->obj_data->sqr);
            break;
        case WGT_FRAME:
            frame_processEvents(event, mouseState, obj->obj_data->frame);
            break;
        case WGT_IMAGE:
            image_processEvents(event, mouseState, obj->obj_data->img);
            break;
        case WGT_TEXT:
            text_processEvents(event, mouseState, obj->obj_data->txt);
            break;
        case WGT_BUTTON:
            button_processEvents(event, mouseState, obj->obj_data->btn);
            break;
        case WGT_FRAMECHAPTER:
            frameChapter_processEvents(event, mouseState, obj->obj_data->frameC);
            break;
    }
}
void widget_drag(Widget obj, Mouse mouseState){
	if(obj == NULL){
		return;
	}
	SDL_Rect newPos = region_position(mouseState.mPos.x - mouseState.mPosDrag.x,
									  mouseState.mPos.y - mouseState.mPosDrag.y);
	newPos.x+=1.1;
	newPos.y*=1.1;
	switch(obj->obj_type){
		case WGT_SQUARE:
			square_updateBounds(obj->obj_data->sqr, newPos);
			break;
		case WGT_FRAME:
			frame_updateBounds(obj->obj_data->frame, newPos);
			break;
		case WGT_IMAGE:
			image_updateBounds(obj->obj_data->img, newPos);
			break;
		case WGT_TEXT:
			text_updateBounds(obj->obj_data->txt, newPos);
			break;
		case WGT_BUTTON:
			button_updateBounds(obj->obj_data->btn, newPos);
			break;
        case WGT_FRAMECHAPTER:
            frameChapter_updateBounds(obj->obj_data->frameC, newPos);
            break;
	}
}
void widget_render(Widget obj, SDL_Renderer *renderer, Camera camera){
	if(obj == NULL){
		return;
	}
    switch (obj->obj_type) {
        case WGT_SQUARE:
            renderSquare(obj->obj_data->sqr, renderer, camera);
            break;
        case WGT_FRAME:
            renderFrame(obj->obj_data->frame, renderer, camera);
            break;
        case WGT_IMAGE:
            renderImage(obj->obj_data->img, renderer, camera);
            break;
        case WGT_TEXT:
            renderText(obj->obj_data->txt, renderer, camera);
            break;
        case WGT_BUTTON:
            renderButton(obj->obj_data->btn, renderer, camera);
            break;
        case WGT_FRAMECHAPTER:
            renderFrameChapter(obj->obj_data->frameC, renderer, camera);
            break;
    }
}

///===================----LIST----===================///
//New and Free
WidgetList newWidgetList(){
	WidgetList list = malloc(sizeof(struct WidgetList_));

	list->size = 0;
	list->first = 0;
	list->last = 0;
	list->array = malloc(MAX_WIDGETS * sizeof(Widget));

	int i;
	for(i=0; i<MAX_WIDGETS; i++){
		list->array[i] = NULL;
	}

	return list;
}
void freeList(WidgetList list){
	if(list_isEmpty(list)){
		return;
	}
    int i;
	for(i=list->first; i<=list->last; i++){
		freeWidget(list_remove_first(list));
		list->array[i] = NULL;
	}
    free(list->array);

	list->first = 0;
	list->last = 0;
	list->size = 0;

	list->array = NULL;

	free(list);
}

int list_isEmpty(WidgetList list){
	return (list->size == 0);
}

//Add
void list_add_first(WidgetList list, Widget obj){
	//This whole if-else section consists in finding where to put the object
	if(list->first > 0){
		list->first--;
	}else{
		//Here the first position of the array is occupied.
		//Then, if there's is enough space, that is, the list isn't full,
		//the objects will be "dragged" so that the first position will be empty.
		if(list->last + 1 < MAX_WIDGETS){
			int i;
			for(i=list->last; i>=0; i--){
				list->array[i+1] = list->array[i];
			}
			list->last++;
		}else{
			//The list is full
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Object list is full", "list_add_first", NULL);
		}
	}

	list->array[list->first] = obj;
	list->size++;
}
void list_add_last(WidgetList list, Widget obj){
	if(list->last + 1 < MAX_WIDGETS){
		list->last++;
	}else{
		//The list is full
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Object list is full", "list_add_last", NULL);
	}

	list->array[list->last] = obj;
	list->size++;
}

//Remove
Widget list_remove_first(WidgetList list){
	Widget obj = NULL;

	if(!list_isEmpty(list)){
		obj = list->array[list->first];
		list->array[list->first] = NULL;
		list->first++;
		list->size--;
	}
	return obj;
}
Widget list_remove_last(WidgetList list){
	Widget obj = NULL;

	if(!list_isEmpty(list)){
		obj = list->array[list->last];
		list->array[list->last] = NULL;
        list->last--;
        list->size--;
	}

	return obj;
}
