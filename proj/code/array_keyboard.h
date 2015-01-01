/**
 * @file array_keyboard.h
 * @author Miguel Botelho and Antonio Ramadas
 * @brief The file containing the functions for filling the arrays of bitmaps
 */

#ifndef __ARRAY_KEYBOARD_H
#define __ARRAY_KEYBOARD_H

#include "bitmap.h"
#include "menu_macros.h"

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
