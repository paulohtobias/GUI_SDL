/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Frame
 * Frame library using SDL2
 */

#include "widgets/frame.h"

Frame newFrame(SDL_Color frameColor, SDL_Color borderColor, int borderSize, SDL_Rect size){
	Frame frame = malloc(sizeof(struct Frame_));

	frame->frame = newSquare(frameColor, size);
	frame->border = newSquare(borderColor, size);

	frame_setColor(frame, frameColor);
	frame_setBorderColor(frame, borderColor);
	resetBounds(&frame->region, size);
	frame_setBorderSize(frame, borderSize);
	frame_setBounds(frame, size);
	frame->state = newWidgetState();

	return frame;
}
void freeFrame(Frame frame){
	freeSquare(frame->border);
	freeSquare(frame->frame);
	free(frame);
}

//Get
SDL_Color frame_getColor(Frame frame){
	return frame->frame->color;
}
SDL_Color frame_getBorderColor(Frame frame){
	return frame->border->color;
}
SDL_Rect frame_getBounds(Frame frame){
	return getBounds(frame->region);
}

//Set and Update
void frame_setColor(Frame frame, SDL_Color color){
	frame->frame->color = color;
}
void frame_setBorderColor(Frame frame, SDL_Color color){
	frame->border->color = color;
}
void frame_setBorderSize(Frame frame, int borderSize){
	if(borderSize < 1)
		borderSize = 1;
		
	frame->borderSize = borderSize;
	
	SDL_Rect frameBounds = frame_getBounds(frame);

	SDL_Rect inner, border;
	inner = region_area(frameBounds.x + borderSize,
						frameBounds.y + borderSize,
						frameBounds.w, frameBounds.h);
	square_setBounds(frame->frame, inner);

	border = region_area(frameBounds.x, frameBounds.y,
						 frameBounds.w + (borderSize * 2),
						 frameBounds.h + (borderSize * 2));
	square_setBounds(frame->border, border);

	resetBounds(&frame->region, border);
}
void frame_setBounds(Frame frame, SDL_Rect region){
	setBounds(&frame->region, region);

	//Setting the border position
	frame_setBorderSize(frame, frame->borderSize);
}
void frame_updateBounds(Frame frame, SDL_Rect region){
	updateBounds(&frame->region, region);
	frame_setBounds(frame, frame_getBounds(frame));
}

//Events
void frame_processEvents(SDL_Event event, Mouse mouseState, Frame frame){
	basic_widget_processEvents(event, mouseState, &frame->state, frame->region);
	if(frame_isDragged(frame)){
		frame_updateBounds(frame, widget_dragPosition(mouseState));
	}
}
bool frame_isFocused(Frame frame){
	return widget_isFocused(frame->state);
}
bool frame_isPressed(Frame frame){
	return widget_isPressed(frame->state);
}
bool frame_isReleased(Frame frame){
	return widget_isReleased(frame->state);
}
bool frame_isDragged(Frame frame){
	return widget_isDragged(frame->state);
}

//Render
void renderFrame(Frame frame, SDL_Renderer *renderer, Camera camera){
	camera_updateWidgetPosition(camera, &frame->region);

	if( !camera_widget_is_off(camera, frame_getBounds(frame)) ){
        renderSquare(frame->border, renderer, camera);
        renderSquare(frame->frame, renderer, camera);
	}
}
