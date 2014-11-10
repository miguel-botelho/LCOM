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

	mouse_int_handler(SET_STREAM); //define o rato como stream mode
	mouse_int_handler(ESDP); //ativa o envio dos dados por parte do rato

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

					//le o packet
					if (bool1 == 0)
					{
						if (BIT(3) == (BIT(3) & mouse))
						{
							bool1 = 1; //o primeiro byte
							byte1 = mouse;
						}
						else continue;

					}
					else
					{
						if (bool2 == 0)
						{

							bool2 = 1; //o segundo byte
							byte2 = mouse;
						}
						else
						{

							//este e o 3 byte
							//estao todos lidos
							//bool3 = 1;
							byte3 = mouse;
							bool1 = 0;
							bool2 = 0;

							//os bytes passam para um array
							a[0] = byte1;
							a[1] = byte2;
							a[2] = byte3;
							i++; //contador de packets
							mouse_printf(a); //imprime o packet
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

	//estas duas opearacoes sao feitas para assegurar o normal funcionamento do rato quando acabar a funcao
	mouse_int_handler(DISABLE_STREAM); //desativa a stream
	mouse_int_handler(SET_STREAM); //volta a ativar a stream, isto foi feito para desativar o envio dos pacotes
	mouse_unsubscribe_int();
}



int test_async(unsigned short idle_time) {
	int r;
	int ipc_status;
	message msg;
	unsigned int mouse;
	unsigned long key_register;
	unsigned int counter = 0; //contador de segundos
	int temp_counter = 0; //contador de ticks
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


	while(counter < idle_time ) { //so para quando nao enviar packets durante idle_time segundos

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
					counter = 0; //faz reset ao contador
					sys_inb(OUT_BUF, &key_register);
					mouse = (unsigned int) key_register;
					//tickdelay(micros_to_ticks(DELAY_US));
					//funcionamento semelhante a funcao test_packets
					if (bool1 == 0)
					{
						if (BIT(3) == (BIT(3) & mouse))
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
	char leftkey;

	char bool1 = 0; //0 = true, nao 0 = true
	char bool2 = 0;
	//char bool3 = 0;

	char byte1;
	char byte2;
	char byte3;

	short tamanho_h; //contador horizontal
	short tamanho_v; //contador vertical
	leftkey = 0;
	char estado = 'i';
	//'i' = inicial
	//'d' = desenho
	//'f' = final

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
						if (BIT(3) == (BIT(3) & mouse))
						{
							bool1 = 1;
							byte1 = (char)mouse;
						}
						else continue;

					}
					else
					{
						if (bool2 == 0)
						{

							bool2 = 1;
							byte2 = (char)mouse;
						}
						else
						{
							//este e o ultimo byte
							//bool3 = 1;
							byte3 = (char)mouse;
							bool1 = 0;
							bool2 = 0;

							a[0] = byte1;
							a[1] = byte2;
							a[2] = byte3;
							mouse_printf(a);
							//***************************acaba aqui o codigo da test_packet***************************
							//botao esquerdo
							leftkey = a[0] & BIT(0);
							//desenho na horizontal
							if (BIT(4) == (BIT(4) & a[0])) //-x
							{
								tamanho_h = tamanho_h - neg8bits(a[1]);
							} else
							{
								tamanho_h = tamanho_h + a[1];
							}
							//desenho na vertical
							if (BIT(5) == (BIT(5) & a[0])) //-y
							{
								tamanho_v = tamanho_v -neg8bits(a[2]);
							} else
							{
								tamanho_v = tamanho_v + a[2];
							}

							switch (estado)
							{
							case 'i': //estado inicial
								if (leftkey == 1)
								{
									//reset dos contadores
									tamanho_h = 0;
									tamanho_v = 0;
									estado = 'd';
								}
								break;
							case 'd': //estado de desenho
								if (leftkey == 0 || abs(tamanho_v) > abs(tolerance)) //o botao esquerdo foi libertado ou a tolerancia foi ultrapassada
								{
									estado = 'i';
								}
								else if (length < 0) // length e negativo (deslocacao negativa) -> lado esquerdo
								{
									if (0 == (BIT(4) & a[0])) //deslocacao positiva -> lado direito
									{
										estado = 'i';
									}
									else if (tamanho_h <= length) //ultrapassou length (negativamente)
									{
										estado = 'f';
									}
								}
								else // length e positivo (deslocacao positivo) -> lado direito
									if (0 != (BIT(4) & a[0])) //deslocacao negativa
									{
										estado = 'i';
									}
									else if (tamanho_h >= length) //ultrapassou length (positivamente)
									{
										estado = 'f';
									}
								break;
							case 'f': //estado final
								return 0;
								break;
							}
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
