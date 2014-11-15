#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <minix/sysutil.h>
#include <minix/com.h>

#include "vbe.h"
#include "video_gr.h"
#include "test5.h"
#include "lmlib.h"
#include <stdint.h>

void *test_init(unsigned short mode, unsigned short delay) {


	int r;
	int ipc_status;
	message msg;
	int i = 0;
	int counter = 0;
	int temp_counter = 0;
	char irq_set = BIT(hook_id);

	if (-1 == timer_subscribe_int())
	{
		printf("Timer not subscribed!\n");
		return NULL;
	}

	video_mem = vg_init(GRAPHIC_MODE);

	while(counter < delay)
	{
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					temp_counter++;
					if (temp_counter/60 == 1)
					{
						temp_counter = 0;
						counter++;
					}
				}
			}

			/* To be completed */
		}
	}

	vg_exit();

	printf("Physical address: %x\n", video_mem);
	timer_unsubscribe_int();

	return video_mem;
}


int test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {

	int r;
	int ipc_status;
	message msg;
	int i = 0;
	int j = 0;
	int key = 0;
	char irq_set = BIT(khook_id);

	if (-1 == kbd_subscribe_int())
	{
		printf("Keyboard not subscribed!\n");
		return 0;
	}



	video_mem = vg_init(GRAPHIC_MODE);

	unsigned char *video_copy;
	video_copy = video_mem;

	video_copy = video_copy + (h_res * y) + x;
	/*for (i; i < size; i++,video_copy++)
	{
	 *video_copy = color;
	}

	i = 0;
	for (i; i < size; i++)
	{
	 *video_copy = color;
		video_copy = video_copy + h_res;
	}

	i = 0; FRAME
	for (i; i < size; i--, video_copy--)
	{
	 *video_copy = color;
	}

	i = 0;
	for (i; i < size; i--)
	{
	 *video_copy = color;
		video_copy = video_copy - h_res;
	} */

	for (i; i < size; i++)
	{
		for (j; j < size; j++)
		{
			*video_copy = color;
			video_copy++;
		}
		j = 0;
		video_copy = video_copy + h_res -size;
	}


	while(key != KBD_ESC_KEY)
	{
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					kbd_scan_c(&key);
				}
			}
		}
	}

	vg_exit();

	kbd_unsubscribe_int();
	return 1;
}

int test_line(unsigned short xi, unsigned short yi,
		unsigned short xf, unsigned short yf, unsigned long color) {


	int r;
	int ipc_status;
	message msg;
	double i = 0;
	int j = 0;
	int key = 0;
	double declive = (yf - yi)/(xf -xi);
	char irq_set = BIT(khook_id);

	if (-1 == kbd_subscribe_int())
	{
		printf("Keyboard not subscribed!\n");
		return 0;
	}

	video_mem = vg_init(GRAPHIC_MODE);

	unsigned char *video_copy;
	video_copy = video_mem;

	video_copy = video_copy + (h_res * yi) + xi;

	if ((xf < xi) && (yf < yi)) // trocar os 2 pontos
	{
		unsigned short temp;
		temp = xf;
		xf = xi;
		xi = temp;
		temp = yf;
		yf = yi;
		yi = temp;

	}

	declive = (double)(yf - yi)/(double)(xf -xi);

	if ( (xf > xi) && (yf < yi) ) // x da esquerda para a direita e y de baixo para cima
	{
		declive = abs(declive);
		if (declive > 1)
		{
			while( (xi <= xf) && (yi >= yf) )
			{
				i = (double)i + 1/declive;
				*video_copy = color;
				video_copy = video_copy - h_res;
				yi--;
				if (i >= 1)
				{
					i = 0;
					xi++;
					video_copy = video_copy + 1;
				}
			}
		}
		else if (declive <= 1)
		{
			while( (xi <= xf) && (yi >= yf) )
			{
				i = (double) i + declive;
				*video_copy = color;
				video_copy = video_copy + 1;
				xi++;
				if (i >= 1)
				{
					i = 0;
					yi--;
					video_copy = video_copy - h_res;
				}
			}
		}
	}

	declive = (double)(yf - yi)/(double)(xf -xi);
	if ( (xf < xi) && (yf > yi) ) // x da direita para a esquerda e y de cima para baixo
	{
		declive = (double)0 - declive;

		if (declive > 1)
		{
			while( (xi >= xf) && (yi <= yf) )
			{
				i = (double)i + 1/declive;
				*video_copy = color;
				video_copy = video_copy + h_res;
				yi++;
				if (i >= 1)
				{
					i = 0;
					xi--;
					video_copy = video_copy - 1;
				}
			}
		}
		else if (declive <= 1)
		{
			while( (xi >= xf) && (yi <= yf) )
			{
				i = (double) i + declive;
				*video_copy = color;
				video_copy = video_copy - 1;
				xi--;
				if (i >= 1)
				{
					i = 0;
					yi++;
					video_copy = video_copy + h_res;
				}
			}
		}
	}

	if ((xi < xf) && (yi < yf)) // x da esquerda para a direita, y de cima para baixo
	{
		if (declive > 1)
		{
			while( (xi <= xf) && (yi <= yf) )
			{
				i = (double)i + 1/declive;
				*video_copy = color;
				video_copy = video_copy + h_res;
				yi++;
				if (i >= 1)
				{
					i = 0;
					xi++;
					video_copy = video_copy + 1;
				}
			}
		}
		else if (declive <= 1)
		{
			while( (xi <= xf) && (yi <= yf) )
			{
				i = (double) i + declive;
				*video_copy = color;
				video_copy = video_copy + 1;
				xi++;
				if (i >= 1)
				{
					i = 0;
					yi++;
					video_copy = video_copy + h_res;
				}
			}
		}
	}

	while(key != KBD_ESC_KEY)
	{
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					kbd_scan_c(&key);
				}
			}
		}
	}

	vg_exit();

	kbd_unsubscribe_int();
	return 1;

}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {

	/* To be completed */

}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	/* To be completed */

}


