#include "widgets/texture_widget.h"
#include "utils/exception.h"

VT_Widget __gtwidget_widget_vt = {
	generic_texture_widget_free,
	generic_widget_set_bounds,
	generic_widget_process_events,
	generic_texture_widget_draw
};

VT_TextureWidget __gtwidget_vt = {
	generic_texture_widget_set_changed,
	generic_texture_widget_render_copy,
	NULL
};

TextureWidget new_TextureWidget(){
	TextureWidget t_widget;

	t_widget.widget = new_Widget();

	t_widget.widget.functions = &__gtwidget_widget_vt;
	t_widget.functions = &__gtwidget_vt;

	t_widget.texture = NULL;

	t_widget.functions->set_changed(&t_widget, true);

	return t_widget;
}

void generic_texture_widget_free(void *raw_texture_widget){
	TextureWidget *t_widget = raw_texture_widget;

	widget_free(&t_widget->widget);

	SDL_DestroyTexture(t_widget->texture);

	t_widget->functions->set_changed = NULL;
	t_widget->functions->render_copy = NULL;
	t_widget->functions->update = NULL;
}

void generic_texture_widget_set_changed(void *raw_texture_widget, int changed){
	((TextureWidget *) raw_texture_widget)->changed = changed;
}

void generic_texture_widget_render_copy(void *raw_widget, SDL_Renderer *renderer){
	TextureWidget *t_widget = raw_widget;

	if(t_widget->texture == NULL){
		return;
	}

	SDL_Rect bounds = get_bounds_camera(t_widget->widget.bounds);
	SDL_RenderCopy(renderer, t_widget->texture, NULL, &bounds);
}

void generic_texture_widget_draw(void *raw_texture_widget, SDL_Renderer *renderer, Camera *camera){
	TextureWidget *t_widget = raw_texture_widget;

	if(widget_is_inside_camera(raw_texture_widget, camera)){
		if(t_widget->widget.state.entered_camera == false){
			t_widget->widget.state.entered_camera = true;
		}

		t_widget->functions->update(raw_texture_widget, renderer);

		if(t_widget->widget.style != NULL){
			border_draw(style_get_border(t_widget->widget.style), renderer, camera);
		}

		t_widget->functions->render_copy(raw_texture_widget, renderer);
	}else if(t_widget->widget.state.entered_camera == true){
		t_widget->widget.state.entered_camera = false;

		SDL_DestroyTexture(t_widget->texture);
		t_widget->texture = NULL;

		t_widget->functions->set_changed(raw_texture_widget, true);
	}
}
