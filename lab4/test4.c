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

	char a[3];

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

	//mouse_clean_buffer();

	while( i < cnt ) { /* You may want to use a different condition */
		/* Get a request message. */

		if ( r = driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					sys_inb(OUT_BUF, &key_register);
					mouse = (unsigned int) key_register;

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

							a[0] = byte1;
							a[1] = byte2;
							a[2] = byte3;
							i++;
							mouse_printf(a);
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
	int r;
	int ipc_status;
	message msg;
	unsigned int mouse;
	unsigned long key_register;
	unsigned int counter = 0;
	int temp_counter = 0;
	int i = 0;
	char bool1 = 0; //0 = true, nao 0 = true
	char bool2 = 0;
	//char bool3 = 0;
	char irq_set = BIT(mhook_id);
	char irq_set_timer = BIT(hook_id);

	char a[3];

	char byte1;
	char byte2;
	char byte3;

	if (mouse_subscribe_int() == -1)
	{
		printf("Fail to subscribe Mouse!\n \n");
		return 1;
	}

	if (timer_subscribe_int() == -1)
	{
		printf("Fail to subscribe Timer 0!\n \n");
		return 1;
	}

	mouse_int_handler(SET_STREAM);
	mouse_int_handler(ESDP);


	while(counter < idle_time ) { /* You may want to use a different condition */
		/* Get a request message. */

		if ( r = driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					temp_counter++;
					if ((temp_counter/60) == 1) //se for true quer dizer que passou um segundo
					{
						temp_counter = 0; //reset do temp_counter para voltar a contar os primeiros freq tiques
						counter++;
					}
				}
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					counter = 0;
					sys_inb(OUT_BUF, &key_register);
					mouse = (unsigned int) key_register;
					//tickdelay(micros_to_ticks(DELAY_US));
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
							a[0] = byte1;
							a[1] = byte2;
							a[2] = byte3;
							mouse_printf(a);
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

	timer_unsubscribe_int();
	mouse_int_handler(DISABLE_STREAM);
	mouse_int_handler(SET_STREAM);
	mouse_unsubscribe_int();
	return 0;
}

int test_config(void) {

	if (mouse_subscribe_int() == -1)
	{
		printf("Fail to subscribe Mouse!\n \n");
		return 1;
	}

	printf("\tMouse Configuration:\n");

	mouse_int_handler(STATUS_REQUEST);

	int conf_temp;
	conf_temp = mouse_cmd_receive();

	char conf;
	conf = (char) conf_temp;

	if (BIT(6) == (BIT(6) & conf))
	{
		printf("Remote Mode\n");
	}
	else printf("Stream Mode\n");

	if (BIT(5) == (BIT(5) & conf))
	{
		printf("Enabled\n");
	}
	else printf("Disabled\n");

	if (BIT(4) == (BIT(4) & conf))
	{
		printf("Scaling set to 1:1\n");
	}
	else printf("Scaling set to 2:1\n");

	if (BIT(2) == (BIT(2) & conf))
	{
		printf("Left Button Pressed\n");
	}
	else printf("Left Button Released\n");

	if (BIT(1) == (BIT(1) & conf))
	{
		printf("Middle Button Pressed\n");
	}
	else printf("Middle Button Released\n");

	if (BIT(0) == (BIT(0) & conf))
	{
		printf("Right Button Pressed\n");
	}
	else printf("Right Button Released\n");

	conf_temp = mouse_cmd_receive();
	conf = (char) conf_temp;

	if (BIT(3) == (BIT(3) & conf))
	{
		printf("Resolution Type: 8 units per mm\n");
	}
	else if (BIT(2) == (BIT(2) & conf))
	{
		printf("Resolution Type: 4 units per mm\n");
	}
	else if (BIT(1) == (BIT(1) & conf))
	{
		printf("Resolution Type: 2 units per mm\n");
	}
	else if (BIT(0) == (BIT(0) & conf))
	{
		printf("Resolution Type: 1 units per mm\n");
	}

	conf_temp = mouse_cmd_receive();
	conf = (char) conf_temp;

	printf("Sample Rate: %d Hz\n", conf);
}

int test_gesture(short length, unsigned short tolerance) {

	int r;
	int ipc_status;
	message msg;
	unsigned int mouse;
	char a[3];
	unsigned long key_register;
	char irq_set = BIT(mhook_id);
	char left_key;
	left_key = 0; //!!!!!!!!!
	int conf_temp;
	char conf;

	char bool1 = 0; //0 = true, nao 0 = true
	char bool2 = 0;
	//char bool3 = 0;

	char byte1;
	char byte2;
	char byte3;

	char deltax = 0;
	char deltay = 0;
	char olddeltax = 0;
	char olddeltay = 0;
	char firstpos = 0;

	char negative_length;

	if (length < 0)
	{
		negative_length = 1;
		length = -length;
	}
	else negative_length = 0;

	if (mouse_subscribe_int() == -1)
	{
		printf("Fail to subscribe Mouse!\n \n");
		return 1;
	}
	mouse_int_handler(SET_STREAM);
	mouse_int_handler(ESDP);

	while( 1 ) { /* You may want to use a different condition */
		/* Get a request message. */

		if ( r = driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					//***************************codigo da test_packet***************************
					//ler os packets
					sys_inb(OUT_BUF, &key_register);
					mouse = (unsigned int) key_register;

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
							//este e o ultimo byte
							//bool3 = 1;
							byte3 = mouse;
							bool1 = 0;
							bool2 = 0;

							a[0] = byte1;
							a[1] = byte2;
							a[2] = byte3;
							mouse_printf(a);
						}
					}
				}

			default:
				break; /* no other notifications expected: do nothing */
			}
		} else {

		}
	}
}
