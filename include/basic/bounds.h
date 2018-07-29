/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Bounds
 * Basic functions and definitions for Position and Size.
 */

#ifndef BOUNDS_H
#define BOUNDS_H

#include "utils/utils.h"
#include <SDL2/SDL.h>

///Debug
#define printR(r) printf("(%d, %d, %d, %d)\n", r.x, r.y, r.w, r.h);

/**
 * Struct used to represent a 2D point. Origin is set at the upper-left corner
 * of the screen.
 */
typedef struct Point{
	int x; //X position.
	int y; //Y position.
} Point;

/**
 * A better name than Point to representa Widget's position.
 */
typedef Point Position;

/**
 * Represents the <code>x</code> and <code>y</code> coordenates of a 2D vector.
 * It's a typedef of the struct <code>Point</code>.
 */
typedef Point Vector2;

/**
 * Representation of the size of a 2D object with <code>width</code> and
 * <code>height</code>.
 */
typedef struct Size{
	int w; //Width.
	int h; //Height.
} Size;

/**
 * Representation of a Widget in a 2D space with information about position and
 * size.
 */
typedef struct Bounds{
	///Position relative to parent's position.
	Position local;
	
	///Position relative to the window.
	Position global;

	///Size of the Widget containing width and height.
	Size size;
} Bounds;

///Constructor
/**
 * Creates a new Position from x and y coordinates.
 * 
 * @param x the x coordinate
 * @param y the y coordinate
 * @return the new position
 */
Position new_Position(int x, int y);

///Creates a new Point from x and y coordinates.
#define new_Point new_Position

///Creates a new 2D Vector from x and y coordinates.
#define new_Vector2 new_Position

/**
 * Creates a new Size from width and height.
 * 
 * @param width the width
 * @param height the height
 * @return the new size
 */
Size new_Size(int width, int height);

/**
 * Creates a new Bounds from <code>Position</code> and <code>Size</code>.
 * 
 * @param position the position
 * @param size the size
 * @return a new Bounds
 */
Bounds new_Bounds(Position position, Size size);

/**
 * Creates a new Bounds using integers for x, y, width and height.
 * 
 * @param x the x position
 * @param y the y position
 * @param w the width
 * @param h the height
 * @return a new Bounds
 */
Bounds new_Bounds_from_integer(int x, int y, int w, int h);

/**
 * Creates a new Bounds using an SDL_Rect struct.
 * 
 * @param rect an <code>SDL_Rect</code>
 * @return a new Bounds
 */
Bounds new_Bounds_from_SDL_Rect(SDL_Rect rect);

/**
 * Creates a new SDL_Rect struct.
 * 
 * @param x the x position
 * @param y the y position
 * @param w the width
 * @param h the height
 * @return a new SDL_Rect
 */
SDL_Rect new_rect(int x, int y, int w, int h);


///Operations
/**
 * Adds <code>p1</code> to <code>p2</code> and returns the result.
 * 
 * @param p1 a <code>Position</code>
 * @param p2 a <code>Position</code>
 * @return a new <code>Position</code> with the added values.
 */
Position position_add(Position p1, Position p2);

/**
 * Subtracts <code>p2</code> from <code>p1</code> and returns the result.
 * 
 * @param p1 a <code>Position</code>
 * @param p2 a <code>Position</code>
 * @return a new <code>Position</code> with the subtracted values.
 */
Position position_subtract(Position p1, Position p2);

/**
 * Adds <code>rect1</code> to <code>rect2</code> and returns the result.
 * 
 * @param rect1 an <code>SDL_Rect</code>
 * @param rect2 an <code>SDL_Rect</code>
 * @return an <code>SDL_Rect</code> with the added values
 */
SDL_Rect rect_add(SDL_Rect rect1, SDL_Rect rect2);


///Get
/**
 * Get local position and size in form of <code>SDL_Rect</code>.
 * 
 * @param bounds a <code>Bounds</code>
 * @return an <code>SDL_Rect</code> struct using local position and size
 */
SDL_Rect get_bounds_local(Bounds bounds);

/**
 * Get global position and size in form of <code>SDL_Rect</code>.
 * 
 * @param bounds a <code>Bounds</code>
 * @return an <code>SDL_Rect</code> struct using global position and size
 */
SDL_Rect get_bounds_global(Bounds bounds);


///Set
/**
 * Sets the new position relative to parent. Global position is updated.
 * 
 * @param bounds a <code>Bounds</code>
 * @param position the new local position
 */
void bounds_set_position_local(Bounds *bounds, Position position);

/**
 * Sets the new position relative to the window. Local position is updated.
 * 
 * @param bounds a <code>Bounds</code>
 * @param position the new global position
 */
void bounds_set_position_global(Bounds *bounds, Position position);

/**
 * Set the size. If <code>width</code> or <code>height</code> is <= 0, then it
 * will <b>NOT</b> be changed. You can safely pass 0 or a negative value to this
 * function if you want to change only the width or height.
 * 
 * @param bounds a <code>Bounds</code>
 * @param size
 */
void bounds_set_size(Bounds *bounds, Size size);

/**
 * Sets the new Position and Size of <code>bounds_dst</code> from a SDL_Rect
 * struct. This function will divide the struct into a Position and a Size
 * struct and call the <code>set_position_local</code> and
 * <code>set_size</code>.
 * 
 * @param bounds_dst a <code>Bounds</code>
 * @param bounds_src an <code>SDL_Rect</code>
 */
void set_bounds_from_SDL_Rect(Bounds *bounds_dst, SDL_Rect bounds_src);


