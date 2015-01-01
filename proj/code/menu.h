/**
 * @file menu.h
 * @author Miguel Botelho and Antonio Ramadas
 * @brief The file contains most of the handling of the menu
 */

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
#include "read_write.h"

extern char OPTION;
extern int RTC_COUNTER;
extern int tries;
extern int radius;
extern char tool;
extern char word[11];
extern char guess_ai[11];
extern char name[11];
extern int length;
extern int length_word;
extern int colour;

extern scores_t top_highscores;

extern int espaco;
extern int tentativas;
extern int ai_or_pvp;
extern int contador_high;
extern int contador_c;
extern int verdadeiro;

extern char day;
extern char year;
extern char month;
extern char hour;
extern char minutes;

/**
 * @brief Receives three colors, red, green and blue, and changes their values according to the selected colour
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
int is_highscore(position_t draw);

/**
 * @brief Calculates the score of the user
 *
 * @param tick the seconds that have passed
 *
 * @return score
 */
int score(int tick);

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
int HighScores_menu(bitmap_struct bitmaps, Bitmap ** numbers, Bitmap ** key_scancode);

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
int HumanMachine(bitmap_struct bitmaps, Bitmap ** numbers);

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
 */
void selectDraw();

/**
 * @brief Selects the colour from the frame
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

/**
 * @brief loads a random image
 *
 * @return random bitmap
 */
Bitmap* randImage();

/**
 * @brief cleans the word
 */
void cleanWord();

/**
 * @brief cleans the guess
 */
void cleanGuess();

/**
 * @brief cleans the name
 */
void cleanName();

/**
 * @brief reads the name of the user and prints it on the screen
 */
void printName(bitmap_struct bitmaps, Bitmap ** key_scancode, int key);

/**
 * @brief prints the Head to Head
 */
void printHead(bitmap_struct bitmaps, Bitmap ** key_scancode, int key, Bitmap ** numbers);

/**
 * @brief prints the Human Vs Machine
 */
void printMachine(bitmap_struct bitmaps, Bitmap ** key_scancode, int key, Bitmap ** numbers);

/**
 * @brief displays an highscore in the end of the game
 *
 * @param numbers the bitmap that contain the numbers
 * @param player the information about the player
 * @param key_scancode the bitmap containing the ketters
 * @param x the position in which to write
 */
void displayScore(Bitmap ** numbers, position_t* player, Bitmap ** key_scancode, int x);

/**
 * @brief displays the highscore read from txt
 *
 * @param numbers the bitmap that contain the numbers
 * @param player the information about the player
 * @param key_scancode the bitmap containing the ketters
 * @param x the position in which to write
 */
void displayHighScore(Bitmap ** numbers, position_t player, Bitmap ** key_scancode, int x);
#endif
