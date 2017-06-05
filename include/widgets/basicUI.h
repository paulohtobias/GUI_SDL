/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Basic UI
 * Structs and functions basic to all GUI widgets
 */

#ifndef BASIC_UI_H
#define BASIC_UI_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifndef TYPE_BOOL
#define TYPE_BOOL
	typedef int bool;
	#define false 0
	#define true 1
#endif //TYPE_BOOL

void init();

///===================----COLOR----===================///
#define COLOR_BLACK COLOR_RGB(0,0,0)
#define COLOR_GREY(value) COLOR_RGB(value, value, value)
#define COLOR_WHITE COLOR_RGB(255,255,255)
#define COLOR_RED COLOR_RGB(255,0,0)
#define COLOR_ORANGE COLOR_RGB(248,163,35)
#define COLOR_GREEN COLOR_RGB(0,255,0)
#define COLOR_LIGHT_GREEN COLOR_RGB(128,255,0)
#define COLOR_BLUE COLOR_RGB(0,0,255)
#define COLOR_LIGHT_BLUE COLOR_RGB(138,210,249)
#define COLOR_YELLOW COLOR_RGB(255,255,0)
#define COLOR_BROWN COLOR_RGB(149,74,0)
#define COLOR_PURPLE COLOR_RGB(128,0,255)
#define COLOR_PINK COLOR_RGB(255,132,255)

SDL_Color COLOR_RGB(Uint8 r, Uint8 g, Uint8 b);
void SetRenderDrawColor(SDL_Renderer *renderer, SDL_Color color);

///===================----BASIC WIDGET----===================///
typedef struct{
	bool isFocused;		//Mouse is over
	int mouseButton;	//Which mouse button pressed the widget
	bool isPressed;		//Mouse button down on widget
	bool isReleased;	//Mouse button left widget
	bool isFixed;		//Widget can't be dragged
	bool isDragged;		//Widget is being dragged
	bool isOnCamera;	//Widget entered camera
	bool wasChanged;	//If an attribute of the widget was changed
						//and need a renderer to update
}WidgetState;

WidgetState newWidgetState();
bool widget_isFocused(WidgetState state);
bool widget_isPressed(WidgetState state);
bool widget_isReleased(WidgetState state);
bool widget_isDragged(WidgetState state);
bool widget_isOnCamera(WidgetState state);
bool widget_wasChanged(WidgetState state);

///===================----REGION----===================///
typedef struct{
    SDL_Rect real;
    SDL_Rect relative;
}Bounds;

//Get, Set and Update
SDL_Rect getBounds(Bounds region);
void setRegion(SDL_Rect *regionDST, SDL_Rect regionSRC);
void updateRegion(SDL_Rect *region, SDL_Rect newValues);
void setBounds(Bounds *regionDST, SDL_Rect regionSRC);
void updateBounds(Bounds *region, SDL_Rect newValues);
void resetBounds(Bounds *region, SDL_Rect regionSRC);
#define WIDGET_FIT_DOWN 0
SDL_Rect get_widgetFit_position(SDL_Rect region, SDL_Rect size, int maxX, int margin_left, int margin_bottom, int escapeX);

//Area, Position and Size
SDL_Rect region_area(int x, int y, int w, int h);
SDL_Rect region_position(int x, int y);
SDL_Rect region_size(int w, int h);

//Reach
int region_reachX(SDL_Rect region);
int region_reachY(SDL_Rect region);
int bounds_reachX(Bounds region);
int bounds_reachY(Bounds region);

///===================----MOUSE----===================///
typedef enum{
	mouse_idle,
	mouse_left_pressed,
	mouse_left_released,
	mouse_right_pressed,
	mouse_right_released
}MouseButtonState;

typedef struct{
	int x, y;
}MousePos;

MousePos getMousePosition();

typedef struct{
	int button;
	MousePos mPos;
	MousePos mPosDrag;
}Mouse;

Mouse newMouseState();
int mousePressed(Mouse mouseState);
int mouseReleased(Mouse mouseState);
bool mouseOverRegion(SDL_Rect region);
bool mouseOver(Bounds region);

///===================----EVENTS----===================///
void basic_widget_processEvents(SDL_Event event, Mouse mouseState, WidgetState *state, Bounds region);
SDL_Rect widget_dragPosition(Mouse mouseState);

///===================----CAMERA----===================///
#define camera_offset 20

struct Camera_{
    SDL_Rect region;
    SDL_Rect limit;
    int movSpeed;
    int movX;
    int movY;
};
typedef struct Camera_* Camera;

Camera newCamera(SDL_Rect limit);
void freeCamera(Camera camera);

void camera_updateSize(SDL_Window *window, Camera camera);
void camera_updateLimit(Camera camera, SDL_Rect widget_region);
void camera_move(Camera camera);

void camera_updateWidgetPosition(Camera camera, Bounds *widget);
bool camera_widget_is_off(Camera camera, SDL_Rect region);

void processEvents_camera(Camera camera, SDL_Event event);

#endif // BASIC_UI_H
