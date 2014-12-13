
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
	sleep(5);
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
