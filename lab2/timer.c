#include <minix/syslib.h>
#include <minix/drivers.h>

int timer_set_square(unsigned long timer, unsigned long freq) {

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
	
	unsigned char *tempByte;

	if (timer == 0)
	{
		(*tempByte) = 0xC2;
		sys_outb(TIMER_CTRL, *tempByte);
		sys_inb(TIMER_CTRL, st);
		return 0;
	}
	else if (timer == 1)
	{
		(*tempByte) = 0xC4;
		sys_outb(TIMER_CTRL, *tempByte);
		sys_inb(TIMER_CTRL, st);
		return 0;
	}
	else if (timer == 2)
	{
		(*tempByte) = 0xC8;
		sys_outb(TIMER_CTRL, *tempByte);
		sys_inb(TIMER_CTRL, st);
		return 0;
	}

	return 1;
}

int timer_display_conf(unsigned char conf) {
	
	unsigned char temp;
	temp = conf;
	int number;

	if (0x80 == (0x80 & temp))
		printf("Output pin: 1\n");
	else printf("Output pin: 0\n");

	temp = conf;
	if (0x40 == (0x40 & temp))
		printf("Null Count: 1\n");
	else printf("Null Count: 0\n");

	temp = conf;
	temp = temp & 0x30;
	if (temp == 0x30)
		printf("Counter Initialization: 3\n");
	else if (temp == 0x20)
		printf("Counter Initialization: 2\n");
	else if (temp == 0x10)
		printf("Counter Initialization: 1\n");
	else printf("Counter Initialization: 0\n");

	temp = conf;
	temp = temp & 0x0E;
	temp = temp >> 1;
	number = temp;

	printf("Programmed Mode: %u \n", number);

	temp = conf;
	temp = temp & 0x01;
	number = temp;

	printf("BCD: %u \n \n", number);

	return 0;
}

int timer_test_square(unsigned long freq) {
	
	return 1;
}

int timer_test_int(unsigned long time) {
	
	return 1;
}

int timer_test_config(unsigned long timer) {
	
	int errorCall1;
	int errorCall2;

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
