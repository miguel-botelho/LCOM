#ifndef __MOUSE_H
#define __MOUSE_H

#include "subscribe_macros.h"

#include "lib.h"
#include "mouse_struct.h"
#include "keyboard_mouse_macros.h"

/**
 * @brief Recept the packets via interrupts
 *
 * Fill the struct with the packets received from the mouse
 * Exits after receiving the number of packets.
 *
 * @param hi the mouse id (required to read the 3-row bytes)
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int test_packet(); //hi = hook id

/**
 * @brief Fill the mouse struct
 *
 * Fill the mouse struct.
 *
 */
void fill_struct(char *a);

/**
 * @brief Interprets a 8 bits negative number
 *
 * Interprets a 8 bits negative number. Returns it in the correct way (2 complement)
 *
 * @return Return 0 upon success and non-zero otherwise
 */
char neg8bits(char neg);

int mouse_int_handler(unsigned long cmd);
int mouse_send_command(unsigned long cmd);
int mouse_send_first_command();
int mouse_cmd_receive();

#endif /* __MOUSE_H */
