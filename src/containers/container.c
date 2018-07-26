#include "containers/container.h"

SDL_bool __container_vt_was_init = SDL_FALSE;

void __container_vt_init(Container *container){
	if(!__container_vt_was_init){
		__gcontainer_widget_vt = __gwidget_vt;
		__gcontainer_widget_vt.free = __container_free;
		__gcontainer_widget_vt.set_bounds = __container_set_bounds;
		__gcontainer_widget_vt.process_events = __container_process_events;
		__gcontainer_widget_vt.draw = __container_draw;

		__gcontainer_vt.add_widget = __container_add_widget;
		__gcontainer_vt.remove_widget = __container_remove_widget;

		__container_vt_was_init = SDL_TRUE;
	}
	
	container->widget.functions = &__gcontainer_widget_vt;
	container->functions = &__gcontainer_vt;
}

Container new_Container(){
	return new_Container_max_widgets(CONTAINER_MAX_WIDGETS);
}

Container new_Container_max_widgets(int max){
	Container container;

	container.widget = new_Widget();
	__container_vt_init(&container);

	container.widget_list = new_ArrayList_max_size(max);

	return container;
}

void container_free(void *container){
	widget_free(container);
}

SDL_Rect container_get_bounds_origin(void *container){
	return widget_get_bounds_origin(container);
}

SDL_Rect container_get_bounds_camera(void *container){
	return widget_get_bounds_camera(container);
}

void container_set_bounds(void *container, SDL_Rect bounds){
	widget_set_bounds(container, bounds);
}

void container_process_events(void *container, SDL_Event event, Mouse mouse){
	widget_process_events(container, event, mouse);
}

void container_draw(void *container, SDL_Renderer *renderer, Camera *camera){
	widget_draw(container, renderer, camera);
}

void container_add_widget(void *container, void *widget){
	((Container *) container)->functions->add_widget(container, widget);
}

void *container_remove_widget(void *container){
	return((Container *) container)->functions->remove_widget(container);
}

void container_empty(void *container){
	Container *container_ = container;
	free_ArrayList(container_->widget_list, widget_free);
	container_->widget_list = new_ArrayList();
}

void __container_free(void *__container){
	__widget_free(__container);

	Container *container = __container;

	free_ArrayList(container->widget_list, widget_free);
	container->widget_list = NULL;
	container->functions->add_widget = NULL;
	container->functions->remove_widget = NULL;
}

void __container_set_bounds(void *__container, SDL_Rect bounds){
	Container *container = __container;

	SDL_Rect container_bounds_old = container_get_bounds_origin(container);
	set_bounds_from_SDL_Rect(&container->widget.bounds, bounds);
	SDL_Rect container_bounds_new = container_get_bounds_origin(container);

	Position container_offset;
	container_offset = new_Position(
		container_bounds_new.x - container_bounds_old.x,
		container_bounds_new.y - container_bounds_old.y
		);

	int i;
	for(i = 0; i < container->widget_list->size; i++){
		void *widget = list_get_index(container->widget_list, i);

		SDL_Rect widget_bounds = widget_get_bounds_origin(widget);
		widget_bounds.x += container_offset.x;
		widget_bounds.y += container_offset.y;

		widget_set_bounds(widget, widget_bounds);
	}
}

void __container_process_events(void *__container, SDL_Event event, Mouse mouse){
	Container *container = __container;

	__widget_process_events(container, event, mouse);
	int i;
	for(i = 0; i < container->widget_list->size; i++){
		widget_process_events(list_get_index(container->widget_list, i), event, mouse);
	}
}

void __container_draw(void *__container, SDL_Renderer *renderer, Camera *camera){
	Container *container = __container;

	int i;
	for(i = 0; i < container->widget_list->size; i++){
		widget_draw(list_get_index(container->widget_list, i), renderer, camera);
	}
}

void __container_add_widget(void *__container, void *widget){
	Container *container = __container;

	SDL_Rect container_bounds = container_get_bounds_origin(container);
	SDL_Rect widget_bounds = widget_get_bounds_origin(widget);
	widget_bounds.x += container_bounds.x;
	widget_bounds.y += container_bounds.y;
	widget_bounds.w = 0;
	widget_bounds.h = 0;
	widget_set_bounds(widget, widget_bounds);

	list_insert_last(container->widget_list, widget);
}

void* __container_remove_widget(void *__container){
	Container *container = __container;
	return list_remove_last(container->widget_list);
}
