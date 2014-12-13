
#include "lib.h"

#include "subscribe_macros.h"

//#include "hook_id.h"

#include "device_interrupts.h"
#include "keyboard.h"
#include "mouse.h"
#include "timer.h"
#include "video_gr.h"
#include "bitmap.h"
#include "mouse_struct.h"

// NEEDS TO BE MADE!!!!!!!
//bitmap.c:113 -> start address of the video card (to draw)


int main(int argc, char **argv) {

	// Initialize service

	sef_startup();

	// Enable IO-sensitive operations for ourselves
	sys_enable_iop(SELF);



	int r;
	int ipc_status;
	message msg;
	int key = 0;
	int temp_counter = 0;
	int counter = 0;
	char irq_set_keyboard = BIT(macro_hook_id_keyboard);
	char irq_set_timer = BIT(macro_hook_id_timer);
	char irq_set_mouse = BIT(macro_hook_id_mouse);

	if (timer_set_square(0, 60) == -1)
	{
		printf("Time not set!\n");
		return -1;
	}

	char a[3];
	char bool2 = 0; //0 = true, nao 0 = true
	char byte1;
	char byte2;
	char byte3;
	unsigned int mouse;
	unsigned long key_register;

	//read the first byte
	sys_inb(OUT_BUF, &key_register);
	mouse = (unsigned int) key_register;
	if (BIT(3) == (BIT(3) & mouse))
	{
		byte1 = mouse;
	}

	if (subscribe_all() == -1)
	{
		printf("Failure to subscribe!! \n\n");
		return -1;
	}

	mouse_int_handler(SET_STREAM); //define o rato como stream mode
	printf("OLA");
	mouse_int_handler(ESDP); //ativa o envio dos dados por parte do rato

	printf("OLA");
	vg_init(GRAPHIC_MODE_16_BITS);
	Bitmap* bmp;
	int contador = 0;
	bmp = loadBitmap("home/lcom/proj/code/images/Penis.bmp");
	int x = 0;
	int y = 0;

	while ((x + bmp->bitmapInfoHeader.width) < 1024)
	{
		drawBitmap(bmp,x,y, ALIGN_LEFT);
		y = y + bmp->bitmapInfoHeader.height;
		if ((y + bmp->bitmapInfoHeader.height) > 768)
		{
			x = x + bmp->bitmapInfoHeader.width;
			y = 0;
		}
	}

	while ( (key != KBD_ESC_KEY) && (counter < 5) && (mouse_t.LB == 0) )  // condição de saída
	{
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_keyboard) { /* subscribed interrupt */
					kbd_scan_c(&key);
				}
				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					temp_counter++;
					if ((temp_counter/60) == 1) //se for true quer dizer que passou um segundo
					{
						temp_counter = 0;
						counter++;
					}
				}

				if (msg.NOTIFY_ARG & irq_set_mouse)
				{
					printf("NOTIFY_MOUSE\n");
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
						fill_struct(a); //fill the struct
						printf("left button: %x\n", mouse_t.LB);
					}
				}
			}
		}
	}

	deleteBitmap(bmp);
	vg_exit();

	//code
	//implementation
	//...

	if (unsubscribe_all() == -1)
	{
		printf("Failure to unsubscribe!! \n\n");
		return -1;
	}

	return 0;
}
