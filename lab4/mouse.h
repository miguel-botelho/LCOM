#ifndef __MOUSE_H
#define __MOUSE_H

#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

extern int mhook_id;
extern int hook_id;

extern char global_bool1;
extern char global_bool2;

#define MOUSE_IRQ	12
#define DELAY_US 	20000
#define BIT(n) 		(0x01<<(n))
#define OUT_BUF		0x60
#define ESDP		0xF4
#define IBF			0x02
#define OBF			0x01
#define MC			0xD4
#define COMMAND_PORT 0x60
#define PAR_ERR		0x80
#define TO_ERR		0x40
#define MOUSE_DATA	0x20
#define DISABLE_STREAM	0xF5
#define SET_STREAM	0xEA
#define STAT_REG	0x64
#define STATUS_REQUEST 0xE9

#define TIMER0_IRQ	        0    /**< @brief Timer 0 IRQ line */


#define ACK			0xFA
#define NACK		0xFE
#define ERROR		0xFC



int mouse_subscribe_int();
int mouse_unsubscribe_int();
int mouse_int_handler(unsigned long cmd);
int mouse_send_command(unsigned long cmd);
int mouse_send_first_command();
int mouse_cmd_receive();
void mouse_printf(char a[]);
int timer_subscribe_int(void );
int timer_unsubscribe_int();
int get_packets(char mouse);
int mouse_clean_buffer();
//void check_hor_line(event_t *evt);


#endif
