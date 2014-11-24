#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <minix/sysutil.h>
#include <minix/com.h>
#include <math.h>

#include "vbe.h"
#include "read_xpm.h"
#include "video_gr.h"
#include "test5.h"
#include "lmlib.h"
#include "pixmap.h"
#include <stdint.h>

void *test_init(unsigned short mode, unsigned short delay) {

	char* physical = vg_init(mode);
	if (physical == NULL)
	{
		vg_exit();
		printf("erro\n");
		return NULL;
	}
	int r;
	int ipc_status;
	message msg;
	int i = 0;
	int counter = 0;
	int temp_counter = 0; // conta tique segundos
	char irq_set = BIT(hook_id);

	if (-1 == timer_subscribe_int()) //subscrição do timer
	{
		vg_exit();
		printf("erro_timer\n");
		printf("Timer not subscribed!\n");

		return NULL;
	}

	while (counter < delay) // enquanto não passar o tempo que o utilizador quer
	{
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					temp_counter++; //tique segundos
					if (temp_counter / 60 == 1) // se contar 60 tiques, significa que passou um segundo
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

	timer_unsubscribe_int();

	printf("Physical Memory: %x\n", physical);
	return getVideoMem();
}

int test_square(unsigned short x, unsigned short y, unsigned short size,
		unsigned long color) {

	int r;
	int ipc_status;
	message msg;
	int i = 0;
	int j = 0;
	int key = 0;
	char irq_set = BIT(khook_id);


	if (-1 == kbd_subscribe_int()) //subscrição do keyboard
	{
		printf("Keyboard not subscribed!\n");
		return 0;
	}

	if (vg_init(GRAPHIC_MODE) == NULL)
	{
		vg_exit();
		printf("Graphic mode failed!\n");
		return 1;
	}
	// inicializa em modo gráfico e retorna video_mem

	unsigned h_res = getHRes();
	unsigned v_res = getVRes();
	printf("h_res: %d\n",getHRes());
	unsigned char *video_copy;
	video_copy = getVideoMem();

	if ((x >= h_res) || (x < 0) || (y >= v_res) || (y < 0)
			|| ((x + size) >= h_res) || ((y + size) >= v_res) || (size <= 0)) // o utilizador introduziu coordenadas erradas
	{
		vg_exit();
		kbd_unsubscribe_int();
		return 1;
	}

	video_copy = video_copy + (h_res * y) + x; //coloca o endereço virtual na posição em que o utilizador pretende que comece
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

	for (i; i < size; i++) // pinta linhas verticais
	{
		for (j; j < size; j++) // pinta linhas horizontais
		{
			*video_copy = color;
			video_copy++;
		}
		j = 0;
		video_copy = video_copy + h_res - size; // linha seguinte
	}

	while (key != KBD_ESC_KEY) // condição de saída
	{
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
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
	return 0;
}

int test_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color) {


	if (vg_init(GRAPHIC_MODE) == NULL)
	{
		vg_exit();
		printf("Graphic mode failed!\n");
		return 1;
	} //inicializa o minix em modo gráfico e diz qual o endereço de memória virtual

	int r;
	int ipc_status;
	message msg;
	int j = 0;
	int key = 0;
	char irq_set = BIT(khook_id);


	if (-1 == kbd_subscribe_int()) //subscrição do keyboard
	{
		printf("Keyboard not subscribed!\n");
		return 0;
	}

	unsigned h_res = getHRes();
	unsigned v_res = getVRes();

	if ((xf >= h_res) || (xi < 0) || (yf >= v_res) || (yi < 0) || (xf < 0)
			|| (yf < 0)) // o utilizador introduziu coordenadas erradas
	{
		vg_exit();
		printf("Coordenadas erradas!\n");
		kbd_unsubscribe_int();
		return 1;
	}

	unsigned char *video_copy;
	video_copy = getVideoMem();

	video_copy = video_copy + (h_res * yi) + xi; //inicializa video_copy no sítio onde é suposto a linha começar
	/*
	 if ((xi == xf) && (yi == yf)) //o utilizador apenas quer um ponto de uma linha
	 {
	 *video_copy = color;
	 }

	 if (xi == xf) // linha vertical
	 {
	 if (yi > yf) // se o inicial é menor que o final, troca
	 {
	 unsigned short temp;
	 temp = yf;
	 yf = yi;
	 yi = temp;
	 }
	 while (yi < yf)
	 {
	 *video_copy = color;
	 video_copy = video_copy + h_res; //desce uma posição
	 yi++;
	 }
	 }

	 if (yi == yf) //linha horizontal
	 {
	 if (xi > xf) //se inicial é menor que o final, troca
	 {
	 unsigned short temp;
	 temp = xf;
	 xf = xi;
	 xi = temp;
	 }
	 while (xi < xf)
	 {
	 *video_copy = color;
	 video_copy = video_copy + 1; //anda uma posição para a direita
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
	 i = (double) i + 1/declive;
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
	 vg_exit();video_mem = malloc((bits_per_pixel / 8) * h_res * v_res);
	 printf("Passou os limites do ecrâ!\n");
	 kbd_unsubscribe_int();
	 return 1;
	 }
	 video_copy = video_copy + h_res; //desce uma posição
	 }
	 }
	 }
	 }
	 */
	/*
	 unsigned long dx,dy;
	 int d,flag,incremento,incremento1;
	 int var = 0;
	 dx=abs(xi-xf);dy=abs(yi-yf);

	 *video_copy = color;
	 if(dy>dx)
	 {
	 unsigned short temp;
	 temp = xi;
	 xi = yi;
	 yi = temp;
	 temp = xf;
	 xf = yf;
	 yf = temp;
	 temp = dy;
	 dy = dx;
	 dx = temp;
	 var=1;
	 }
	 if(xi>xf)
	 {
	 unsigned short temp;
	 temp = xi;
	 xi = xf;
	 xf = temp;
	 temp = yi;
	 yi = yf;
	 yf = temp;
	 }
	 if(yi>yf)
	 flag=-1;
	 else
	 flag=1;
	 d=2*dy-dx;
	 incremento=2*dy;
	 incremento1=2*(dy-dx);
	 while(xi<xf)
	 {
	 if(d<=0)
	 d+=incremento;
	 else
	 {
	 d+=incremento1;
	 yi+=flag;
	 }
	 xi++;
	 if(var)
	 {
	 video_copy = video_mem;
	 video_copy = video_copy + (h_res * xi) + yi;
	 *video_copy = color;
	 }
	 else
	 {
	 video_copy = video_mem;
	 video_copy = video_copy + (h_res * yi) + xi;
	 *video_copy = color;
	 }

	 }
	 */

	int dx = abs(xf - xi);
	int dy = abs(yf - yi);
	int i;
	if (dx > dy) {
		if (xf - xi < 0) {
			int temp = xi;
			xi = xf;
			xf = temp;
			temp = yi;
			yi = yf;
			yf = temp;
		}
		for (i = 0; i <= dx; i++) {
			double y = (double) dy * (double) i / (double) dx;
			if (yf - yi < 0) {
				video_copy = getVideoMem();
				video_copy = video_copy + (h_res * (yi - (int) (y + 0.5))) + xi + i;
				*video_copy = color;
			}
			else {
				video_copy = getVideoMem();
				video_copy = video_copy + (h_res * (yi + (int) (y + 0.5))) + xi + i;
				*video_copy = color;
			}
		}
	}

	else {
		if (yf - yi < 0) {
			int temp = xi;
			xi = xf;
			xf = temp;
			temp = yi;
			yi = yf;
			yf = temp;
		}

		for (i = 0; i <= dy; i++) {
			double x = (double) dx * (double) i / (double) dy;
			if (xf - xi < 0) {
				video_copy = getVideoMem();
				video_copy = video_copy + (h_res * (yi + i)) + xi - (int) (x + 0.5);
				*video_copy = color;
			}
			else {
				video_copy = getVideoMem();
				video_copy = video_copy + (h_res * (yi + i)) + xi + (int) (x + 0.5);
				*video_copy = color;
			}
		}
	}

	while (key != KBD_ESC_KEY) //condição de saída
	{
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
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

	if (vg_init(GRAPHIC_MODE) == NULL)
	{
		vg_exit();
		printf("Graphic mode failed!\n");
		return 1;
	}

	int r;
	int ipc_status;
	message msg;
	unsigned int i = 0;
	int key = 0;
	char irq_set = BIT(khook_id);
	unsigned h_res = getHRes();
	unsigned v_res = getVRes();

	if (-1 == kbd_subscribe_int()) //subscrição do keyboard
	{
		printf("Keyboard not subscribed!\n");
		return 0;
	}

	int bool;

	int width;
	int height;

	bool = xpm_cre(&height, &width, xi, yi, xpm);

	if (bool == 1) {
		return 1;
	} else {
		while (key != KBD_ESC_KEY) //condição de saída
		{
			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
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
	}

	vg_exit();
	kbd_unsubscribe_int();

	return 0;

}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	/* To be completed */

	if (vg_init(GRAPHIC_MODE) == NULL)
	{
		vg_exit();
		printf("Graphic mode failed!\n");
		return 1;
	}

	int r;
	int ipc_status;
	message msg;
	unsigned int i = 0;
	int key = 0;
	char irq_set = BIT(khook_id);
	char irq_set_timer = BIT(hook_id);
	int temp_counter = 0;
	int counter = 0;
	double delta_move = 0;
	double delta_time = 0;
	unsigned h_res = getHRes();
	unsigned v_res = getVRes();

	int width;
	int height;

	delta_time = (double) delta / (double) (time * 60);

	xpm_cre(&height, &width, xi, yi, xpm);

	if (-1 == kbd_subscribe_int()) //subscrição do keyboard
	{
		vg_exit();
		printf("Keyboard not subscribed!\n");
		return 0;
	}

	if (-1 == timer_subscribe_int())
	{
		vg_exit();
		printf("Timer not subscribed!\n");
		return 0;
	}

	while (counter < time) //condição de saída
	{
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					kbd_scan_c(&key);
					if (key == KBD_ESC_KEY)
					{
						kbd_unsubscribe_int();
						timer_unsubscribe_int();
						vg_exit();
						return 0;
					}
				}
				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					temp_counter++; //tique segundos
					if (temp_counter / 60 == 1) // se contar 60 tiques, significa que passou um segundo
					{
						temp_counter = 0;
						counter++;
					}
					delta_move = delta_move + delta_time;
					if ((delta_move >= 1) || (delta_move <= -1))
					{
						if (hor) //escrever na horizontal
						{
							xpm_del(&height, &width, xi, yi);
							xi = xi + (int)delta_move;
							xpm_cre(&height, &width, xi, yi, xpm);
						}
						else //escrever na vertical
						{
							xpm_del(&height, &width, xi, yi);
							yi = yi + (int)delta_move;
							xpm_cre(&height, &width, xi, yi, xpm);
						}
						delta_move = delta_move - (int) delta_move;
					}

				}
			}
		}
	}

	kbd_unsubscribe_int();
	timer_unsubscribe_int();
	vg_exit();
	return 1;
}

