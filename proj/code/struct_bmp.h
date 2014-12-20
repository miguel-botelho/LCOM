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
