
#include "lib.h"

#include "subscribe_macros.h"

//#include "hook_id.h"

#include "device_interrupts.h"
#include "keyboard.h"
#include "mouse.h"
#include "timer.h"
#include "video_gr.h"
#include "bitmap.h"

// NEEDS TO BE MADE!!!!!!!
//bitmap.c:113 -> start address of the video card (to draw)


int main(int argc, char **argv) {

	// Initialize service
	sef_startup();

	// Enable IO-sensitive operations for ourselves
	sys_enable_iop(SELF);

	if (subscribe_all() == -1)
	{
		printf("Failure to subscribe!! \n\n");
		return -1;
	}

	int contador = 0;
	int temp_counter = 0;
	int key = 0;
	int r;
	int ipc_status;
	message msg;

	vg_init(GRAPHIC_MODE_16_BITS);
	Bitmap* bmp;

	bmp = loadBitmap("home/lcom/proj/code/images/A.bmp");
	drawBitmap(bmp, 0, 0 , ALIGN_LEFT);

	char irq_set_keyboard = BIT(macro_hook_id_keyboard);
	char irq_set_timer = BIT(macro_hook_id_timer);


	while( (contador < 5) && (key != KBD_ESC_KEY) ) { /* You may want to use a different condition */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_timer) { /* subscribed interrupt */
					temp_counter++;
					if ((temp_counter/60) == 1) //se for true quer dizer que passou um segundo
					{
						contador++;
						temp_counter = 0; //reset do temp_counter para voltar a contar os primeiros freq tiques
					}
					/* process it */
				}
				if (msg.NOTIFY_ARG & irq_set_keyboard)
				{
					kbd_scan_c(&key);
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
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

