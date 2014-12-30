#ifndef __ARRAY_KEYBOARD_H
#define __ARRAY_KEYBOARD_H

#include "bitmap.h"

/**
 * @brief fills the array of bitmaps that have the fonts for the letter
 *
 * @param Bitmap ** array of bitmaps
 */
void fill_key_scancode(Bitmap ** scan_code);

/**
 * @brief fills the array of bitmaps that have the fonts for the number
 *
 * @param Bitmap ** array of numbers
 */
void fill_number(Bitmap ** numbers);

#endif
