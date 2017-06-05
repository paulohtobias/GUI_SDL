/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Button
 * Button library using SDL2
 */

#include "widgets/button.h"

Button newButton(char *text, char *img_path, SDL_Rect bounds){
	Button btn = malloc(sizeof(struct Button_));

	btn->txt = NULL;
	btn->img = NULL;

	btn->buttonColorTextIdle = default_button_textColor_idle;
	btn->buttonColorIdle = default_button_frameColor_idle;
	btn->buttonColorBorderIdle = default_button_borderColor_idle;
	btn->buttonColorTextFocused = default_button_textColor_focused;
	btn->buttonColorFocused = default_button_frameColor_focused;
	btn->buttonColorBorderFocused = default_button_borderColor_focused;
	btn->buttonColorTextPressed = default_button_textColor_pressed;
	btn->buttonColorPressed = default_button_frameColor_pressed;
	btn->buttonColorBorderPressed = default_button_borderColor_pressed;
	btn->buttonColorTextDisabled = default_button_textColor_disabled;
	btn->buttonColorDisabled = default_button_frameColor_disabled;
	btn->buttonColorBorderDisabled = default_button_borderColor_disabled;

	btn->frame = newFrame(default_button_frameColor_idle,
						default_button_borderColor_idle,
						default_button_borderSize, bounds);

	if(img_path != NULL){
		btn->img = newImage(img_path, bounds);
	}
	if(text != NULL){
		btn->txt = newText(text, region_position(bounds.x, bounds.y));
		text_setWrap(btn->txt, true);
	}
	resetBounds(&btn->region, bounds);
	btn->state = newWidgetState();

	button_Idle(btn);

	return btn;
}
void init_button(Button btn, SDL_Renderer *renderer){
	if(btn->img != NULL){
		init_image(btn->img, renderer);
	}
	if(btn->txt != NULL){
		init_text(btn->txt, renderer);
	}
	button_setBounds(btn, button_getBounds(btn));
}
void freeButton(Button btn){
	freeFrame(btn->frame);
	if(btn->txt != NULL)
        freeText(btn->txt);
    if(btn->img != NULL)
        freeImage(btn->img);
	free(btn);
}

//Get
int button_getBorderSize(Button  btn){
	return btn->frame->borderSize;
}
SDL_Rect button_getBounds(Button btn){
	return getBounds(btn->region);
}

//Set and Update
void button_setBorderSize(Button btn, int borderSize){
	frame_setBorderSize(btn->frame, borderSize);
}
void button_setBounds(Button btn, SDL_Rect region){
	setBounds(&btn->region, region);

	frame_setBounds(btn->frame, region);

	if (btn->img != NULL) {
		image_setBounds(btn->img, button_getBounds(btn));
	}
	if(btn->txt != NULL)
		text_center(btn->txt, button_getBounds(btn));
}
void button_updateBounds(Button btn, SDL_Rect region){
	updateBounds(&btn->region, region);

	button_setBounds(btn, button_getBounds(btn));
}
void button_Idle(Button btn){
	if(btn->txt != NULL)
		text_setColor(btn->txt, btn->buttonColorTextIdle);
	frame_setColor(btn->frame, btn->buttonColorIdle);
	frame_setBorderColor(btn->frame, btn->buttonColorBorderIdle);
}
void button_Focus(Button btn){
	if(btn->txt != NULL)
		text_setColor(btn->txt, btn->buttonColorTextFocused);
	frame_setColor(btn->frame, btn->buttonColorFocused);
	frame_setBorderColor(btn->frame, btn->buttonColorBorderFocused);
}
void button_Press(Button btn){
	if(btn->txt != NULL)
		text_setColor(btn->txt, btn->buttonColorTextPressed);
	frame_setColor(btn->frame, btn->buttonColorPressed);
	frame_setBorderColor(btn->frame, btn->buttonColorBorderPressed);
}
//button_Activate(Button btn);
//button_Deactivate(Button btn);
void button_setColorIdle(Button  btn, SDL_Color text, SDL_Color frame, SDL_Color border){
	btn->buttonColorTextIdle = text;
	btn->buttonColorIdle = frame;
	btn->buttonColorBorderIdle = border;
}
void button_setColorFocused(Button  btn, SDL_Color text, SDL_Color frame, SDL_Color border){
	btn->buttonColorTextFocused = text;
	btn->buttonColorFocused = frame;
	btn->buttonColorBorderFocused = border;
}
void button_setColorPressed(Button  btn, SDL_Color text, SDL_Color frame, SDL_Color border){
	btn->buttonColorTextPressed = text;
	btn->buttonColorPressed = frame;
	btn->buttonColorBorderPressed = border;
}
void button_setColorDisabled(Button  btn, SDL_Color text, SDL_Color frame, SDL_Color border){
	btn->buttonColorTextDisabled = text;
	btn->buttonColorDisabled = frame;
	btn->buttonColorBorderDisabled = border;
}

//Events
void button_processEvents(SDL_Event event, Mouse mouseState, Button btn){
	basic_widget_processEvents(event, mouseState, &btn->state, btn->region);
	if(button_isFocused(btn)){
		button_Focus(btn);
	}else if(button_isPressed(btn)){
		button_Press(btn);
	}else if(button_isDragged(btn)){
		button_Press(btn);
		button_updateBounds(btn, widget_dragPosition(mouseState));
	}else{
		button_Idle(btn);
	}
}
bool button_isFocused(Button btn){
	return widget_isFocused(btn->state);
}
bool button_isPressed(Button btn){
	return widget_isPressed(btn->state);
}
bool button_isReleased(Button btn){
	return widget_isReleased(btn->state);
}
bool button_isDragged(Button btn){
	return widget_isDragged(btn->state);
}

//Render
void renderButton(Button btn, SDL_Renderer *renderer, Camera camera){
	camera_updateWidgetPosition(camera, &btn->region);

	renderFrame(btn->frame, renderer, camera);
	if(btn->img != NULL)
		renderImage(btn->img, renderer, camera);
	if(btn->txt != NULL)
		renderText(btn->txt, renderer, camera);
}
