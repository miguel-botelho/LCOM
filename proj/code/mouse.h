#ifndef __MOUSE_H
#define __MOUSE_H

#include "subscribe_macros.h"

#include "lib.h"
#include "mouse_struct.h"
#include "keyboard_mouse_macros.h"


/**
 * @brief Fill the mouse struct
 *
 * Fill the mouse struct.
 *
 * @param *a pointer to the array to fill the mouse struct
 *
 * @return void
 *
 */
void fill_struct(char *a);

/**
 * @brief Interprets a 8 bits negative number
 *
 * Interprets a 8 bits negative number. Returns it in the correct way (2 complement)
 *
 * @param neg Number to be interpreted as negative
 *
 * @return Return 0 upon success and non-zero otherwise
 */
char neg8bits(char neg);

/**
 * @brief Take cares of the process of sending a command
 *
 * Call different functions to send the cmd
 *
 * @param cmd command to be sent
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_int_handler(unsigned long cmd);

/**
 * @brief Send command
 *
 * Send the argument to the respetive port
 *
 * @param cmd command to be sent
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_send_command(unsigned long cmd);

/**
 * @brief Send first command
 *
 * Send the first command before the actual one (see mouse_send_command() followed by mouse_int_handler())
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_send_first_command();

/**
 * @brief Receives the consequence of the command sent
 *
 * Receive the command of the mouse
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_cmd_receive();

#endif /* __MOUSE_H */
