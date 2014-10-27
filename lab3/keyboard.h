#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

////////////////////////////////////////// MACROS FOR TIMER //////////////////////////////////////////

#define TIMER_FREQ  1193182    /**< @brief clock frequency for timer in PC and AT */

#define TIMER_LSB_MSB		(TIMER_LSB | TIMER_MSB) /**< @brief Initialize LSB first and MSB afterwards */

#define TIMER_0			0x40 /**< @brief Timer 0 count register */
#define TIMER_1			0x41 /**< @brief Timer 1 count register */
#define TIMER_2			0x42 /**< @brief Timer 2 count register */
#define TIMER_CTRL		0x43 /**< @brief Control register */

#define TIMER_SEL0		0x00     /**< @brief Control Word for Timer 0 */
#define TIMER_SEL1		BIT(6)   /**< @brief Control Word for Timer 1 */
#define TIMER_SEL2		BIT(7)   /**< @brief Control Word for Timer 2 */
#define TIMER0_IRQ	        0    /**< @brief Timer 0 IRQ line */

#define TIMER_LSB		BIT(4)  /**< @brief Initialize Counter LSB only */
#define TIMER_MSB		BIT(5)  /**< @brief Initialize Counter MSB only */

#define TIMER_RB_COUNT_         BIT(5)
#define TIMER_RB_CMD		(BIT(7)|BIT(6))  /**< @brief Read Back Command */
#define TIMER_RB_SEL(n)         BIT((n)+1)

////////////////////////////////////////// MACROS FOR KEYBOARD //////////////////////////////////////////

#define DELAY_US 	20000
#define KBC_IRQ		0x01
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
#define KBD_ESC_KEY 0x81


////////////////////////////////////////// GLOBAL VARIABLES //////////////////////////////////////////

extern int khook_id; //hook_id tem de estar entre [0..30] //kbd
extern int hook_id; //hook_id tem de estar entre [0..30] //timer
extern unsigned long global_counter; //contador para o timer (contar o nr de segundos)
extern unsigned long elem; //led a ligar/desligar



int kbd_unsubscribe_int(); //Cancela a subscrição das interrupções do keyboard

int kbd_subscribe_int(void ); //Ativa a subscrição das interrupções do keyboard

int kbd_scan_c(int *apt); //Lê a tecla em C

//int kbd_scan_ass(); //Lê a tecla em assembly

int kbc_cmd_send(unsigned long cmd); //envia o comando para o input

int kbc_cmd_receive(); //recebe todo o output

int timer_test_square(unsigned long freq); //Programa o Timer 0 para gerar o modo de square com frequencia freq

int timer_set_square(unsigned long timer, unsigned long freq); //Configura um timer para gerar uma square wave

int timer_subscribe_int(void ); //Ativa a subscrição das interrupções do Timer 0

int timer_unsubscribe_int(); //Cancela a subscrição das interrupções do Timer 0

void timer_int_handler(); //Incrementa o global counter

int timer_get_conf(unsigned long timer, unsigned char *st); //Lê o input do timer através de read-back command

void kbd_int_handler(); //Envia o comando para o keyboard

#endif /* __KEYBOARD_H */
