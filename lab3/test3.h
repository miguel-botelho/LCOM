#ifndef __TEST3_H
#define __TEST3_H

#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

/////////////////////

#define TIMER_SEL0		0x00     /**< @brief Control Word for Timer 0 */
#define TIMER_LSB_MSB		(TIMER_LSB | TIMER_MSB) /**< @brief Initialize LSB first and MSB afterwards */
#define TIMER_CTRL		0x43 /**< @brief Control register */
#define TIMER_0			0x40 /**< @brief Timer 0 count register */
#define TIMER_FREQ  1193182    /**< @brief clock frequency for timer in PC and AT */
#define TIMER_SEL1		BIT(6)   /**< @brief Control Word for Timer 1 */
#define TIMER_1			0x41 /**< @brief Timer 1 count register */
#define TIMER_SEL2		BIT(7)   /**< @brief Control Word for Timer 2 */
#define TIMER_2			0x42 /**< @brief Timer 2 count register */
#define TIMER0_IRQ	        0    /**< @brief Timer 0 IRQ line */
#define TIMER_LSB		BIT(4)  /**< @brief Initialize Counter LSB only */
#define TIMER_MSB		BIT(5)  /**< @brief Initialize Counter MSB only */
#define TIMER_RB_COUNT_         BIT(5)
#define TIMER_RB_CMD		(BIT(7)|BIT(6))  /**< @brief Read Back Command */
#define TIMER_RB_SEL(n)         BIT((n)+1)

/////////////////////

#define DELAY_US 	20000
#define BIT(n) 		(0x01<<(n))
#define STAT_REG	0X64
#define KBC_CMD_REG	0x64
#define OUT_BUF		0x60
#define PAR_ERR		0x80
#define TO_ERR		0x40
#define CBUFFER_EKBD	0xF4
#define LEDS		0xED
#define ACK			0x00FA
#define RESEND		0xFE
#define ERROR		0xFC

int kbd_unsubscribe_int();

int kbd_subscribe_int(void );

int kbd_scan_c(int *apt);

int kbd_scan_ass();

int kbc_cmd_send(unsigned long cmd);

int kbc_cmd_receive();

int timer_test_square(unsigned long freq);

int timer_set_square(unsigned long timer, unsigned long freq);

int timer_test_square(unsigned long freq);

int timer_subscribe_int(void );

void timer_int_handler();

int timer_get_conf(unsigned long timer, unsigned char *st);

/** @defgroup test3 test3
 * @{
 *
 * Functions for testing the kbd code
 */

/** 
 * @brief To test reading of scancode via KBD interrupts 
 * 
 * Displays the scancodes received from the keyboard
 * Exits upon release of the ESC key
 * 
 * @param ass Which IH to use: if 0, in C, otherwise in assembly
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_test_scan(unsigned short ass);

/**
 * @brief To test keyboard commands 
 * 
 * Toggles LED indicators, one per second, according to the 
 *  arguments
 * 
 * @param n number of elements of the second argument
 * @param leds array with the LEDs to toggle (Ranges from 0 t0 2)
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_test_leds(unsigned short n, unsigned short *leds);

/** 
 * @brief To test handling of more than one interrupt
 * 
 *  Similar to kbd_test_scan() except that it 
 *  should terminate also if no scancodes are received for n seconds
 * 
 * @param n Number of seconds without scancodes before exiting
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_test_timed_scan(unsigned short n);

#endif /* __TEST3_H */
