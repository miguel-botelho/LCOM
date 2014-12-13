#ifndef __DEVICE_INTERRUPTS_H
#define __DEVICE_INTERRUPTS_H

#include "lib.h"
#include "subscribe_macros.h"

// This file only subscribes and unsubscribes

/**
 * @brief Subscribe all devices
 *
 * Subscribe all devices by calling the diferent functions.
 *
 * @return -1 upon failure or non -1 otherwise
 */
int subscribe_all();

/**
 * @brief Unsubscribe all devices
 *
 * Unsubscribe all devices by calling the diferent functions.
 *
 * @return -1 upon failure or non -1 otherwise
 */
int unsubscribe_all();

/**
 * @brief Subscribe timer
 *
 * Subscribe timer.
 *
 * @return -1 upon failure or non -1 otherwise
 */
int timer_subscribe_int();

/**
 * @brief Unsubscribe timer
 *
 * Unsubscribe timer.
 *
 * @return -1 upon failure or non -1 otherwise
 */
int timer_unsubscribe_int();

/**
 * @brief Subscribe keyboard
 *
 * Subscribe keyboard.
 *
 * @return -1 upon failure or non -1 otherwise
 */
int kbd_subscribe_int();

/**
 * @brief Unsubscribe keyboard
 *
 * Unsubscribe keyboard.
 *
 * @return -1 upon failure or non -1 otherwise
 */
int kbd_unsubscribe_int();

/**
 * @brief Subscribe mouse
 *
 * Subscribe mouse.
 *
 * @return -1 upon failure or non -1 otherwise
 */
int mouse_subscribe_int();

/**
 * @brief Unsubscribe mouse
 *
 * Unsubscribe mouse.
 *
 * @return -1 upon failure or non -1 otherwise
 */
int mouse_unsubscribe_int();

/**
 * @brief Subscribe rtc
 *
 * Subscribe rtc.
 *
 * @return -1 upon failure or non -1 otherwise
 */
int rtc_subscribe_int();

/**
 * @brief Unsubscribe rtc
 *
 * Unsubscribe rtc.
 *
 * @return -1 upon failure or non -1 otherwise
 */
int rtc_unsubscribe_int();

#endif /* __DEVICE_INTERRUPTS_H */
