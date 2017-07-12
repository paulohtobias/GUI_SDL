/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Shape
 * Shape module. Used to draw simple shapes on the screen.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <basic/bounds.h>
#include <basic/mouse.h>
#include <basic/color.h>

typedef struct Rectangle_{
    Color color;
    Bounds bounds;
}Rectangle;

/**
 * Creates a new Rectangle.
 * 
 * @param color the rectangle color
 * @param bounds the Position and Size
 * @return the Rectangle
 */
Rectangle new_rectangle(Color color, Bounds bounds);

/**
 * Changes the color of a rectangle.
 * 
 * @param rectangle the rectangle that will have the color changed.
 * @param color the new color.
 */
void rectangle_set_color(Rectangle rectangle, Color color);

//TO-DO: all the set and update for bounds, position and size. Also the draw function.
        //I don't think a process_events is necessary here.
//void rectangle_set_bounds(Rectangle rectangle, Bounds bounds);

#endif //SHAPE_H

