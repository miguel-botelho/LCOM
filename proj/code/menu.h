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

/**
 * @brief calculates the position in the menu, knowing if the user pressed one of the squares that allows you to go to another menu
 *
 * @param bitmaps (needed to delete)
 * @param video_copy (needed to change the color in the menu)
 *
 * @return 0 if the user pressed any option in the menu, 1 otherwise
 */
char position_menu(bitmap_struct bitmaps, char * video_copy);

/**
 * @brief exits the main menu
 *
 * @param bitmaps (needed to delete)
 *
 * @return 0 if menu successfully exited, 1 if otherwise
 */
int exit_menu(bitmap_struct bitmaps);

/**
 * @brief change the color of a certain part of the menu
 *
 * @param xi the initial x
 * @param xf the final x
 * @param yi the initial y
 * @param yf the final f
 * @param color_init initial color to be changed
 * @param color_final color that will stay instead of the other
 * @param video_copy to allow the change in colors
 *
 * @return 0 if color successfully changed, 1 otherwise
 */
int change_color(unsigned xi, unsigned xf, unsigned yi, unsigned yf, int color_init, int color_final, char * video_copy);

/**
 * @brief displays the high scores
 *
 */
int HighScores_menu();

/**
 * @brief the online option (serial port)
 *
 */
int Online_menu();

/**
 * @brief Player vs Player option (on the same pc)
 *
 */
int Head_to_Head();

/**
 * @brief Player vs Computer
 *
 */
int HumanMachine();
#endif
