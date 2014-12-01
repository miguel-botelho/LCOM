#include "test6.h"

int rtc_hook_id = 0x02;

unsigned long rtc_subscribe_int(void) {

	int hook_temp = rtc_hook_id;

	if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &RTC_HOOK) == OK)
		if (sys_irqenable(&RTC_HOOK) == OK)
			return BIT(hook_temp);
	return -1;

}

int RTC_unsubscribe_int() {

	if (sys_irqrmpolicy(&RTC_HOOK) != OK)
		if (sys_irqdisable(&RTC_HOOK) != OK)
			return 0;
	return -1;
}

short read_rtc(long array) {

	long temp;
	short ret;

	sys_outb(RTC_ADDR_REG, array);
	sys_inb(RTC_DATA_REG, temp);

	ret = (short) temp;
	return ret;
}



int rtc_test_conf(void) {
	/* To be completed */
}

int rtc_test_date(void) {

	int r;
	int ipc_status;
	message msg;
	long array;

	if (-1 == rtc_subscribe_int())
	{
		printf("Fail to subscribe RTC!\n");
		return -1;
	}

	while (1) // enquanto não passar o tempo que o utilizador quer
	{
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					array = 4;
					printf("%d",read_rtc(array));
					return 0;

				}

			}

			/* To be completed */
		}
	}

}

int rtc_test_int(/* to be defined in class */) { 
	/* To be completed */
}

