#include "basic/color.h"

//Create a new Color using RGB.
SDL_Color COLOR_RGB(Uint8 red, Uint8 green, Uint8 blue){
    SDL_Color color;

	color.r = red;
    color.g = green;
    color.b = blue;
    color.a = 255;

	return color;
}
void SetRenderDrawColor(SDL_Renderer *renderer, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