///Update
/**
 * Update the position by adding the new values to the current position.
 * 
 * @param bounds a <code>Bounds</code>
 * @param position a <code>Position</code>
 */
void bounds_update_position(Bounds *bounds, Position position);

/**
 * Update the size adding the new values to the current size.
 * 
 * @param bounds a <code>Bounds</code>
 * @param size a <code>Size</code>
 */
void bounds_update_size(Bounds *bounds, Size size);

/**
 * Updates the Position and Size of <code>bounds_dst</code> from an
 * <code>SDL_Rect</code> struct.
 * 
 * @param bounds_dst a <code>Bounds</code>
 * @param bounds_src an <code>SDL_Rect</code>
 */
void update_bounds(Bounds *bounds_dst, SDL_Rect bounds_src);

/**
 * Update the <code>dst</code> by addind the values from <code>src</code>.
 * 
 * @param dst the <code>SDL_Rect</code> to be updated
 * @param src the source <code>SDL_Rect</code>
 */
void update_rect(SDL_Rect *dst, SDL_Rect src);


///Reach
/**
 * Returns the end point of <code>bounds</code> in X axis using local position.
 * 
 * @param bounds a <code>Bounds</code>
 * @return the <code>x</code> coordinate where <code>bounds</code> ends
 */
int bounds_reach_x_local(Bounds bounds);

/**
 * Returns the end point of <code>bounds</code> in Y axis using local position.
 * 
 * @param bounds a <code>Bounds</code>
 * @return the <code>y</code> coordinate where <code>bounds</code> ends
 */
int bounds_reach_y_local(Bounds bounds);

/**
 * Returns the end point of <code>bounds</code> in X axis using global position.
 * 
 * @param bounds a <code>Bounds</code>
 * @return the <code>x</code> coordinate where <code>bounds</code> ends
 */
int bounds_reach_x_global(Bounds bounds);

/**
 * Returns the end point of <code>bounds</code> in Y axis using global position.
 * 
 * @param bounds a <code>Bounds</code>
 * @return the <code>y</code> coordinate where <code>bounds</code> ends
 */
int bounds_reach_y_global(Bounds bounds);

/**
 * Returns the end point of <code>rect</code> in X axis.
 * 
 * @param rect an <code>SDL_Rect</code>
 * @return the <code>x</code> coordinate where <code>rect</code> ends
 */
int rect_reach_x(SDL_Rect rect);

/**
 * Returns the end point of <code>rect</code> in Y axis.
 * 
 * @param rect an <code>SDL_Rect</code>
 * @return the <code>y</code> coordinate where <code>rect</code> ends
 */
int rect_reach_y(SDL_Rect rect);


///Area
/**
 * Check if point is inside the area covered by <code>bounds</code> using local
 * position.
 * 
 * @param point the point that may be inside <code>bounds</code>
 * @param bounds a <code>Bounds</code>
 * @return <code>SDL_TRUE</code> if <code>point</code> is inside
 *         <code>bounds</code> and <code>SDL_FALSE</code> otherwise
 */
SDL_bool position_is_inside_bounds_local(Point point, Bounds bounds);

/**
 * Check if point is inside the area covered by <code>bounds</code> using global
 * position.
 * 
 * @param point the point that may be inside <code>bounds</code>
 * @param bounds a <code>Bounds</code>
 * @return <code>SDL_TRUE</code> if <code>point</code> is inside
 *         <code>bounds</code> and <code>SDL_FALSE</code> otherwise
 */
SDL_bool position_is_inside_bounds_global(Point point, Bounds bounds);

/**
 * Check if point is inside the area covered by <code>rect</code>.
 * 
 * @param point the point that may be inside <code>rect</code>
 * @param rect an <code>SDL_Rect</code>
 * @return <code>SDL_TRUE</code> if <code>point</code> is inside
 *         <code>bounds</code> and <code>SDL_FALSE</code> otherwise
 */
SDL_bool position_is_inside_rect(Point point, SDL_Rect rect);

/**
 * Checks if the area covered by <code>rect1</code> is inside the area covered
 * by <code>rect2</code>.
 * 
 * @param rect1 an <code>SDL_Rect</code> that may be inside <code>rect2</code>
 * @param rect1 an an <code>SDL_Rect</code>
 * @return <code>SDL_TRUE</code> if <code>rect1</code> is inside
 *         <code>rect2</code> and <code>SDL_FALSE</code> otherwise
 */
SDL_bool rect_is_inside_rect(SDL_Rect rect1, SDL_Rect rect2);

/**
 * Checks if any point in the area covered by <code>rect1</code> is inside the
 * area covered by <code>rect2</code>.
 * 
 * @param rect1 an <code>SDL_Rect</code>
 * @param rect2 an <code>SDL_Rect</code>
 * @return <code>SDL_TRUE</code> if any point of <code>rect1</code> is inside
 *	       <code>rect2</code> and <code>SDL_FALSE</code> otherwise
 */
SDL_bool rect_intersects_rect(SDL_Rect rect1, SDL_Rect rect2);

/**
 * Checks if the area covered by <code>bounds1</code> using <b>global</b>
 * position is inside the area covered by <code>bounds2</code>.
 * 
 * @param bounds1 a Bounds that may be inside <code>bounds2</code>
 * @param bounds2 a <code>Bounds</code>
 * @return <code>SDL_TRUE</code> if <code>bounds1</code> is inside
 *         <code>bounds2</code> and <code>SDL_FALSE</code> otherwise
 */
SDL_bool bounds_is_inside_bounds(Bounds bounds1, Bounds bounds2);

#endif //BOUNDS_H
