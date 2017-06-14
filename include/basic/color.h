/**
  * Paulo Henrique Tobias
  * Manga Library
  *
  * Color
  * Basic functions and definitions for color.
  */

#ifndef COLOR_H
#define COLOR_H

#include <stdlib.h>
#include <SDL2/SDL.h>

//Create a new Color using RGB.
SDL_Color COLOR_RGB(Uint8 red, Uint8 green, Uint8 blue);

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

void set_renderer_draw_color(SDL_Renderer *renderer, SDL_Color color);

#endif //COLOR_H
