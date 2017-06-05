/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Basic UI
 * Structs and functions basic to all GUI widgets
 */

#include "widgets/basicUI.h"

void init(){
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error SDL_Init", SDL_GetError(), NULL);
        SDL_Quit();
        exit(1);
    }
    //Initialize SDL_image
    if( IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) < 0 ){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error IMG_Init", IMG_GetError(), NULL);
        exit(1);
    }
    //Initialize SDL_ttf
    if( TTF_Init() == -1 ){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error TTF_Init", TTF_GetError(), NULL);
        exit(1);
    }
}

///===================----COLOR----===================///
SDL_Color COLOR_RGB(Uint8 r, Uint8 g, Uint8 b){
    SDL_Color c;

	c.r = r;
    c.g = g;
    c.b = b;
    c.a = 255;

	return c;
}
void SetRenderDrawColor(SDL_Renderer *renderer, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

///===================----BASIC WIDGET----===================///
WidgetState newWidgetState(){
	WidgetState state;

	state.isFocused = false;
	state.mouseButton = mouse_idle;
	state.isPressed = false;
	state.isReleased = false;
	state.isFixed = true;
	state.isDragged = false;
    state.isOnCamera = true;
    state.wasChanged = false;

	return state;
}
bool widget_isFocused(WidgetState state){
	return state.isFocused;
}
bool widget_isPressed(WidgetState state){
	return state.isPressed;
}
bool widget_isReleased(WidgetState state){
	return state.isReleased;
}
bool widget_isDragged(WidgetState state){
	return state.isDragged;
}
bool widget_isOnCamera(WidgetState state){
    return state.isOnCamera;
}
bool widget_wasChanged(WidgetState state){
    return state.wasChanged;
}

///===================----REGION----===================///
SDL_Rect getBounds(Bounds region){
    return region.relative;
}
void setRegion(SDL_Rect *regionDST, SDL_Rect regionSRC){
    regionDST->x = regionSRC.x;
    regionDST->y = regionSRC.y;

    if(regionSRC.w > 0)
        regionDST->w = regionSRC.w;

    if(regionSRC.h > 0)
        regionDST->h = regionSRC.h;
}
void updateRegion(SDL_Rect *region, SDL_Rect newValues){
    setRegion(region,
              region_area(region->x + newValues.x,
                          region->y + newValues.y,
                          region->w + newValues.w,
                          region->h + newValues.h));
}
void setBounds(Bounds *regionDST, SDL_Rect regionSRC){
    regionDST->relative.x += regionSRC.x - regionDST->real.x;
    regionDST->real.x = regionSRC.x;

    regionDST->relative.y += regionSRC.y - regionDST->real.y;
    regionDST->real.y = regionSRC.y;

    if(regionSRC.w > 0){
        regionDST->relative.w += regionSRC.w - regionDST->real.w;
        regionDST->real.w = regionSRC.w;
    }

    if(regionSRC.h > 0){
        regionDST->relative.h += regionSRC.h - regionDST->real.h;
        regionDST->real.h = regionSRC.h;
    }
}
void updateBounds(Bounds *region, SDL_Rect newValues){
    setBounds(region,
             region_area(region->real.x + newValues.x,
                        region->real.y + newValues.y,
                        region->real.w + newValues.w,
                        region->real.h + newValues.h));
}
void resetBounds(Bounds *region, SDL_Rect regionSRC){
    region->real = regionSRC;
    region->relative = regionSRC;
}
SDL_Rect get_widgetFit_position(SDL_Rect region, SDL_Rect size, int maxX, int margin_left, int margin_bottom, int escapeX){
	SDL_Rect widgetRegion = region_area(
		region_reachX(region) + margin_left,
		region.y,
		size.w,
		size.h
	);
	if( region_reachX(widgetRegion) > maxX ){
		widgetRegion = region_area(
			escapeX,
			region_reachY(region) + margin_bottom,
            size.w,
            size.h
		);
	}
	return widgetRegion;
}

//Area, Position and Size
SDL_Rect region_area(int x, int y, int w, int h){
    SDL_Rect region;

    region.x = x;
    region.y = y;
    region.w = w;
    region.h = h;

    return region;
}
SDL_Rect region_position(int x, int y){
    SDL_Rect region;

    region.x = x;
    region.y = y;
    region.w = 0;
    region.h = 0;

    return region;
}
SDL_Rect region_size(int w, int h){
    SDL_Rect region;

    region.x = 0;
    region.y = 0;
    region.w = w;
    region.h = h;

    return region;
}

//Reach
int region_reachX(SDL_Rect region){
    return region.x + region.w;
}
int region_reachY(SDL_Rect region){
    return region.y + region.h;
}
int bounds_reachX(Bounds region){
    return region.relative.x + region.relative.w;
}
int bounds_reachY(Bounds region){
    return region.relative.y + region.relative.h;
}

///===================----MOUSE----===================///
MousePos getMousePosition(){
	MousePos mPos;
	SDL_GetMouseState(&mPos.x, &mPos.y);
	return mPos;
}
Mouse newMouseState(){
    Mouse mouseState;

    mouseState.button = mouse_idle;
	mouseState.mPos = getMousePosition();
	mouseState.mPosDrag = getMousePosition();

	return mouseState;
}
int mousePressed(Mouse mouseState){
	if( (mouseState.button == mouse_left_pressed) || (mouseState.button == mouse_right_pressed) ){
		return mouseState.button;
	}else{
		return 0;
	}
}
int mouseReleased(Mouse mouseState){
	if( (mouseState.button == mouse_left_released) || (mouseState.button == mouse_right_released) ){
		return mouseState.button;
	}else{
		return 0;
	}
}
bool mouseOverRegion(SDL_Rect region){
	int mx, my;

	SDL_GetMouseState(&mx, &my);

	int xi = region.x;
	int xf = region_reachX(region);

	int yi = region.y;
	int yf = region_reachY(region);

	if( (mx>xi && mx<xf) && (my>yi && my<yf) ){
		return true;
	}else{
		return false;
	}
}
bool mouseOver(Bounds region){
	return mouseOverRegion(region.relative);
}

///===================----EVENTS----===================///
void basic_widget_processEvents(SDL_Event event, Mouse mouseState, WidgetState *state, Bounds region){
	//(*state) = newWidgetState();
	state->isFocused = false;
	state->mouseButton = mouse_idle;
	state->isPressed = false;
	state->isReleased = false;
	state->isDragged = false;

	if(mouseOver(region)){
		if(mousePressed(mouseState)){
			state->mouseButton = mouseState.button;
			state->isPressed = true;
			if(state->isFixed == false && event.type == SDL_MOUSEMOTION){ //Being dragged
				state->isDragged = true;
				return;
			}
		}else if(mouseState.button == mouse_left_released){
			state->isReleased = true;
		}else{
			state->isFocused = true;
		}
	}
}
SDL_Rect widget_dragPosition(Mouse mouseState){
	SDL_Rect newPos =  region_position(mouseState.mPos.x - mouseState.mPosDrag.x,
						   			   mouseState.mPos.y - mouseState.mPosDrag.y);

	newPos.x*=1.05;
	newPos.y*=1.05;

	return newPos;
}

///===================----CAMERA----===================///
Camera newCamera(SDL_Rect limit){
    Camera camera = (Camera )SDL_malloc(sizeof(struct Camera_));

    camera->region = limit;
    camera->limit = limit;
    camera->movSpeed = 20;
    camera->movX = 0;
    camera->movY = 0;

    return camera;
}
void freeCamera(Camera camera){
	free(camera);
}

void camera_updateSize(SDL_Window *window, Camera camera){
    SDL_GetWindowSize(window, &camera->region.w, &camera->region.h);
}
void camera_updateLimit(Camera camera, SDL_Rect widget_region){
    //Checking if the object position is "out of bounds" so the camera can reach it too.
    if(region_reachX(widget_region) + camera_offset > region_reachX(camera->limit) ){
        camera->limit.w = region_reachX(widget_region) + camera_offset;
    }

    if(region_reachY(widget_region) + camera_offset > region_reachY(camera->limit) ){
        camera->limit.h = region_reachY(widget_region) + camera_offset;
    }
}
void camera_move(Camera camera){
    updateRegion(&camera->region, region_position(camera->movX, camera->movY));

    if(camera->region.x < camera->limit.x){
        camera->region.x = camera->limit.x;
    }
    if(region_reachX(camera->region) > camera->limit.w){
        camera->region.x = camera->limit.w - camera->region.w;
    }

    if(camera->region.y < camera->limit.y){
        camera->region.y = camera->limit.y;
    }
    if(region_reachY(camera->region) > camera->limit.h){
        camera->region.y = camera->limit.h - camera->region.h;
    }
    camera->movX = 0; camera->movY = 0;
}

void camera_updateWidgetPosition(Camera camera, Bounds *widget){
    if(camera != NULL){
        setRegion(&widget->relative,
                  region_position(widget->real.x - camera->region.x,
                                  widget->real.y - camera->region.y));
    }
}
bool camera_widget_is_off(Camera camera, SDL_Rect region){
    if(camera == NULL){
        return false;
    }
    //X axis
    if( region_reachX(region) + camera_offset < camera->limit.x ){ //Widget is too much to the left
        return true;
    }
    if( region.x - camera_offset > camera->region.w ){ //Widget is too much to the right
        return true;
    }

    //Y axis
    if( region_reachY(region) + camera_offset < camera->limit.y ){ //Widget is is too much above camera
        return true;
    }
    if( region.y - camera_offset > camera->region.h ){ //Widget is is too much below camera
        return true;
    }

    return false;
}

void processEvents_camera(Camera camera, SDL_Event event){
    switch(event.type){
        case SDL_MOUSEWHEEL:
            camera->movY-=event.wheel.y*camera->movSpeed;
            camera->movX+=event.wheel.x*camera->movSpeed;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_UP:
                    camera->movY-=camera->movSpeed;
                    break;
                case SDLK_DOWN:
                    camera->movY+=camera->movSpeed;
                    break;
                case SDLK_END:
                    camera->movY = (camera->limit.h - camera->region.h) - camera->region.y;
                    break;
                case SDLK_HOME:
                    camera->movY = camera->limit.y - camera->region.y;
                    break;
            }
            break;
        default:
            camera->movX = 0;
            camera->movY = 0;
            break;
    }
}
