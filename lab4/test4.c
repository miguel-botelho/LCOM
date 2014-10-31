#include"test4.h"

int test_packet(unsigned short cnt){

	int r;
	int ipc_status;
	message msg;
	unsigned int mouse;
	unsigned long key_register;
	int i = 0;
	char bool1 = 0; //0 = true, nao 0 = true
	char bool2 = 0;
	//char bool3 = 0;
	char irq_set = BIT(mhook_id);

	char byte1;
	char byte2;
	char byte3;

	if (mouse_subscribe_int() == -1)
	{
		printf("Fail to subscribe Mouse!\n \n");
		return 1;
	}
	mouse_int_handler(SET_STREAM);
	mouse_int_handler(ESDP);

	while( i < cnt ) { /* You may want to use a different condition */
		/* Get a request message. */

		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					sys_inb(OUT_BUF, &key_register);
					mouse = (unsigned int) key_register;
					tickdelay(micros_to_ticks(DELAY_US));

					printf("mouse: %x", mouse);

					if (bool1 == 0)
					{
						if (0x08 == (0x08 & mouse))
						{
							bool1 = 1;
							byte1 = mouse;
						}
						else continue;

					}
					else
					{
						if (bool2 == 0)
						{

							bool2 = 1;
							byte2 = mouse;
						}
						else
						{

							//bool3 = 1;
							byte3 = mouse;
							bool1 = 0;
							bool2 = 0;
							mouse_printf(byte1, byte2, byte3);
						}
					}

				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else {

		}
	}

	mouse_int_handler(DISABLE_STREAM);
	mouse_int_handler(SET_STREAM);
	mouse_unsubscribe_int();
}



int test_async(unsigned short idle_time) {
	/* To be completed ... */
}

int test_config(void) {
	/* To be completed ... */
}

int test_gesture(short length, unsigned short tolerance) {
	/* To be completed ... */
}
