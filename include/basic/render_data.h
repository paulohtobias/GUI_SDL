/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Render Data
 * Information needed to render a widget.
 */

#ifndef RENDER_DATA_H
#define RENDER_DATA_H

#include <SDL2/SDL.h>
#include "camera.h"

///Holds all information needed to render a widget.
typedef struct RenderData {
	SDL_Renderer *renderer;
	Camera *camera;
} RenderData;

#endif //RENDER_DATA_H
