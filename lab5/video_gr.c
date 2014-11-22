#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "video_gr.h"
#include "read_xpm.h"
#include "vbe.h"
#include "test5.h"
#include "lmlib.h"
#include "pixmap.h"
#include <stdint.h>

static char *video_mem;		/* Process address to which VRAM is mapped */
static long vram_size;		/* Size of VRAM */
static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

int vg_exit() {
	struct reg86u reg86;

	reg86.u.b.intno = 0x10; /* BIOS video services */

	reg86.u.b.ah = 0x00;    /* Set Video Mode function */
	reg86.u.b.al = 0x03;    /* 80x25 text mode*/

	if( sys_int86(&reg86) != OK ) {
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	} else
		return 0;
}

void *vg_init(unsigned short mode) {


	vbe_mode_info_t config;

	if ( vbe_set_mode(VBE_MODE, mode) == 1) //set graphic mode
		return NULL;

	if (vbe_get_mode_info(mode, &config) != 0) //get vbe info
	{
		return NULL;
	}

	h_res = config.XResolution; //store X Resolution
	v_res = config.YResolution; //store Y Resolution
	bits_per_pixel = config.BitsPerPixel; //store Bits Per Pixel
	vram_size = (config.XResolution * config.YResolution * config.BitsPerPixel) / 8; //store the size of the vram


	int r;
	struct mem_range mr;

	/* Allow memory mapping */

	mr.mr_base = (config.PhysBasePtr);
	mr.mr_limit = mr.mr_base + (config.XResolution * config.YResolution * config.BitsPerPixel) / 8;

	if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, (config.XResolution * config.YResolution * config.BitsPerPixel) / 8);

	if(video_mem == MAP_FAILED)
		panic("video_txt couldn't map video memory");


	if (video_mem == NULL)
	{
		printf("vg_init: Error!\n");
		vg_exit();
		return NULL;
	}
	return video_mem;
}

char* getVideoMem(){

	return video_mem;
}

unsigned getHRes(){

	return h_res;
}

unsigned getVRes(){

	return v_res;
}
