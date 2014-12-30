/**
 * @file struct_bmp.h
 * @author Miguel Botelho and Antonio Ramadas
 * @brief The file containing the images for the screen
 */

#ifndef __STRUCT_BMP_H
#define __STRUCT_BMP_H

#include "bitmap.h"

typedef struct
{
	Bitmap* background;
	Bitmap* highscores;
	Bitmap* mouse;
	Bitmap* frame;
	Bitmap* pre_head_to_head;
	Bitmap* lost;
	Bitmap* win;
} bitmap_struct;

#endif
