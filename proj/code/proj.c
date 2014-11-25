
#include "lib.h"

int hook_id_timer = 0x01;
int hook_id_keyboard = 0x02;
int hook_id_mouse = 0x04;

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

	/*if (subscribe_all() == -1)
	{
		printf("Failure to subscribe!! \n\n");
		return -1;
	}*/


	//code
	//implementation
	//...

	/*if (unsubscribe_all() == -1)
	{
		printf("Failure to unsubscribe!! \n\n");
		return -1;
	}*/

	return 0;
}
