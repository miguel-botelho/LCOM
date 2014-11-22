#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <minix/sysutil.h>
#include <minix/com.h>

#include "vbe.h"
#include "read_xpm.h"
#include "video_gr.h"
#include "test5.h"
#include "lmlib.h"
#include "pixmap.h"
#include <stdint.h>

int hook_id = 0x00;
int khook_id = 0x01;

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {

	struct reg86u r;

	mmap_t map;

	if (lm_alloc(sizeof(vbe_mode_info_t), &map) == NULL) //alloc memory needed
	{
		printf("Bad allocation of memory!\n");
		return 1;
	}
	r.u.w.ax = VBE_GET_MODE; /* VBE get mode info */
	r.u.w.es = PB2BASE(map.phys); /* set a segment base */
	r.u.w.di = PB2OFF(map.phys); /* set the offset accordingly */
	r.u.w.cx = mode; /* the mode required*/
	r.u.b.intno = INTERRUPT_VBE; /* interrupt VBE */
	if( sys_int86(&r) != OK ) { /* call BIOS */

		printf("Error. Video Mode Wrong!\n");
		lm_free(&map); //free memory
		return 1;
	}

	if (r.u.b.ah == 0x01 )
	{
		printf("Function call mapping failed!\n");
		lm_free(&map);
		return 1;
	}
	else if (r.u.b.ah == 0x02)
	{
		printf("Function is not supported in current HW configuration!\n");
		lm_free(&map);
		return 1;
	}
	else if (r.u.b.ah == 0x03)
	{
		printf("Function is invalid in current video mode!\n");
		lm_free(&map);
		return 1;
	}

	*vmi_p = *(vbe_mode_info_t*) map.virtual; //virtual memory
	lm_free(&map); //free memory
	return 0;
}

int get_vbe_info(vbe_info_block *vib_p){

	struct reg86u r;

	mmap_t map;

	if (lm_alloc(sizeof(vbe_info_block), &map) == NULL) //alloc memory needed
	{
		printf("Bad allocation of memory!\n");
		return 1;
	}

	r.u.w.ax = VBE_CONTROL_INFO; /* VBE control info */
	r.u.w.di = PB2BASE(map.phys); /* set a segment base */
	r.u.w.es = PB2OFF(map.phys); /* set the offset accordingly */
	r.u.w.cx = GRAPHIC_MODE; /* the mode required*/
	r.u.b.intno = INTERRUPT_VBE; /* interrupt VBE */

	if( sys_int86(&r) != OK ) { /* call BIOS */

		printf("Error. Video Mode Wrong!\n");
		lm_free(&map); //free memory
		return 1;
	}

	if (r.u.b.ah == 0x01 )
	{
		printf("Function call mapping failed!\n");
		lm_free(&map);
		return 1;
	}
	else if (r.u.b.ah == 0x02)
	{
		printf("Function is not supported in current HW configuration!\n");
		lm_free(&map);
		return 1;
	}
	else if (r.u.b.ah == 0x03)
	{
		printf("Function is invalid in current video mode!\n");
		lm_free(&map);
		return 1;
	}

	*vib_p = *(vbe_info_block*) map.virtual; //virtual memory
	lm_free(&map); //free memory
	return 0;
}


int vbe_set_mode(unsigned short function, unsigned short mode) {


	struct reg86u r;


	r.u.w.ax = function; // VBE call, function 02 -- set VBE mode
	r.u.w.bx = LINEAR_MODEL_BIT | mode; // set bit 14: linear framebuffer
	r.u.b.intno = INTERRUPT_VBE; // interrupt VBE (0x10)


	if( sys_int86(&r) != OK ) {
		printf("set_vbe_mode: sys_int86() failed \n");
		return 1;
	}
	if (r.u.b.ah == 0x01 )
	{
		printf("Function call failed!\n");
		return 1;
	}
	else if (r.u.b.ah == 0x02)
	{
		printf("Function is not supported in current HW configuration!\n");
		return 1;
	}
	else if (r.u.b.ah == 0x03)
	{
		printf("Function is invalid in current video mode!\n");
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

int xpm_cre(int *altura, int *largura, unsigned short x, unsigned short y, char* xpm[]) {

	int i = 0;
	int j = 0;

	char *video_copy = getVideoMem();
	unsigned h_res = getHRes();

	video_copy = video_copy + h_res * y + x;

	char* pixel;
	if (( pixel= read_xpm(xpm, largura, altura)) == NULL)
	{
		return 1;
	}

	else
	{
		for (i; i < *altura; i++)
		{
			for (j; j < *largura; j++)
			{
				*video_copy = *pixel;
				video_copy++;
				pixel++;
			}
			video_copy = video_copy + h_res - *largura;
			j = 0;
		}
	}
	return 0;
}

int xpm_del(int *altura, int *largura, unsigned short x, unsigned short y) {

	int i = 0;
	int j = 0;

	char *video_copy = getVideoMem();
	unsigned h_res = getHRes();

	video_copy = video_copy + h_res * y + x;

	for (i; i < *altura; i++)
	{
		for (j; j < *largura; j++)
		{
			*video_copy = 0;
			video_copy++;
		}
		video_copy = video_copy + h_res - *largura;
		j = 0;
	}
	return 0;
}

