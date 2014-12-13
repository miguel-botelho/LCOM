#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "test6.h"

int rtc_hook_id = 2;

unsigned long rtc_subscribe_int(void) {

	int hook_temp = rtc_hook_id;

	if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &rtc_hook_id) != OK)
	{
		printf("SET POlicy\n");
		return -1;
	}

	if (sys_irqenable(&rtc_hook_id) != OK)
	{
		printf("irq enable\n");
		return -1;
	}

	return BIT(hook_temp);

}

int rtc_unsubscribe_int() {

	if (sys_irqrmpolicy(&rtc_hook_id) != OK)
		if (sys_irqdisable(&rtc_hook_id) != OK)
			return 0;
	return -1;
}

short read_rtc(long array) {

	long temp;
	short ret;

	sys_outb(RTC_ADDR_REG, array);
	sys_inb(RTC_DATA_REG, &temp);

	ret = (short) temp;
	return ret;
}

void write_rtc(long array, long temp) {

	short ret;

	sys_outb(RTC_ADDR_REG, array);
	sys_outb(RTC_DATA_REG, temp);
}


int rtc_test_conf(void) {
	/* To be completed */
}

int rtc_test_date(void) {

	int r;
	int ipc_status;
	message msg;
	long array;
	unsigned int i = 0;
	char irq_set = BIT(rtc_hook_id);

	if (-1 == rtc_subscribe_int())
	{
		printf("Fail to subscribe RTC!\n");
		return -1;
	}



	while (1)
	{
		if ((BIT(7) & read_rtc(10)) == BIT(7))
		{
			printf("Date: %x/%x/%x\n", read_rtc(7), read_rtc(8), read_rtc(9));
			printf("Hour: %x:%x:%x\n", read_rtc(4), read_rtc(2), read_rtc(0));

			int x = 0;
			for (x; x < 2000000; x++)
			{

			}

			switch(read_rtc(8))
			{
			case 0x01:
				printf("January\n");
				break;
			case 0x02:
				printf("February\n");
				break;
			case 0x03:
				printf("March\n");
				break;
			case 0x04:
				printf("April\n");
				break;
			case 0x05:
				printf("May\n");
				break;
			case 0x06:
				printf("June\n");
				break;
			case 0x07:
				printf("July\n");
				break;
			case 0x08:
				printf("August\n");
				break;
			case 0x09:
				printf("September\n");
				break;
			case 0x10:
				printf("October\n");
				break;
			case 0x11:
				printf("November\n");
				break;
			case 0x12:
				printf("December\n");
			default:
				break;
			}

			x = 0;
			for (x; x < 2000000; x++)
			{

			}

			switch(read_rtc(6))
			{
			case 0x01:
				printf("Sunday   \n");
				break;
			case 0x02:
				printf("Monday   \n");
				break;
			case 0x03:
				printf("Tuesday   \n");
				break;
			case 0x04:
				printf("Wednesday   \n");
				break;
			case 0x05:
				printf("Thursday   \n");
				break;
			case 0x06:
				printf("Friday   \n");
			case 0x07:
				printf("Saturday   \n");
				break;
			default:
				break;
			}



			rtc_unsubscribe_int();

			return 0;
		}
	}

	rtc_unsubscribe_int();

	return 0;
}

int rtc_test_int(/* to be defined in class */) { 

	int r;
	int ipc_status;
	message msg;
	char irq_set = BIT(rtc_hook_id);

	/*unsigned long regA = 0;
	do {
		rtc_subscribe_int();
		sys_outb(RTC_ADDR_REG, RTC_REG_A);
		sys_inb(RTC_DATA_REG, &regA);
		rtc_unsubscribe_int();
	} while ((BIT(7) == (BIT(7) & regA)));*/

	if (-1 == rtc_subscribe_int())
	{
		printf("Fail to subscribe RTC!\n");
		return -1;
	}

	read_rtc(12);
	write_rtc(11, 0x16);

	long i = 0;

	while (i < 5) // enquanto não passar o tempo que o utilizador quer
	{

		printf("\n\n\t%d \n", i);
		i = i + 1;
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					printf("Date: %x/%x/%x\n", read_rtc(7), read_rtc(8), read_rtc(9));
					printf("Hour: %x:%x:%x\n", read_rtc(4), read_rtc(2), read_rtc(0));

					int x = 0;
					for (x; x < 2000000; x++)
					{

					}

					switch(read_rtc(8))
					{
					case 0x01:
						printf("January\n");
						break;
					case 0x02:
						printf("February\n");
						break;
					case 0x03:
						printf("March\n");
						break;
					case 0x04:
						printf("April\n");
						break;
					case 0x05:
						printf("May\n");
						break;
					case 0x06:
						printf("June\n");
						break;
					case 0x07:
						printf("July\n");
						break;
					case 0x08:
						printf("August\n");
						break;
					case 0x09:
						printf("September\n");
						break;
					case 0x10:
						printf("October\n");
						break;
					case 0x11:
						printf("November\n");
						break;
					case 0x12:
						printf("December\n");
					default:
						break;
					}

					x = 0;
					for (x; x < 2000000; x++)
					{

					}

					switch(read_rtc(6))
					{
					case 0x01:
						printf("Sunday   \n");
						break;
					case 0x02:
						printf("Monday   \n");
						break;
					case 0x03:
						printf("Tuesday   \n");
						break;
					case 0x04:
						printf("Wednesday   \n");
						break;
					case 0x05:
						printf("Thursday   \n");
						break;
					case 0x06:
						printf("Friday   \n");
					case 0x07:
						printf("Saturday   \n");
						break;
					default:
						break;
					}
				}
			}

			/* To be completed */
		}
		read_rtc(12);
	}
	rtc_unsubscribe_int();

	return 0;
}

