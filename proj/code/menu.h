#ifndef __MENU_H
#define __MENU_H

#include "struct_bmp.h"
#include "struct_scores.h"

/**
 * @brief Load the bitmaps
 *
 * By loading every bitmaps, this function may take some time. The argument is filled with the bitmaps.
 *
 * @param *t struct of bitmaps
 *
 */
void bitmaps_load(bitmap_struct *t);

#endif
