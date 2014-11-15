#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "video_gr.h"
#include "vbe.h"
#include "test5.h"
#include "lmlib.h"
#include <stdint.h>



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


	struct vbe_mode_info_t *config;
	if ( vbe_set_mode(VBE_MODE, mode) == 1)
		return NULL;
	else
	{
		int r;
		struct mem_range mr;

		/* Allow memory mapping */

		mr.mr_base = (phys_bytes)(VRAM_PHYS_ADDR);
		mr.mr_limit = mr.mr_base + 1024*768;

		if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
			panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

		/* Map memory */

		video_mem = vm_map_phys(SELF, (void *)mr.mr_base, 1024*768);

		if(video_mem == MAP_FAILED)
			panic("video_txt couldn't map video memory");

		return video_mem;

	}

}
