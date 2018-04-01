#include "widgets/texture_widget.h"

VT_Widget __gtwidget_widget_vt = {
	__texture_widget_free,
	__widget_set_bounds,
	__widget_process_events,
	__texture_widget_draw
};

VT_TextureWidget __gtwidget_vt = {
	__texture_widget_set_changed,
	__texture_widget_render_copy,
	NULL
};

TextureWidget new_TextureWidget(){
	TextureWidget t_widget;

	t_widget.widget = new_Widget();

	t_widget.widget.functions = &__gtwidget_widget_vt;
	t_widget.functions = &__gtwidget_vt;

	t_widget.texture = NULL;

	t_widget.functions->set_changed(&t_widget, SDL_TRUE);

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

	widget_free(&t_widget->widget);

	SDL_DestroyTexture(t_widget->texture);

	t_widget->functions->set_changed = NULL;
	t_widget->functions->render_copy = NULL;
	t_widget->functions->update = NULL;
}

void __texture_widget_set_changed(void *__texture_widget, int changed){
	((TextureWidget *) __texture_widget)->changed = changed;
}

void __texture_widget_render_copy(void *__widget, SDL_Renderer *renderer){
	TextureWidget *t_widget = __widget;

	if(t_widget->texture == NULL){
		return;
	}

	SDL_Rect bounds = get_bounds_camera(t_widget->widget.bounds);
	SDL_RenderCopy(renderer, t_widget->texture, NULL, &bounds);
}

void __texture_widget_draw(void *__texture_widget, SDL_Renderer *renderer, Camera *camera){
	TextureWidget *t_widget = __texture_widget;

	if(widget_is_inside_camera(__texture_widget, camera)){
		if(t_widget->widget.state.entered_camera == SDL_FALSE){
			t_widget->widget.state.entered_camera = SDL_TRUE;
		}

		t_widget->functions->update(__texture_widget, renderer);

		border_draw(t_widget->widget.border, renderer, camera);

		t_widget->functions->render_copy(__texture_widget, renderer);
	}else if(t_widget->widget.state.entered_camera == SDL_TRUE){
		t_widget->widget.state.entered_camera = SDL_FALSE;

		SDL_DestroyTexture(t_widget->texture);
		t_widget->texture = NULL;

		t_widget->functions->set_changed(__texture_widget, SDL_TRUE);
	}
}
