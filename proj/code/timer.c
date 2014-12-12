#include "timer.h"

int timer_get_conf(unsigned long timer, unsigned char *st) {

	unsigned long tempByte;

	if (timer == 0)
	{
		tempByte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(0); //read-back command for timer 0, ativa o status e desativa o count
		sys_outb(TIMER_CTRL, tempByte);
		sys_inb(TIMER_0, &tempByte);
		*st = (unsigned char) tempByte; //trunca o valor de tempByte para char (8 bits)
		return 0;
	}
	else if (timer == 1)
	{
		tempByte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(1); //read-back command for timer 1, ativa o status e desativa o count
		sys_outb(TIMER_CTRL, tempByte);
		sys_inb(TIMER_1, &tempByte);
		*st = (unsigned char) tempByte; //trunca o valor de tempByte para char (8 bits)
		return 0;
	}
	else if (timer == 2)
	{
		tempByte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(2); //read-back command for timer 2, ativa o status e desativa o count
		sys_outb(TIMER_CTRL, tempByte);
		sys_inb(TIMER_2, &tempByte);
		*st = (unsigned char) tempByte; //trunca o valor de tempByte para char (8 bits)
		return 0;
	}

	return 1;
}

int timer_set_square(unsigned long timer, unsigned long freq) {

	unsigned long tempByte;
	unsigned char st;

	if (timer == 0)
	{
		timer_get_conf(timer, &st);
		st = 0x0F & st; //st fica com os ultimos 4 bits
		tempByte = (TIMER_SEL0 | TIMER_LSB_MSB | st); // seleciona o TIMER_0 e ativa LSB followed by MSB
		sys_outb(TIMER_CTRL, tempByte);
		sys_outb(TIMER_0, TIMER_FREQ/freq); //manda LSB
		sys_outb(TIMER_0, (TIMER_FREQ/freq >> 8)); //manda MSB
		return 0;
	}
	else if (timer == 1)
	{
		timer_get_conf(timer, &st);
		st = 0x0F & st; //st fica com os ultimos 4 bits
		tempByte = (TIMER_SEL1 | TIMER_LSB_MSB | st); // seleciona o TIMER_1 e ativa LSB followed by MSB
		sys_outb(TIMER_CTRL, tempByte);
		sys_outb(TIMER_1, TIMER_FREQ/freq); //manda LSB
		sys_outb(TIMER_1, (TIMER_FREQ/freq >> 8)); // manda MSB
		return 0;
	}
	else if (timer == 2)
	{
		timer_get_conf(timer, &st);
		st = 0x0F & st; //st fica com os ultimos 4 bits
		tempByte = (TIMER_SEL2 | TIMER_LSB_MSB | st); // seleciona o TIMER_2 e ativa LSB followed by MSB
		sys_outb(TIMER_CTRL, tempByte);
		sys_outb(TIMER_2, TIMER_FREQ/freq); //manda LSB
		sys_outb(TIMER_2, (TIMER_FREQ/freq >> 8)); //manda MSB
		return 0;
	}

	return -1;
}
