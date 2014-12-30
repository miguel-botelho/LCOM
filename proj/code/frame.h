#ifndef __FRAME_H
#define __FRAME_H

#include"mouse_struct.h"
#include"video_gr.h"
#include"global_variables.h"
#include "bitmap.h"

extern int radius;
extern int colour;
extern int screen_abs;
extern int screen_current;

#define NUMBER_TO_CHANGE			27

/**
 * @brief Draws a line in the painting screen
 *
 * @param mouse_st previous the previous state of the mouse
 */
void draw_line(mouse_st previous);

/**
 * @brief draws a circle in the painting screen, with a radius and a colour
 */
void draw_circle();

/**
 * @brief draws the brush in the painting screen
 */
void draw_brush();

/**
 * @brief Sees if the user is pressing the right conditions and if he is, calls draw_line
 */
void drawLINE();

/**
 * @brief Sees if the user is pressing the right conditions and if he is, calls draw_line
 */
void draw_pencil();

/**
 * @brief Changes the colour that was in screen_buffer when the user pressed the left button, to the current colour
 */
void draw_bucket();

/**
 * @brief draws a square in the painting screen
 */
void draw_square();

/**
 * @brief undos what the user wrote on the screen
 */
void undo();

/**
 * @brief redos what the user undoed
 */
void redo();

/**
 * @brief increases the radius
 */
void plus();

/**
 * @brief decreases the radius
 */
void minus();

/**
 * @brief paints the painting screen to white
 */
void white_screen();

#endif