int test_controller() {

	vbe_info_block config;

	if (get_vbe_info(&config) == 1)
	{
		return 0;
	}

	printf("Controller Capablities:\n");

	if ((config.Capabilities[0] && BIT(0)) == 0)
	{
		printf("DAC is fixed width, with 6 bits per primary color\n");

	}
	else
	{
		printf("DAC width is switchable to 8 bits per primary color\n");
	}

	if ((config.Capabilities[0] && BIT(1)) == 0)
	{
		printf("Controller is VGA compatible\n");
	}
	else
	{
		printf("Controller is not VGA compatible\n");
	}

	if ((config.Capabilities[0] && BIT(2)) == 0)
	{
		printf("Normal RAMDAC operation\n");
	}
	else
	{
		printf("When programming large blocks of information to the RAMDAC, use the blank bit in Function 09h\n");
	}


	printf("\n");
	printf("Supported Modes:\n");

	short *fisico = config.VideoModePtr;
	int x = fisico;
	x = ((x >> 12) & 0xF0000) + (x & 0x0FFFF);
	x = x + posicao;
	fisico = x;
	while (*fisico != -1)
	{
		printf("%x\t", *fisico);
		fisico++;
	}

	printf("Size of VRAM: %x\n", config.TotalMemory * 64);

	return 1;

	/* To be completed */
}
