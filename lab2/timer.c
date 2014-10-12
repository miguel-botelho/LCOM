#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include"i8254.h"

int hook_id = 0x00;
unsigned long global_counter = 0;

int timer_set_square(unsigned long timer, unsigned long freq) {

	unsigned long tempByte;
	unsigned char st;

	if (timer == 0)
		{
			timer_get_conf(timer, &st);
			st = 0x0F & st; //*st fica com os ultimos 4 bits
			tempByte = (TIMER_SEL0 | TIMER_LSB_MSB | st);
			sys_outb(TIMER_CTRL, tempByte);
			sys_outb(TIMER_0, TIMER_FREQ/freq);
			sys_outb(TIMER_0, (TIMER_FREQ/freq >> 8));
			return 0;
		}
		else if (timer == 1)
		{
			timer_get_conf(timer, &st);
			st = 0x0F & st; //*st fica com os ultimos 4 bits
			tempByte = (TIMER_SEL1 | TIMER_LSB_MSB | st);
			sys_outb(TIMER_CTRL, tempByte);
			sys_outb(TIMER_1, TIMER_FREQ/freq);
			sys_outb(TIMER_1, (TIMER_FREQ/freq >> 8));
			return 0;
		}
		else if (timer == 2)
		{
			timer_get_conf(timer, &st);
			st = 0x0F & st; //*st fica com os ultimos 4 bits
			tempByte = (TIMER_SEL2 | TIMER_LSB_MSB | st);
			sys_outb(TIMER_CTRL, tempByte);
			sys_outb(TIMER_2, TIMER_FREQ/freq);
			sys_outb(TIMER_2, (TIMER_FREQ/freq >> 8));
			return 0;
		}

	return -1;
}

int timer_subscribe_int(void ) {

	int hook_temp;
	hook_temp = hook_id;

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
	unsigned long temp;

	if (timer == 0)
	{
		tempByte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(0); //read-back command for timer 0
		sys_outb(TIMER_CTRL, tempByte);
		sys_inb(TIMER_0, &temp);
		*st = (unsigned char) temp;
		return 0;
	}
	else if (timer == 1)
	{
		tempByte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(1); //read-back command for timer 1
		sys_outb(TIMER_CTRL, tempByte);
		sys_inb(TIMER_1, &temp);
		*st = (unsigned char) temp;
		return 0;
	}
	else if (timer == 2)
	{
		tempByte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(2); //read-back command for timer 2
		sys_outb(TIMER_CTRL, tempByte);
		sys_inb(TIMER_2, &temp);
		*st = (unsigned char) temp;
		return 0;
	}

	return 1;
}

int timer_display_conf(unsigned char conf) {
	
	unsigned char temp;
	temp = conf;
	int number;

	/*
	 * the following operations where is in use 0xyy (where y is a number)
	 * is used to get the value of a single bit
	 */

	if (BIT(7) == (BIT(7) & temp))
		printf("Output pin: 1\n");
	else printf("Output pin: 0\n");

	if (BIT(6) == (BIT(6) & temp))
		printf("Null Count: 1\n");
	else printf("Null Count: 0\n");

	temp = conf;
	temp = temp & (BIT(5) | BIT(4));
	temp = temp >> 4;
	number = temp;
	if (number == 1)
	printf("Counter Initialization: LSB\n");
	else if (number == 2)
		printf("Counter Initialization: MSB\n");
	else printf("Counter Initialization: LSB followed by MSB\n");

	temp = conf;
	temp = temp & (BIT(3) | BIT(2) | BIT(1));
	temp = temp >> 1;
	number = temp; //to display (interpret) an int
	if (number == 2 || number == 6)
		printf("Programmed Mode: 2\n");
	else if (number == 3 || number == 7)
		printf("Programmed Mode: 3\n");
	else printf("Programmed Mode: %u \n", number);

	temp = conf;
	temp = temp & BIT(0);
	number = temp; //to display (interpret) an int
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
	
	int r;
	int ipc_status;
	int temp_counter = 0;
	unsigned long freq = 60;
	message msg;

	timer_test_square(freq);
	int irq_set = BIT(hook_id);

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
					if ((temp_counter/freq) == 1)
					{
						printf("Notification %lu \n", global_counter+1);
						temp_counter = 0;
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
	return 1;
}

int timer_test_config(unsigned long timer) {
	
	int errorCall1;
	int errorCall2;
	unsigned char timerConf;

	if ((timer >= 0) || (timer <= 2))
	{
		errorCall1 = timer_get_conf(timer, &timerConf);
		if (errorCall1 == 1)
			return 1;

		errorCall2 = timer_display_conf(timerConf);
		if (errorCall2 == 1)
			return 1;

		return 0;
	}

	return 1;
}
