#include"test3.h"

int khook_id = 0x01; //hook_id tem de estar entre [0..30] //kbd
int hook_id = 0x00; //hook_id tem de estar entre [0..30] //timer

unsigned long global_counter = 0;

#define KBC_IRQ 0x01

int kbd_unsubscribe_int() {

	if (OK == sys_irqdisable(&khook_id))
		if (OK == sys_irqrmpolicy(&khook_id))
			return 0;
	return -1;
}

int kbd_subscribe_int(void ) {

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

int kbd_test_scan(unsigned short ass) {
	int r;
	int key = 0;
	int return_byte;
	int ipc_status;
	message msg;
	char irq_set = BIT(khook_id);

	if (-1 == kbd_subscribe_int())
	{
		printf("Fail to subscribe Keyboard!\n\n");
		return 1;
	}

	while(0x81 != key) { /* When ESC key is pressed */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					if (return_byte != 1) //if return_byte == 1 then the key has 2 bytes
					{
						if (ass == 0)
							return_byte = kbd_scan_c(&key);
						else key = kbd_scan_ass();
						if (0x0080 == (0x0080 & key))
						{
							printf("Breakcode: 0x%x\n", key);
						}
						else
						{
							//if (key == 0)
							{
								printf("Makecode: 0x%x\n", key);
							}
						}
					}
					else
						{
							return_byte = 0;
							kbd_scan_c(&key);
						}
					/* process it */
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	kbd_unsubscribe_int();
	return 0;
}

int kbd_test_leds(unsigned short n, unsigned short *leds) {
	unsigned short i = 0;
	int cmd_receive = 0;
	int cmd_receive2 = 0;
	unsigned long elem;
	int l0, l1, l2;
	l0 = 0;
	l1 = 0;
	l2 = 0;

	if (-1 == kbd_subscribe_int())
		{
			printf("Fail to subscribe Keyboard!\n\n");
			return 1;
		}


	////////////////////////////////////////////////////////////////////////////////////////////////
	int r; //vai ter o codigo do erro driver_receive(ANY, &msg, &ipc_status)
	int ipc_status;
	int temp_counter = 0; //contador de tiques
	unsigned long freq = 60; //frequencia normal
	message msg;

	timer_test_square(freq); //para funcionar a frequencia normal
	char irq_set = BIT(hook_id);

	if (-1 == timer_subscribe_int())
	{
		printf("Fail to subscribe Timer 0!\n\n");
		return 1;
	}
	for (i; i < n; i++)
	{
		global_counter = 0;
		while( global_counter < 1 ) { /* You may want to use a different condition */
			/* Get a request message. */
			if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
				printf("driver_receive failed with: %d", r);
				continue;
			}
			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
						temp_counter++;
						if ((temp_counter/freq) == 1) //se for true quer dizer que passou um segundo
						{
							//elem = leds[i];
							if (leds[i] == 0x0)
							{
								if (l0 == 0)
									l0 = 0x1;
								else l0 = 0;
							}
							else if(leds[i] == 0x1)
							{
								if (l1 == 0)
									l1 = 0x2;
								else l1 = 0;
							}
							else if (l2 == 0)
								l2 = 0x4;
							else l2 = 0;

							elem = l0 + l1 + l2;

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
							timer_test_square(60);
							temp_counter = 0; //reset do temp_counter para voltar a contar os primeiros freq tiques
							timer_int_handler();
						}
					}
					/* process it */
					break;
				default:
					break; /* no other notifications expected: do nothing */
				}
			} else { /* received a standard message, not a notification */
				/* no standard messages expected: do nothing */
			}
		}
	}
	timer_unsubscribe_int();

	kbd_unsubscribe_int();

	////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}

int kbd_test_timed_scan(unsigned short n) {
	/* To be completed */
}

int kbd_scan_c(int *apt) {

	unsigned long key_register;

	//1 byte
	sys_inb(0x60, &key_register);
	*apt = (unsigned int) key_register;
	if (0xE0 == (0xE0 & *apt))
	{
		//2 bytes
		*apt = *apt << 8;
		tickdelay(micros_to_ticks(DELAY_US));
		sys_inb(0x60, &key_register);
		*apt = *apt + (unsigned int) key_register;

		tickdelay(micros_to_ticks(DELAY_US));
		return 1;

	}
	return 0;
}

int kbd_scan_ass()
{
	return 0;
}

int kbc_cmd_send(unsigned long cmd)
{
	unsigned long stat = 0;
	unsigned long IBF = 0x0002; //to check if input buffer is full

	while(1)
	{
		sys_inb(STAT_REG, &stat); /*assuming it returns OK*/
		/*loop while 8042 input buffer is not empty*/
		if ((stat & IBF) == 0)
		{
			sys_outb(0x60, cmd);
			//sys_outb(KBC_CMD_REG, cmd); /*no args command*/
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int kbc_cmd_receive()
{
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

int timer_test_square(unsigned long freq) {

	if (timer_set_square(0, freq) == 0)
		return 0;

	return 1;
}

int timer_subscribe_int(void ) {

	//para nao perder o valor original de hook_id (vai ser preciso para depois reconhecer a notificacao)
	int hook_temp = hook_id;

	if (OK == sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id))
		if (OK == sys_irqenable(&hook_id))
			return BIT(hook_temp);
	return -1;
}

int timer_unsubscribe_int() {

	if (OK == sys_irqdisable(&hook_id))
		if (OK == sys_irqrmpolicy(&hook_id))
			return 0;
	return -1;
}

void timer_int_handler() {

	global_counter++;

}

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
