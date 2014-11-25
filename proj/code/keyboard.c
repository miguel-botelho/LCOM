#include "keyboard.h"

int kbd_scan_c(int *apt)
{

	unsigned long key_register;

	//1 byte
	sys_inb(OUT_BUF, &key_register);
	*apt = (unsigned int) key_register;

	// this controller is slower than the cpu
	tickdelay(micros_to_ticks(DELAY_US));
	if (0xE0 == (0xE0 & *apt))
	{
		//2 bytes
		return 1;

	}
	return 0;
}

int kbd_test_scan(int *ret) {

	int msb;
	int key = 0;
	int return_byte;

	//the key is read
	return_byte = kbd_scan_c(&key);
	if (return_byte == 0)
	{
		if (0x0080 == (0x0080 & key))
		{
			if (key == CAPS_LOCK_UP || key == NUM_LOCK_UP || key == SCROLL_LOCK_UP)
				return kbd_test_leds(key);
			*ret = key;
			return BREAKCODE;
		}
		else
		{
			if (key == CAPS_LOCK_PRESS || key == NUM_LOCK_PRESS || key == SCROLL_LOCK_PRESS)
				return kbd_test_leds(key);
			*ret = key;
			return MAKECODE;
		}
	}
	else //a tecla tem 2 bytes, volta a chamar a funcao de read
	{
		msb = key;
		msb = msb << 8;

		//the key is read
		return_byte = kbd_scan_c(&key);

		key = key & 0x00FF;
		key = key + msb;
		if (0x0080 == (0x0080 & key))
		{
			*ret = key;
			return BREAKCODE;
		}
		else
		{
			*ret = key;
			return MAKECODE;
		}
	}
}

int kbd_test_leds(char led) {

	//shutdown all the lights
	unsigned long key = 0;

	switch (led)
	{
	case CAPS_LOCK_PRESS:
		led = 0x02;
		break;

	case NUM_LOCK_PRESS:
		led = 0x01;
		break;

	case SCROLL_LOCK_PRESS:
		led = 0x04;
		break;

	default: break;
	}

	kbd_int_handler(key);

	return -1;
}

void kbd_int_handler(unsigned long led){

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
			kbc_cmd_send(led);
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

int kbc_cmd_send(unsigned long cmd){

	unsigned long stat = 0;

	while(1)
	{
		sys_inb(STAT_REG, &stat); /*assuming it returns OK*/
		/*loop while 8042 input buffer is not empty*/
		if ((stat & IBF) == 0) //to check if input buffer is full
		{
			sys_outb(OUT_BUF, cmd);
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int kbc_cmd_receive(){

	unsigned long stat = 0;
	unsigned long data = 0;

	while(1)
	{
		sys_inb(STAT_REG, &stat); /*assuming it returns OK*/
		/*loop while 8042 input buffer is not empty*/
		if (stat & OBF) //to check if output buffer is full
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
