#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include"i8254.h"

int hook_id = 0x00; //hook_id tem de estar entre [0..7]
unsigned long global_counter = 0;

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

int timer_display_conf(unsigned char conf) {
	
	int number; //esta variavel vai ser usada para fazer printf de um decimal

	if (BIT(7) == (BIT(7) & conf)) //para ver se o BIT(7) esta a 1
		printf("Output pin: 1\n");
	else printf("Output pin: 0\n");

	if (BIT(6) == (BIT(6) & conf)) //para ver se o BIT(6) esta a 1
		printf("Null Count: 1\n");
	else printf("Null Count: 0\n");

	number = (conf & (BIT(5) | BIT(4))) >> 4; //desloca os BITS 5 e 4 para as posicoes 0 e 1
	if (number == 1)
	printf("Counter Initialization: LSB\n");
	else if (number == 2)
		printf("Counter Initialization: MSB\n");
	else printf("Counter Initialization: LSB followed by MSB\n");

	number = (conf & (BIT(3) | BIT(2) | BIT(1))) >> 1; //desloca os BITS 3, 2 e 1 para as posicoes 0, 1 e 2
	if (number == 2 || number == 6)
		printf("Programmed Mode: 2\n");
	else if (number == 3 || number == 7)
		printf("Programmed Mode: 3\n");
	else printf("Programmed Mode: %u \n", number);

	number = conf & BIT(0); //vai buscar o BIT 0
	if (number == 1)
	printf("Counting Mode: BCD \n \n");
	else printf("Counting Mode: Binary \n \n");

	return 0;
}

int timer_test_square(unsigned long freq) {
	
	if (timer_set_square(0, freq) == 0)
		return 0;

	return 1;
}

int timer_test_int(unsigned long time) {
	
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

	while( global_counter < time ) { /* You may want to use a different condition */
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
						printf("Notification %lu \n", global_counter+1);
						temp_counter = 0; //reset do temp_counter para voltar a contar os primeiros freq tiques
						timer_int_handler();
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

	timer_unsubscribe_int();
	printf("Press the Enter key to exit\n");
	return 1;
}

int timer_test_config(unsigned long timer) {
	
	int errorCall;
	unsigned char timerConf;

	if ((timer >= 0) || (timer <= 2))
	{
		errorCall = timer_get_conf(timer, &timerConf);
		if (errorCall == 1)
			return 1;

		errorCall = timer_display_conf(timerConf);
		if (errorCall == 1)
			return 1;

		return 0;
	}

	return 1;
}
