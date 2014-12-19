
#include "lib.h"

#include "subscribe_macros.h"
#include "device_interrupts.h"
#include "keyboard.h"
#include "mouse.h"
#include "timer.h"
#include "video_gr.h"
#include "bitmap.h"
#include "rtc.h"

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

	mouse_int_handler(SET_STREAM); //define o rato como stream mode
	mouse_int_handler(ESDP); //ativa o envio dos dados por parte do rato

	int contador = 0;
	int temp_counter = 0;
	int key = 0;
	int r;
	int ipc_status;
	message msg;

	// mouse
	unsigned int i = 0;
	unsigned int j = 0;
	char bool1 = 0;
	char bool2 = 0;
	char a[3];
	char byte1;
	char byte2;
	char byte3;
	unsigned int mouse;
	unsigned long key_register;

	char irq_set_keyboard = BIT(macro_hook_id_keyboard);
	char irq_set_timer = BIT(macro_hook_id_timer);
	char irq_set_mouse = BIT(macro_hook_id_mouse);



	vg_init(GRAPHIC_MODE_16_BITS);

	mouse_t.x_mouse = getHRes() / 2;
	mouse_t.y_mouse = getVRes() / 2;
	char * mouse_buffer = malloc (getHRes() * getVRes() * getBitsPerPixel() / 8);
	char * screen_buffer = malloc(getHRes() * getVRes() * getBitsPerPixel() / 8);
	char * video_memory = getVideoMem();
	char * video_copy = video_memory;

	Bitmap* fundo;
	Bitmap * leonel;
	Bitmap* rato;

	fundo = loadBitmap("home/lcom/proj/code/images/Fundo.bmp");
	leonel = loadBitmap("home/lcom/proj/code/images/leonel.bmp");
	rato = loadBitmap("home/lcom/proj/code/images/Mouse.bmp");

	drawBitmap(fundo, 0, 0 , ALIGN_LEFT, screen_buffer);

	screen_to_mouse(screen_buffer, mouse_buffer);
	drawBitmap(rato, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, mouse_buffer);
	mouse_to_video(mouse_buffer, video_memory);
	mouse_t.LB = 0;

	// enquanto nao passarem 10 segundos ou nao for premida a tecla ESC ou o clique esquerdo do rato
	while( (contador < 10) && (key != KBD_ESC_KEY)) {
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
				}

				if (msg.NOTIFY_ARG & irq_set_keyboard)
				{
					kbd_scan_c(&key);
					if (key == KEY_SPACE)
					{
						memset(screen_buffer, 0xFF, (getHRes() * getVRes() * getBitsPerPixel() / 8));
						drawBitmap(fundo, 0, 0, ALIGN_LEFT, screen_buffer);
						memcpy(video_memory, screen_buffer, (getHRes() * getVRes() * getBitsPerPixel() / 8));
						for (i; i < (getHRes() * getVRes() * getBitsPerPixel() / 8); i++)
						{
							if (*video_copy == rgb(0,0,0))
							{
								*video_copy = rgb(0,255,0);
							}
							video_copy++;
						}
					}

				}

				if (msg.NOTIFY_ARG & irq_set_mouse)
				{
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
							fill_struct(a);

							if (mouse_t.LB == 1)
							{
								if ((mouse_t.x_mouse >= 438) && (mouse_t.x_mouse <= 591))
								{
									if ((mouse_t.y_mouse >= 650) && (mouse_t.y_mouse <= 716))
									{
										deleteBitmap(fundo);
										deleteBitmap(leonel);
										deleteBitmap(rato);
										vg_exit();

										//estas duas opearacoes sao feitas para assegurar o normal funcionamento do rato quando acabar a funcao
										mouse_int_handler(DISABLE_STREAM); //desativa a stream
										mouse_int_handler(SET_STREAM); //volta a ativar a stream, isto foi feito para desativar o envio dos pacotes

										if (unsubscribe_all() == -1)
										{
											printf("Failure to unsubscribe!! \n\n");
											return -1;
										}
										return 0;
									}
								}
							}
							screen_to_mouse(screen_buffer, mouse_buffer);
							drawBitmap(rato, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, mouse_buffer);
							mouse_to_video(mouse_buffer, video_memory);

						}
					}
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	deleteBitmap(fundo);
	deleteBitmap(leonel);
	deleteBitmap(rato);
	vg_exit();

	//estas duas opearacoes sao feitas para assegurar o normal funcionamento do rato quando acabar a funcao
	mouse_int_handler(DISABLE_STREAM); //desativa a stream
	mouse_int_handler(SET_STREAM); //volta a ativar a stream, isto foi feito para desativar o envio dos pacotes

	if (unsubscribe_all() == -1)
	{
		printf("Failure to unsubscribe!! \n\n");
		return -1;
	}

	return 0;
}

