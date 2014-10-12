#include <minix/syslib.h>
#include <minix/drivers.h>
#include"i8254.h"

int timer_set_square(unsigned long timer, unsigned long freq) {

	unsigned long tempByte;

	if (timer == TIMER_0)
		{
			tempByte = (TIMER_SEL0 | TIMER_LSB_MSB | TIMER_SQR_WAVE);
			sys_outb(TIMER_CTRL, tempByte);
			sys_outb(TIMER_0, TIMER_FREQ/freq);
			sys_outb(TIMER_0, (TIMER_FREQ/freq >> 8));
			return 0;
		}
		else if (timer == TIMER_1)
		{
			tempByte = (TIMER_SEL1 | TIMER_LSB_MSB | TIMER_SQR_WAVE);
			sys_outb(TIMER_CTRL, tempByte);
			sys_outb(TIMER_1, TIMER_FREQ/freq);
			return 0;
		}
		else if (timer == TIMER_2)
		{
			tempByte = (TIMER_SEL2 | TIMER_LSB_MSB | TIMER_SQR_WAVE);
			sys_outb(TIMER_CTRL, tempByte);
			sys_outb(TIMER_2, TIMER_FREQ/freq);
			return 0;
		}

	return 1;
}

int timer_subscribe_int(void ) {

	return 1;
}

int timer_unsubscribe_int() {

	return 1;
}

void timer_int_handler() {

}

int timer_get_conf(unsigned long timer, unsigned char *st) {
	
	unsigned long tempByte;
	unsigned long temp;

	if (timer == TIMER_0)
	{
		tempByte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(0); //read-back command for timer 0
		sys_outb(TIMER_CTRL, tempByte);
		sys_inb(TIMER_0, &temp);
		*st = (unsigned char) temp;
		return 0;
	}
	else if (timer == TIMER_1)
	{
		tempByte = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(1); //read-back command for timer 1
		sys_outb(TIMER_CTRL, tempByte);
		sys_inb(TIMER_1, &temp);
		*st = (unsigned char) temp;
		return 0;
	}
	else if (timer == TIMER_2)
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
	
	if (timer_set_square(TIMER_0, freq) == 0)
		return 0;

	return 1;
}

int timer_test_int(unsigned long time) {
	
	return 1;
}

int timer_test_config(unsigned long timer) {
	
	int errorCall1;
	int errorCall2;
	unsigned char timerConf;

	if ((timer >= TIMER_0) || (timer <= TIMER_CTRL))
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
