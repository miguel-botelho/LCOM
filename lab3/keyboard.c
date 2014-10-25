#include"keyboard.h"

int khook_id = 0x01;
int hook_id = 0x00;
unsigned long global_counter = 0;
unsigned long elem;


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

int kbd_scan_ass(int *apt){

/*
	unsigned long key_register;

		//1 byte

		IN 0x64, eax
		mov eax, key_register
		sys_inb(OUT_BUF, &key_register);
		*apt = (unsigned int) key_register;
		tickdelay(micros_to_ticks(DELAY_US));
		if (0xE0 == (0xE0 & *apt))
		{
			//2 bytes
			return 1;

		}
		return 0;

*/ //ESCREVER TUDO EM ASSEMBLY
	return 0;
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
			//sys_outb(KBC_CMD_REG, cmd); /*no args command*/
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

int timer_test_square(unsigned long freq){

	if (timer_set_square(0, freq) == 0)
		return 0;

	return 1;
}

int timer_set_square(unsigned long timer, unsigned long freq){

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

int timer_subscribe_int(void ){

	//para nao perder o valor original de hook_id (vai ser preciso para depois reconhecer a notificacao)
	int hook_temp = hook_id;

	if (OK == sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id))
		if (OK == sys_irqenable(&hook_id))
			return BIT(hook_temp);
	return -1;
}

void timer_int_handler(){

	global_counter++;
}

int timer_get_conf(unsigned long timer, unsigned char *st){

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

void kbd_int_handler(){

	int cmd_receive = 0;
	int cmd_receive2 = 0;

	while (1)
	{
		kbc_cmd_send(LEDS);
		cmd_receive = kbc_cmd_receive();

		if (cmd_receive == RESEND || cmd_receive == ERROR)
		{
			continue;
		}


		while (1)
		{
			kbc_cmd_send(elem);
			cmd_receive2 = kbc_cmd_receive();

			if (cmd_receive2 == RESEND)
			{
				continue;
			}
			break;
		}
		if (cmd_receive2 == ERROR)
		{
			continue;
		}
		break;
	}

}

int timer_unsubscribe_int(){

	if (OK == sys_irqdisable(&hook_id))
			if (OK == sys_irqrmpolicy(&hook_id))
				return 0;
		return -1;
}
