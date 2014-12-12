#ifndef __TIMER_H
#define __TIMER_H

#include "subscribe_macros.h"

#include "lib.h"
#include "timer_macros.h"

/**
 * @brief Configures a timer to generate a square wave
 *
 * Does not change the LSB (BCD/binary) of the timer's control word.
 *
 * @param timer Timer to configure. (Ranges from 0 to 2)
 * @param freq Frequency of the square wave to generate
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_set_square(unsigned long timer, unsigned long freq);

/**
 * @brief Reads the input timer configuration via read-back command
 *
 * @param timer Timer whose config to read (Ranges from 0 to 2)
 * @param st    Address of memory position to be filled with the timer config
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_get_conf(unsigned long timer, unsigned char *st);

#endif /* __TIMER_H */
