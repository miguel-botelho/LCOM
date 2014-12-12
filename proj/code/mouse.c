#include "mouse.h"

int test_packet(){

	int r;
	int ipc_status;
	message msg;
	unsigned int mouse;
	unsigned long key_register;
	int i = 0;
	char bool2 = 0; //0 = true, nao 0 = true
	//char bool3 = 0;
	char irq_set = BIT(macro_hook_id_mouse);

	char a[3];

	char byte1;
	char byte2;
	char byte3;

	//read the first byte
	sys_inb(OUT_BUF, &key_register);
	mouse = (unsigned int) key_register;
	if (BIT(3) == (BIT(3) & mouse))
	{
		byte1 = mouse;
	}

	//mouse_clean_buffer();

	while( i < 1 ) { /* You may want to use a different condition */
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

						//os bytes passam para um array
						a[0] = byte1;
						a[1] = byte2;
						a[2] = byte3;
						i++; //contador de packets
						fill_struct(a); //fill the struct
						return 0;
					}
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else {

		}
	}
}

char neg8bits(char neg) //transforma um char de 8 bits em complemento para 2, para o seu equivalente positivo; i.e -24 transforma-se em 24
{
	int i = 0;
	char ret = 0;
	char negative = 0; //flag que verifica se foi encontrado o primeiro 1

	for (i; i < 8; i++)
	{
		if (negative == 0) //se não foi encontrado o primeiro 1, então copia o bit
		{
			if (BIT(i) == (BIT(i) & neg))
			{
				negative = 1;
				ret = ret + (BIT(i) & neg);
			}
			else ret = ret + (BIT(i) & neg);
		}
		else ret = ret + !(BIT(i) & neg); //troca o bit
	}

	return ret;
}

void fill_struct(char *a) // the size of this array is fixed, so does not need to have an argument to specify the size
{
	mouse_t.LB = a[0] & BIT(0);
	mouse_t.RB = (a[0] & BIT(1)) >> 1;
	mouse_t.MB = (a[0] & BIT(2)) >> 2;
	mouse_t.XOV = (a[0] & BIT(6)) >> 2;
	mouse_t.YOV = (a[0] & BIT(7)) >> 3;

	if (BIT(4) == (BIT(4) & a[0])) // se for negativo
	{
		mouse_t.x = neg8bits(a[1]);
	}
	else //nr positivo
	{
		mouse_t.x = a[1];
	}

	if (BIT(5) == (BIT(5) & a[0])) //negativo
	{
		mouse_t.y = neg8bits(a[2]);
	}
	else //positivo
	{
		mouse_t.y = a[2];
	}
}
