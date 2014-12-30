#ifndef __MENU_H
#define __MENU_H

#include "frame.h"
#include "global_variables.h"
#include "menu_macros.h"
#include "struct_bmp.h"
#include "struct_scores.h"
#include "array_keyboard.h"
#include "mouse_struct.h"
#include "video_gr.h"
#include "keyboard_mouse_macros.h"
#include "device_interrupts.h"
#include "video_gr_macros.h"

extern char OPTION;
extern int RTC_COUNTER;
extern int tries;
extern int radius;
extern char tool;
extern int colour;
extern scores_t top_highscores;
extern int espaco;
extern int tentativas;
extern int ai_or_pvp;

/**
 * @brief Receives three colors, red, green and blue, and the buffer, and changes their values
 *
 * @param int red the red color
 * @param int green the green color
 * @param int blue the blue color
 */
void getrgb(int *red, int *green, int *blue);

/**
 * @brief Checks if the new score is an highscore, and stores it
 *
 * @param draw the draw that the user made
 *
 * @return the place of the user (1,2,3,4 or 5)
 */
int is_highscore(position_t *draw);

/**
 * @brief Calculates the score of the user
 *
 * @param tick the seconds that have passed
 *
 * @return score
 */
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
/**
 * @brief handles the menu options
 *
 * @param bitmaps the different screens
 * @param numbers the different bitmap numbers
 * @param key_scancode the different bitmap letters
 *
 * @return -1 if the option doesn't exist
 */
int menu_handler (bitmap_struct bitmaps, Bitmap ** numbers, Bitmap ** key_scancode);

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
 * @brief sees if anything was pressed in the menu and changes the state machine
 *
 * @param bitmaps the different screens
 * @param numbers the different bitmap numbers
 * @param key_scancode the different bitmap letters
 *
 * @return 0 if anything was pressed, 1 if not
 */
char position_menu(bitmap_struct bitmaps, Bitmap ** numbers, Bitmap ** key_scancode);

/**
 * @brief exits the menu
 *
 * @param bitmaps the different screens (delete)
 * @param numbers the different bitmap numbers (delete)
 * @param key_scancode the different bitmap letters (delete)
 *
 * @return 0 if sucessfully exited, 1 otherwise
 */
int exit_menu(bitmap_struct bitmaps, Bitmap ** numbers, Bitmap ** key_scancode);

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
 * @param bitmaps needed to change the screen
 *
 * @return 0 if sucessfully, 1 otherwise
 */
int HighScores_menu(bitmap_struct bitmaps);

/**
 * @brief the serial port game option
 *
 * @param bitmaps needed to change the screen
 *
 * @return 0 if sucessfully, 1 otherwise
 */
int Online_menu(bitmap_struct bitmaps);

/**
 * @brief the AI option
 *
 * @param bitmaps needed to change the screen
 * @param numbers needed to display the tries
 *
 * @return 0 if sucessfully, 1 otherwise
 */
int HumanMachine(bitmap_struct bitmaps);

/**
 * @brief the PVP option
 *
 * @param bitmaps needed to change the screen
 * @param numbers needed to display the tries
 *
 * @return 0 if sucessfully, 1 otherwise
 */
int Head_to_Head(bitmap_struct bitmaps, Bitmap ** numbers);

/**
 * @brief Selects the tool from the frame
 *
 */
void selectDraw();

/**
 * @brief Selects the colour from the frame
 *
 */
void selectColour();

/**
 * @brief Handler for the drawings
 *
 * @return -1 if tool is not available
 */
int toolHandler();

/**
 * @brief displays the Timer for numbers < 10
 *
 * @param contador the number to be displayed
 * @param numbers the bitmaps that have the numbers
 * @param bitmaps needed to change the screen
 *
 * @return 0 if sucessfully, 1 otherwise
 */
int displayTimer(int contador, Bitmap ** numbers, bitmap_struct bitmaps);

/**
 * @brief displays the Timer for numbers >= 10
 *
 * @param contador the number to be displayed
 * @param numbers the bitmaps that have the numbers
 * @param bitmaps needed to change the screen
 *
 * @return 0 if sucessfully, 1 otherwise
 */
int displayTimer10(int contador, Bitmap ** numbers, bitmap_struct bitmaps);

/**
 * @brief writes the name of the player in pre head to head
 *
 * @param name name of the player
 * @param key_scancode bitmaps that have all the letters
 * @param bitmaps needed to change the screen
 *
 * @return 0 if sucessfully, 1 otherwise
 */
void WriteArray(char * name, int length, Bitmap ** key_scancode, bitmap_struct bitmaps);

/**
 * @brief writes the name of the player in frame option
 *
 * @param name name of the player
 * @param key_scancode bitmaps that have all the letters
 * @param bitmaps needed to change the screen
 *
 * @return 0 if sucessfully, 1 otherwise
 */
void WriteArrayFrame(char * name, int length, Bitmap ** key_scancode, bitmap_struct bitmaps);

/**
 * @brief writes the guess of the player
 *
 * @param name name of the player
 * @param key_scancode bitmaps that have all the letters
 * @param bitmaps needed to change the screen
 *
 * @return 0 if sucessfully, 1 otherwise
 */
void WriteArrayFrame2(char * name, int length, Bitmap ** key_scancode, bitmap_struct bitmaps);
#endif
