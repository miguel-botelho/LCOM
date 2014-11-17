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

	if ( (x >= h_res) || (x < 0) || (y >= v_res) || (y < 0) || ((x + size) >= h_res) || ((y + size) >= v_res) ) // o utilizador introduziu coordenadas erradas
		{
			vg_exit();
			printf("Coordenadas erradas!\n");
			kbd_unsubscribe_int();
			return 1;
		}

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



	if ( (xf >= h_res) || (xi < 0) || (yf >= v_res) || (yi < 0) ) // o utilizador introduziu coordenadas erradas
	{
		vg_exit();
		printf("Coordenadas erradas!\n");
		kbd_unsubscribe_int();
		return 1;
	}


	unsigned char *video_copy;
	video_copy = video_mem;

	video_copy = video_copy + (h_res * yi) + xi; //inicializa video_copy no sítio onde é suposto a linha começar

	if ((xi == xf) && (yi == yf))
	{
		*video_copy = color;
	}

	if (xi == xf)
	{
		if (yi > yf)
		{
			unsigned short temp;
			temp = yf;
			yf = yi;
			yi = temp;
		}
		while (yi < yf)
		{
			*video_copy = color;
			video_copy = video_copy + h_res;
			yi++;
		}
	}

	if (yi == yf)
	{
		if (xi > xf)
		{
			unsigned short temp;
			temp = xf;
			xf = xi;
			xi = temp;
		}
		while (xi < xf)
		{
			*video_copy = color;
			video_copy = video_copy + 1;
			xi++;
		}
	}

	if ((xf < xi) && (yf < yi)) // trocar os 2 pontos, quando o ponto final é menor do que o ponto inicial
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
				video_copy = video_copy - h_res; //pintou o pixel, então sobe uma posição
				yi--; //yi começa a aproximar-se de yf
				if (yi < 0) //passou o limite do ecrâ
				{
					vg_exit();
					printf("Passou os limites do ecrâ!\n");
					kbd_unsubscribe_int();
					return 1;
				}
				if (i >= 1)
				{
					i = 0;
					xi++; //xi aproxima-se de xf
					if (xi > h_res) //passou o limite do ecrâ
					{
						vg_exit();
						printf("Passou os limites do ecrâ!\n");
						kbd_unsubscribe_int();
						return 1;
					}
					video_copy = video_copy + 1; //anda uma posição para a direita
				}
			}
		}
		else if (declive <= 1)
		{
			while( (xi <= xf) && (yi >= yf) )
			{
				i = (double) i + declive;
				*video_copy = color;
				video_copy = video_copy + 1; //anda uma posição para a direita
				xi++;
				if (xi > h_res) //passou os limites do ecrâ
				{
					vg_exit();
					printf("Passou os limites do ecrâ!\n");
					kbd_unsubscribe_int();
					return 1;
				}
				if (i >= 1)
				{
					i = 0;
					yi--;
					if (yi < 0) //passou os limites do ecrâ
					{
						vg_exit();
						printf("Passou os limites do ecrâ!\n");
						kbd_unsubscribe_int();
						return 1;
					}
					video_copy = video_copy - h_res; //sobe uma posição
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
				video_copy = video_copy + h_res; //desce uma posição
				yi++;
				if (yi > v_res) //passou os limites do ecrâ
				{
					vg_exit();
					printf("Passou os limites do ecrâ!\n");
					kbd_unsubscribe_int();
					return 1;
				}
				if (i >= 1)
				{
					i = 0;
					xi--;
					if (xi < 0) //passou os limites do ecrâ
					{
						vg_exit();
						printf("Passou os limites do ecrâ!\n");
						kbd_unsubscribe_int();
						return 1;
					}
					video_copy = video_copy - 1; //anda uma posição para a esquerda
				}
			}
		}
		else if (declive <= 1)
		{
			while( (xi >= xf) && (yi <= yf) )
			{
				i = (double) i + declive;
				*video_copy = color;
				video_copy = video_copy - 1; //anda uma posição para a esquerda
				xi--;
				if (xi < 0) //passou os limites do ecrâ
				{
					vg_exit();
					printf("Passou os limites do ecrâ!\n");
					kbd_unsubscribe_int();
					return 1;
				}
				if (i >= 1)
				{
					i = 0;
					yi++;
					if (yi > v_res) //passou os limites do ecrâ
					{
						vg_exit();
						printf("Passou os limites do ecrâ!\n");
						kbd_unsubscribe_int();
						return 1;
					}
					video_copy = video_copy + h_res; //desce uma posição
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
				video_copy = video_copy + h_res; //desce uma posição
				yi++;
				if (yi > v_res)
				{
					vg_exit();
					printf("Passou os limites do ecrâ!\n");
					kbd_unsubscribe_int();
					return 1;
				}
				if (i >= 1)
				{
					i = 0;
					xi++;
					if (xi > h_res)
					{
						vg_exit();
						printf("Passou os limites do ecrâ!\n");
						kbd_unsubscribe_int();
						return 1;
					}
					video_copy = video_copy + 1; //anda uma posição para a direita
				}
			}
		}
		else if (declive <= 1)
		{
			while( (xi <= xf) && (yi <= yf) )
			{
				i = (double) i + declive;
				*video_copy = color;
				video_copy = video_copy + 1; //anda uma posição para a direita
				xi++;
				if (xi > h_res)
				{
					vg_exit();
					printf("Passou os limites do ecrâ!\n");
					kbd_unsubscribe_int();
					return 1;
				}
				if (i >= 1)
				{
					i = 0;
					yi++;
					if (yi > v_res)
					{
						vg_exit();
						printf("Passou os limites do ecrâ!\n");
						kbd_unsubscribe_int();
						return 1;
					}
					video_copy = video_copy + h_res; //desce uma posição
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


