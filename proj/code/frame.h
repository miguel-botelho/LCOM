#ifndef __FRAME_H
#define __FRAME_H

#include"mouse_struct.h"
#include"video_gr.h"
#include"global_variables.h"

extern int radius;
extern int colour;

//remember to draw only inside the board!!!
//collisions?

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void draw_line(mouse_st previous); //<- the same from the previous lab with some improvements

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//obviously needs more arguments
void draw_circle();

void draw_brush();

void drawLINE();

void draw_pencil();

void draw_bucket();

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//obviously needs more arguments
//do not forget to fill the array with color
void draw_square();

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//just run through the white board filling with the colors from the array
//this function is easy to implement, but complex with process (think before do)
void undo();

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//just run through the white board filling with the colors from the array
//this function is easy to implement, but complex with process (think before do)
void redo();


void plus();


void minus();

void white_screen();

#endif
