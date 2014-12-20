
#include "lib.h"

#include "struct_scores.h"
#include "struct_bmp.h"
#include "serial_port_macros.h"
#include "subscribe_macros.h"
#include "device_interrupts.h"
#include "keyboard.h"
#include "mouse.h"
#include "timer.h"
#include "video_gr.h"
#include "bitmap.h"
#include "rtc.h"
#include "menu.h"
#include "struct_bmp.h"
#include "read_write.h"

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

	// graphics mode
	bitmap_struct bitmaps;
	bitmaps_load(&bitmaps); // this operation may require a lot of time

	// scores
	scores_t scores;

	char irq_set_keyboard = BIT(macro_hook_id_keyboard);
	char irq_set_timer = BIT(macro_hook_id_timer);
	char irq_set_mouse = BIT(macro_hook_id_mouse);
	char irq_set_sp1 = BIT(macro_hook_id_sp1);
	char irq_set_sp2 = BIT(macro_hook_id_sp2);

	//atributes for the serial port
	unsigned long line_status;
	char send[1];
	int size_send = 1;
	char need_to_write = 0; // 0 = false

	// Initialization of graphics mode
	vg_init(GRAPHIC_MODE_16_BITS);

	// Mouse on the middle of the screen
	mouse_t.x_mouse = getHRes() / 2;
	mouse_t.y_mouse = getVRes() / 2;
	char * mouse_buffer = malloc (getHRes() * getVRes() * getBitsPerPixel() / 8);
	char * screen_buffer = malloc(getHRes() * getVRes() * getBitsPerPixel() / 8);
	char * video_memory = getVideoMem();
	char * video_copy = video_memory;

	// Draw of the background
	drawBitmap(bitmaps.background, 0, 0 , ALIGN_LEFT, screen_buffer);

	screen_to_mouse(screen_buffer, mouse_buffer);
	drawBitmap(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, mouse_buffer);
	mouse_to_video(mouse_buffer, video_memory);

	// enquanto nao for premida a tecla ESC
	while( key != KBD_ESC_KEY) {
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_timer) { /* subscribed interrupt */

				}

				if (msg.NOTIFY_ARG & irq_set_keyboard)
				{
					kbd_scan_c(&key);
					if (key == KEY_SPACE)
					{
						memset(video_memory, 0xFF, (getHRes() * getVRes() * getBitsPerPixel() / 8));
						drawBitmap(bitmaps.frame, 0, 0, ALIGN_LEFT, screen_buffer);
						screen_to_mouse(screen_buffer, mouse_buffer);
						mouse_to_video(mouse_buffer, video_memory);
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

							//funcao exit
							if ((mouse_t.x_mouse >= 438) && (mouse_t.x_mouse <= 591))
							{
								if ((mouse_t.y_mouse >= 650) && (mouse_t.y_mouse <= 716))
								{
									if (mouse_t.LB == 1)
									{
										deleteBitmap(bitmaps.background);
										deleteBitmap(bitmaps.mouse);
										deleteBitmap(bitmaps.frame);
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
									else
									{
										//mudar cor para vermelho
										for (i; i < (getHRes() * getVRes() * getBitsPerPixel() / 8); i++)
										{
											if (*video_copy == rgb(0,0,0))
											{
												printf("PRETO\n");
												*video_copy = rgb(0,255,0);
											}
											video_copy++;
										}
									}
								}
							}
							drawBitmap(bitmaps.background, 0, 0, ALIGN_LEFT, screen_buffer);
							screen_to_mouse(screen_buffer, mouse_buffer);
							drawBitmap(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, mouse_buffer);
							mouse_to_video(mouse_buffer, video_memory);
						}
					}
				}

				if (msg.NOTIFY_ARG & irq_set_sp1)
				{
					sys_inb(BASE_ADDRESS_COM1 + INTERRUPT_IDENTIFICATION, &line_status);
					if (INTERRUPT_ORIGIN_RECEIVED_DATA & line_status)
					{
						com1_receive_interrupt(size_send, send);
						/////////////////////////////////////////////////////////
						// need to call the handler (don exist, need to create)//
						/////////////////////////////////////////////////////////
					}
					else if (INTERRUPT_ORIGIN_TRANSMITTER_EMPTY & line_status)
					{
						if (need_to_write) //need_to_write = 1 = true
						{
							/////////////////////////////////////////////////////////
							// need to call the handler (don exist, need to create)//
							/////////////////////////////////////////////////////////
							need_to_write = 0;
						}
					}
					else
					{
						printf("Error on serial port 1!\n");
					}
				}

				if (msg.NOTIFY_ARG & irq_set_sp2)
				{
					sys_inb(BASE_ADDRESS_COM2 + INTERRUPT_IDENTIFICATION, &line_status);
					if (INTERRUPT_ORIGIN_RECEIVED_DATA & line_status)
					{
						com2_receive_interrupt(size_send, send);
						/////////////////////////////////////////////////////////
						// need to call the handler (don exist, need to create)//
						/////////////////////////////////////////////////////////
					}
					else if (INTERRUPT_ORIGIN_TRANSMITTER_EMPTY & line_status)
					{
						if (need_to_write) //need_to_write = 1 = true
						{
							/////////////////////////////////////////////////////////
							// need to call the handler (don exist, need to create)//
							/////////////////////////////////////////////////////////
							need_to_write = 0;
						}
					}
					else
					{
						printf("Error on serial port 1!\n");
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
	deleteBitmap(bitmaps.background);
	deleteBitmap(bitmaps.mouse);
	deleteBitmap(bitmaps.frame);
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
