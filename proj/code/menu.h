#ifndef __MENU_H
#define __MENU_H

#include "menu_macros.h"
#include "struct_bmp.h"
#include "struct_scores.h"
#include "array_keyboard.h"
#include "mouse_struct.h"
#include "video_gr.h"
#include "keyboard_mouse_macros.h"
#include "device_interrupts.h"

extern char OPTION;

//in case of highscore it changes OPTION to GET_NAME
//return -1 if not highscore or the position otherwise
int is_highscore(scores_t *t, position_t *draw);

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// score = -135 * t + 10000, 0 <= t <= 60 (in seconds)
// 4 tries | discount of 100 per wrong
// number of letter * 150 | plus if right
// max number = 11500
// min number = 1900 - 4 * 100
int score(int tick);

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//print the letter in the given position (also numbers?)
//be careful to where this should point
//this function is easy to implement, but complex with process (think before do)
void print_letter();

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//erase a letter in the given position (also numbers?)
//be careful to where this should point
//this function is easy to implement, but complex with process (think before do)
void erase_letter();

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//given the position (*m) and the screen (*option), this function calls the respective menu
//this function has a switch statement and after finding the screen (meaning, the option)
//it will see where is the mouse over and call the respective function
int menu_handler (bitmap_struct bitmaps);

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//Human VS Machine option
//if button pressed go to the screen and changes the option
//otherwise just change the color of these option
void menu_handle_h_vs_m(mouse_st *m);

//....
//need to create the rest of the functions
// continue the menu_handle_h_vs_m(char *option, mouse_st *m); to the several options
// IMP: do not forget that the screen to enter the word need also to register the scancode
//            and the minimum word size is 3 and the max word length is 10 (the array will
//			  be sized 11 to store 0 (end of string))
//.....

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
char position_menu(bitmap_struct bitmaps);

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
int HighScores_menu(bitmap_struct bitmaps);

/**
 * @brief the online option (serial port)
 *
 */
int Online_menu(bitmap_struct bitmaps);

/**
 * @brief Player vs Player option (on the same pc)
 *
 */
int Head_to_Head(bitmap_struct bitmaps);

/**
 * @brief Player vs Computer
 *
 */
int HumanMachine(bitmap_struct bitmaps);
#endif
