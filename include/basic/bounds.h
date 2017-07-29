/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Bounds
 * Basic functions and definitions for Position and Size.
 */

#ifndef BOUNDS_H
#define BOUNDS_H

#include <stdlib.h>
#include <SDL2/SDL.h>

#ifndef TYPE_BOOL
#define TYPE_BOOL
	typedef int bool;
	#define false 0
	#define true 1
#endif //MOUSE_BOOL

/**
 * Struct used to represent a 2D point. Origin is set at the upper-left corner
 * of the screen.
 */
struct Point_{
    int x; //X position.
    int y; //Y position.
};
/**
 * Struct used to represent a 2D point. Origin is set at the upper-left corner
 * of the screen.
 */
typedef struct Point_ Point;

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
struct Size_{
    int w;  //Width.
    int h;  //Height.
};
/**
 * Representation of the size of a 2D object with <code>width</code> and
 * <code>height</code>.
 */
typedef struct Size_ Size;


/**
 * Representation of a Widget in a 2D space with information about position and
 * size.
 */
struct Bounds_{
    /**
     * Position relative to parent's origin. Use when calculating position
     * relative to other widgets
     */
    Position origin;
    
    /**
     * Position relative to parent's camera. This will be the used in most
     * cases.
     */
    Position camera;
    
    /**
     * Size of the Widget containing width and height.
     */
    Size size;
};
/**
 * Representation of a Widget in a 2D space with information about position and
 * size.
 */
typedef struct Bounds_ Bounds;

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
 * Camera position will have the same value as origin posistion
 * 
 * @param position the position
 * @param size the size
 * @return a new Bounds
 */
Bounds new_Bounds(Position position, Size size);

/**
 * Creates a new Bounds using integers from x, y, width and height.
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
 * @param rect an SDL_Rect struct containing x, y, width and height
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


///Get
/**
 * Get the position relative to parent's origin.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return the origin position
 */
Position get_position_origin(Bounds bounds);

/**
 * Get the position relative to the camera.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return the camera position
 */
Position get_position_camera(Bounds bounds);

/**
 * Get origin position and size in form of <code>SDL_Rect</code>.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return an <code>SDL_Rect</code> struct using origin position and size
 */
SDL_Rect get_bounds_origin(Bounds bounds);

/**
 * Get camera position and size in form of <code>SDL_Rect</code>.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return an <code>SDL_Rect</code> struct using camera position and size
 */
SDL_Rect get_bounds_camera(Bounds bounds);

/**
 * Get the size of the Bounds.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return the size
 */
Size get_size(Bounds bounds);


///Set
/**
 * Sets the new position relative to origin. Camera position
 * <b>WILL</b> be updated to the difference of the new and old origin's
 * posistion.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @param position the new origin position
 */
void set_position_origin(Bounds *bounds, Position position);

/**
 * Set the position relative to camera. Origin position is <b>NOT</b> updated.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @param position the new position of the camera
 */
void set_position_camera(Bounds *bounds, Position position);

/**
 * Set both origin and camera to the same value.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @param position the new position of origin and camera
 */
void reset_position(Bounds *bounds, Position position);

/**
 * Set the size. If <code>width</code> or <code>height</code> is <= 0, then it
 * will <b>NOT</b> be changed. You can safely pass 0 or a negative value to this
 * function if you want to change only the width or height.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @param size
 */
void set_size(Bounds *bounds, Size size);

/**
 * Sets the new Position and Size of <code>bounds_dst</code> from a SDL_Rect
 * struct. This function will divide the struct into a Position and a Size
 * struct and call the <code>set_position_origin</code> and
 * <code>set_size</code>.
 * 
 * @param bounds_dst a Bounds containing origin and camera Position and Size
 * @param bounds_src an SDL_Rect struct containing x, y, width and height
 */
void set_bounds_from_SDL_Rect(Bounds *bounds_dst, SDL_Rect bounds_src);


///Update
/**
 * Update the origin position by adding the new values to the current position.
 * <b>Camera position will also be updated.</b>
 * <br><br>
 * <b>Example</b>: if <code>bounds->origin.x</code> is <code>35</code> and
 * <code>position.x</code> is <code>-10</code>, then the new value of
 * <code>bounds->origin.x</code> will be <code>25</code>.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @param position the values of <code>x</code> and <code>y</code> to be added
 *        to the current origin position
 */
void update_position_origin(Bounds *bounds, Position position);

/**
 * Update the camera position by adding the new values to the current position.
 * Origin position is <b>NOT</b> updated.
 * <br><br>
 * <b>Example</b>: if <code>bounds->camera.x</code> is <code>35</code> and
 * <code>position.x</code> is <code>-10</code>, then the new value of
 * <code>bounds->camera.x</code> will be <code>25</code>.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @param position the values of <code>x</code> and <code>y</code> to be added
 *        to the current camera position
 */
void update_position_camera(Bounds *bounds, Position position);

/**
 * Update the size adding the new values to the current size.
 * <br><br>
 * <b>Example</b>: if <code>bounds->size.w</code> is <code>35</code> and
 * <code>size.w</code> is <code>-10</code>, then the new value of
 * <code>bounds->size.w</code> will be <code>25</code>.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @param size the values of <code>width</code> and <code>height</code> to be
 *        added to the current size
 */
void update_size(Bounds *bounds, Size size);

/**
 * Updates the Position and Size of <code>bounds_dst</code> from a SDL_Rect
 * struct. This function will divide the struct into a Position and a Size
 * struct and call the <code>update_position_origin</code> and
 * <code>update_size</code>.
 * 
 * @param bounds_dst a Bounds containing origin and camera Position and Size
 * @param bounds_src an SDL_Rect struct containing x, y, width and height
 */
