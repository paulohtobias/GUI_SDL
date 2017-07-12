#include "basic/color.h"

//Create a new Color using RGBA.
Color COLOR_RGBA(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha){
    Color color;

	color.r = red;
    color.g = green;
    color.b = blue;
    color.a = alpha;

	return color;
}

//Create a new Color using RGB.
Color COLOR_RGB(Uint8 red, Uint8 green, Uint8 blue){
    return COLOR_RGBA(red, green, blue, 255);
}


void set_renderer_draw_color(SDL_Renderer *renderer, Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
