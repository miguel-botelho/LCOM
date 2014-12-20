#ifndef __MENU_H
#define __MENU_H

#include "struct_bmp.h"
#include "struct_scores.h"
#include "array_keyboard.h"
#include "mouse_struct.h"
#include "video_gr.h"
#include "keyboard_mouse_macros.h"
#include "device_interrupts.h"

/**
 * @brief Load the bitmaps
 *
 * By loading every bitmaps, this function may take some time. The argument is filled with the bitmaps.
 *
 * @param *t struct of bitmaps
 *
 */
void bitmaps_load(bitmap_struct *t);

char position_menu(bitmap_struct bitmaps, char * video_copy);
void exit_menu(bitmap_struct bitmaps);

int change_color(unsigned xi, unsigned xf, unsigned yi, unsigned yf, int color_init, int color_final, char * video_copy);

#endif