void update_bounds(Bounds *bounds_dst, SDL_Rect bounds_src);

/**
 * Update the SDL_Rect by addind the values from <code>dst</code> to
 * <code>src</code>.
 * 
 * @param dst the SDL_Rect to be updated
 * @param src the source SDL_Rect
 */
void update_rect(SDL_Rect *dst, SDL_Rect src);


///Reach
/**
 * Returns the end point of <code>bounds</code> in X using origin position.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return the <code>x</code> coordinate where <code>bounds</code> ends
 */
int bounds_reach_x_origin(Bounds bounds);

/**
 * Returns the end point of <code>bounds</code> in Y using origin position.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return the <code>y</code> coordinate where <code>bounds</code> ends
 */
int bounds_reach_y_origin(Bounds bounds);

/**
 * Returns the end point of <code>bounds</code> in X using camera position.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return the <code>x</code> coordinate where <code>bounds</code> ends
 */
int bounds_reach_x_camera(Bounds bounds);

/**
 * Returns the end point of <code>bounds</code> in Y using camera position.
 * 
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return the <code>y</code> coordinate where <code>bounds</code> ends
 */
int bounds_reach_y_camera(Bounds bounds);

/**
 * Returns the end point of <code>rect</code> in X using origin position.
 * 
 * @param rect an SDL_Rect struct containing x, y, width and height
 * @return the <code>x</code> coordinate where <code>rect</code> ends
 */
int rect_reach_x(SDL_Rect rect);

/**
 * Returns the end point of <code>rect</code> in Y using origin position.
 * 
 * @param rect an SDL_Rect struct containing x, y, width and height
 * @return the <code>y</code> coordinate where <code>rect</code> ends
 */
int rect_reach_y(SDL_Rect rect);

/**
 * Check if point is inside the area covered by <code>bounds</code> using origin
 * position.
 * 
 * @param point the point that may be inside <code>bounds</code>
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return <code>true</code> if <code>point</code> is inside
 *         <code>bounds</code> and <code>false</code> otherwise
 */
bool position_is_inside_bounds_origin(Point point, Bounds bounds);

/**
 * Check if point is inside the area covered by <code>bounds</code> using camera
 * position.
 * 
 * @param point the point that may be inside <code>bounds</code>
 * @param bounds a Bounds containing origin and camera Position and Size
 * @return <code>true</code> if <code>point</code> is inside
 *         <code>bounds</code> and <code>false</code> otherwise
 */
bool position_is_inside_bounds_camera(Point point, Bounds bounds);

/**
 * Check if point is inside the area covered by <code>rect</code>.
 * 
 * @param point the point that may be inside <code>bounds</code>
 * @param rect an SDL_Rect struct containing x, y, width and height
 * @return <code>true</code> if <code>point</code> is inside
 *         <code>bounds</code> and <code>false</code> otherwise
 */
bool position_is_inside_rect(Point point, SDL_Rect rect);

/**
 * Checks if the area covered by <code>rect1</code> is inside the area covered
 * by <code>rect2</code>.
 * 
 * @param rect1 an <code>SDL_Rect</code> that may be inside <code>rect2</code>
 * @param rect1 an an SDL_Rect struct containing x, y, width and height
 * @return <code>true</code> if <code>rect1</code> is inside
 *         <code>rect2</code> and <code>false</code> otherwise
 */
bool rect_is_inside_rect(SDL_Rect rect1, SDL_Rect rect2);

/**
 * Checks if the area covered by <code>bounds1</code> using <b>origin</b>
 * position is inside the area covered by <code>bounds2</code> using
 * <b>origin</b> position.
 * 
 * @param bounds1 a Bounds that may be inside <code>bounds2</code>
 * @param bounds2 a Bounds containing origin and camera Position and Size
 * @return <code>true</code> if <code>bounds1</code> is inside
 *         <code>bounds2</code> and <code>false</code> otherwise
 */
bool bounds_origin_is_inside_bounds_origin(Bounds bounds1, Bounds bounds2);

/**
 * Checks if the area covered by <code>bounds1</code> using <b>origin</b>
 * position is inside the area covered by <code>bounds2</code> using
 * <b>camera</b> position.
 * 
 * @param bounds1 a Bounds that may be inside <code>bounds2</code>
 * @param bounds2 a Bounds containing origin and camera Position and Size
 * @return <code>true</code> if <code>bounds1</code> is inside
 *         <code>bounds2</code> and <code>false</code> otherwise
 */
bool bounds_origin_is_inside_bounds_camera(Bounds bounds1, Bounds bounds2);

/**
 * Checks if the area covered by <code>bounds1</code> using <b>camera</b>
 * position is inside the area covered by <code>bounds2</code> using
 * <b>origin</b> position.
 * 
 * @param bounds1 a Bounds that may be inside <code>bounds2</code>
 * @param bounds2 a Bounds containing origin and camera Position and Size
 * @return <code>true</code> if <code>bounds1</code> is inside
 *         <code>bounds2</code> and <code>false</code> otherwise
 */
bool bounds_camera_is_inside_bounds_origin(Bounds bounds1, Bounds bounds2);

/**
 * Checks if the area covered by <code>bounds1</code> using <b>camera</b>
 * position is inside the area covered by <code>bounds2</code> using
 * <b>camera</b> position.
 * 
 * @param bounds1 a Bounds that may be inside <code>bounds2</code>
 * @param bounds2 a Bounds containing origin and camera Position and Size
 * @return <code>true</code> if <code>bounds1</code> is inside
 *         <code>bounds2</code> and <code>false</code> otherwise
 */
bool bounds_camera_is_inside_bounds_caemera(Bounds bounds1, Bounds bounds2);

#endif //BOUNDS_H
