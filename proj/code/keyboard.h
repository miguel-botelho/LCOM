#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "subscribe_macros.h"

#include "lib.h"
#include "keyboard_mouse_macros.h"

char get_char(int key);

/**
 * @brief Interpret the scancode
 *
 * Interprets the keys' interrupts.
 *
 * @param *ret modifies this parameter (it is the key pressed)
 *
 * @return Return 0 upon makecode and non-zero on breakcode and -1 on led
 */
int kbd_test_scan(int *ret);

/**
 * @brief To test keyboard commands
 *
 * Toggles LED indicators according to the argument
 *
 * @param led the led to enabled or disabled
 *
 * @return Return NULL to show that a led cmd had been sent
 */
int kbd_test_leds(char led);

/**
 * @brief Read the scancode
 *
 * Read the keys' interrupts.
 *
 * @param *apt modifies this parameter (it is the key pressed)
 *
 * @return Return 0 upon 1 byte key and non-zero on 2 byte key
 */
int kbd_scan_c(int *apt);

/**
 * @brief Send the led to keyboard
 *
 * Turn on the lights of the respective led on the keyboard.
 *
 * @param led is the led key's code
 */
void kbd_int_handler(unsigned long led);

/**
 * @brief Send cmd to input
 *
 * Send cmd to device
 *
 * @param cmd the cmd to be sent
 *
 * @return Return 0 upon cmd successfully sent
 */
int kbc_cmd_send(unsigned long cmd);

/**
 * @brief Return data
 *
 * Read the output and returns the data read
 *
 * @return Return data
 */
int kbc_cmd_receive();

#endif /* __KEYBOARD_H */
