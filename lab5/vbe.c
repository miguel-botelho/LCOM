#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <minix/sysutil.h>
#include <minix/com.h>

#include "vbe.h"
#include "video_gr.h"
#include "test5.h"
#include "lmlib.h"
#include <stdint.h>

int hook_id = 0x00;
int khook_id = 0x01;

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {

	/* To be completed */

	phys_bytes buf; /* to store the VBE Mode Info desired */
	struct reg86u r;
	r.u.w.ax = VBE_GET_MODE; /* VBE get mode info */
	/* translate the buffer linear address to a far pointer */
	r.u.w.es = PB2BASE(buf); /* set a segment base */
	r.u.w.di = PB2OFF(buf); /* set the offset accordingly */
	r.u.w.cx = mode;
	r.u.b.intno = INTERRUPT_VBE;
	if( sys_int86(&r) != OK ) { /* call BIOS */


	}

	return 1;
}


int vbe_set_mode(unsigned short function, unsigned short mode) {

	struct reg86u r;
	r.u.w.ax = function; // VBE call, function 02 -- set VBE mode
	r.u.w.bx = 1<<14| mode; // set bit 14: linear framebuffer
	r.u.b.intno = INTERRUPT_VBE;
	if( sys_int86(&r) != OK ) {
		printf("set_vbe_mode: sys_int86() failed \n");
		return 1;
	}
	return 0;
}


int timer_subscribe_int(void ){

	//para nao perder o valor original de hook_id (vai ser preciso para depois reconhecer a notificacao)
	int hook_temp = hook_id;

	if (OK == sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id))
		if (OK == sys_irqenable(&hook_id))
			return BIT(hook_temp);
	return -1;
}

int timer_unsubscribe_int(){
	if (OK == sys_irqdisable(&hook_id))
		if (OK == sys_irqrmpolicy(&hook_id))
			return 0;
	return -1;
}

int kbd_unsubscribe_int(){

	if (OK == sys_irqdisable(&khook_id))
			if (OK == sys_irqrmpolicy(&khook_id))
				return 0;
		return -1;
}

int kbd_subscribe_int(void ){

	//para nao perder o valor original de khook_id (vai ser preciso para depois reconhecer a notificacao)
		int hook_temp = khook_id;

		if (OK == sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &khook_id))
		{
			if (OK == sys_irqenable(&khook_id))
			{
				return BIT(hook_temp);
			}
		}
		return -1;
}

int kbc_cmd_send(unsigned long cmd){

	unsigned long stat = 0;
	unsigned long IBF = 0x0002; //to check if input buffer is full

	while(1)
	{
		sys_inb(STAT_REG, &stat); /*assuming it returns OK*/
		/*loop while 8042 input buffer is not empty*/
		if ((stat & IBF) == 0)
		{
			sys_outb(OUT_BUF, cmd);
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int kbc_cmd_receive(){

	unsigned long stat = 0;
	unsigned long OBF = 0x0001; //to check if output buffer is full
	unsigned long data = 0;

	while(1)
	{
		sys_inb(STAT_REG, &stat); /*assuming it returns OK*/
		/*loop while 8042 input buffer is not empty*/
		if (stat & OBF)
		{
			sys_inb(OUT_BUF, &data); /*assuming it returns OK*/

			if ((stat & (PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return -1;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int kbd_scan_c(int *apt){

	unsigned long key_register;

	//1 byte
	sys_inb(OUT_BUF, &key_register);
	*apt = (unsigned int) key_register;
	tickdelay(micros_to_ticks(DELAY_US));
	if (0xE0 == (0xE0 & *apt))
	{
		//2 bytes
		return 1;

	}
	return 0;
}
