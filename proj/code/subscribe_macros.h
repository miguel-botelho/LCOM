#ifndef __SUBSCRIBE_MACROS_H
#define __SUBSCRIBE_MACROS_H

#define BIT(n) 					(0x01<<(n))

#define macro_hook_id_keyboard 	(0x01)
#define macro_hook_id_mouse 	(0x02)
#define macro_hook_id_timer 	(0x04)
#define macro_hook_id_rtc 		(0x10)

#define TIMER0_IRQ				0
#define KBC_IRQ					1
#define RTC_IRQ 				8
#define MOUSE_IRQ				12

#endif
