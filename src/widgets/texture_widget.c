#include "widgets/texture_widget.h"

SDL_bool __twidget_vt_was_init = SDL_FALSE;

void __twidget_vt_init(TextureWidget *t_widget){
	if(!__twidget_vt_was_init){
		__gtwidget_widget_vt = __gwidget_vt;
		__gtwidget_widget_vt.free = __texture_widget_free;
		__gtwidget_widget_vt.draw = __texture_widget_draw;

		__gtwidget_vt.set_changed = __texture_widget_set_changed;
		__gtwidget_vt.render_copy = __texture_widget_render_copy;
		__gtwidget_vt.update = NULL;

		__twidget_vt_was_init = SDL_TRUE;
	}
	
	t_widget->widget.functions = &__gtwidget_widget_vt;
	t_widget->functions = &__gtwidget_vt;
}

TextureWidget new_TextureWidget(){
	TextureWidget t_widget;

	t_widget.widget = new_Widget();
	__twidget_vt_init(&t_widget);

	t_widget.texture = NULL;

	texture_widget_set_changed(&t_widget, SDL_TRUE);

	return t_widget;
}

int texture_widget_get_changed(void *t_widget){
	return ((TextureWidget *)t_widget)->changed;
}

void texture_widget_set_changed(void *t_widget, int changed){
	((TextureWidget *) t_widget)->functions->set_changed(t_widget, changed);
}


void __texture_widget_free(void *__texture_widget){
	TextureWidget *t_widget = __texture_widget;

	__widget_free(&t_widget->widget);

	SDL_DestroyTexture(t_widget->texture);
}

void __texture_widget_set_changed(void *__texture_widget, int changed){
	((TextureWidget *) __texture_widget)->changed = changed;
}

void __texture_widget_render_copy(void *__widget, RenderData *data){
	TextureWidget *t_widget = __widget;

	if(t_widget->texture == NULL){
		return;
	}

	SDL_Rect bounds = widget_get_bounds_camera(t_widget, data->camera);
	SDL_Rect draw_area = camera_get_drawable_area(data->camera, &bounds);

	border_draw(t_widget->widget.border, data);
	SDL_RenderCopy(data->renderer, t_widget->texture, &draw_area, &bounds);
}

void __texture_widget_draw(void *__texture_widget, RenderData *data){
	TextureWidget *t_widget = __texture_widget;

	if(widget_is_inside_camera(__texture_widget, data->camera)){
		if(t_widget->widget.state.entered_camera == SDL_FALSE){
			t_widget->widget.state.entered_camera = SDL_TRUE;
		}

		t_widget->functions->update(__texture_widget, data->renderer);

		t_widget->functions->render_copy(__texture_widget, data);
	}else if(t_widget->widget.state.entered_camera == SDL_TRUE){
		t_widget->widget.state.entered_camera = SDL_FALSE;

		SDL_DestroyTexture(t_widget->texture);
		t_widget->texture = NULL;

		t_widget->functions->set_changed(__texture_widget, SDL_TRUE);
	}
}
