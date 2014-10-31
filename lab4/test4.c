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
	printf("subscribe!\n");
	mouse_int_handler(SET_STREAM);
	mouse_int_handler(ESDP);
	printf("handler!\n");


	while( i < cnt ) { /* You may want to use a different condition */
		/* Get a request message. */
		printf("while\n");

		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					printf("INTERRUPCAO! \n");
					sys_inb(OUT_BUF, &key_register);
					mouse = (unsigned int) key_register;
					tickdelay(micros_to_ticks(DELAY_US));
					if (bool1 == 0)
					{

						printf("mouse: %x\n", mouse);
						tickdelay(micros_to_ticks(DELAY_US));

						sys_inb(STAT_REG, &key_register);
						mouse = (unsigned int) key_register;
						printf("stat: %x\n", mouse);
						tickdelay(micros_to_ticks(DELAY_US));

						sys_inb(OUT_BUF, &key_register);
						mouse = (unsigned int) key_register;
						printf("mouse2: %x\n", mouse);

						continue;


						if (0x08 == (0x08 & mouse))
						{
							printf("mouse: %x\n", mouse);
							bool1 = 1;
							byte1 = mouse;
						}
						else continue;

					}
					else
					{
						printf("mouse2: %x\n", mouse);
						if (bool2 == 0)
						{

							bool2 = 1;
							byte2 = mouse;
						}
						else
						{
							printf("mouse3: %x\n", mouse);

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
