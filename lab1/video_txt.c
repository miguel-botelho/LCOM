#include <minix/drivers.h>
#include <sys/video.h>
#include <sys/mman.h>
#include "math.h"

#include <assert.h>

#include "vt_info.h"

#include "video_txt.h"

/* Private global variables */

static char *video_mem;		/* Address to which VRAM is mapped */

static unsigned scr_width;	/* Width of screen in columns */
static unsigned scr_lines;	/* Height of screen in lines */

void vt_fill(char ch, char attr) {
  unsigned w;
  w = 0;
  unsigned l;
  l = 0;
  char *address;
  address = video_mem;
  address = address - 1;

  for (l = 0; l < scr_lines; l = l + 1)
  {
	  for (w = 0; w < scr_width; w = w + 1)
	  {
		  address = address + 1;
		  *address = ch; //character
		  address = address + 1;
		  *address = attr; //atribute
	  }
  }
  /* To complete */
  
}

void vt_blank() {
	vt_fill(0,0);
  /* To complete ... */

}

int vt_print_char(char ch, char attr, int r, int c) {
	char *address;
	address = video_mem;
	address = address + 2 * r * scr_width + 2 * c;
	*address = ch;
	address++;
	*address = attr;
	return 0;

  /* To complete ... */

}

int vt_print_string(char *str, char attr, int r, int c) {
	char *address;
	address = (2 * r * scr_width + 2 * c) + video_mem;
	do
	{
		*address = *str;
		address++;
		*address = attr;
		address++;
		str++;
	}
	while (0 != (*str));
	return 0;
  /* To complete ... */

}

int vt_print_int(int num, char attr, int r, int c) {
	char *address;
	address = (2 * r * scr_width + 2 * c) + video_mem;
	int num_temp;

	if (num < 0)
	num_temp = -num;
	else num_temp = num;
	int i;
	i = 0;

	//quanto o numero de digitos
	do
	{
		i++;
		num_temp = num_temp / 10;
	}
	while (num_temp != 0);

	i--;

	//imprime os digitos
	if (num < 0)
	{
		*address = '-';
		address++;
		*address = attr;
		address++;
		num = -num;
	}
	for (i; i >= 0; i--)
	{
		*address = num / (pow(10,i)) + '0';
		address++;
		*address = attr;
		address++;
		num = num % ((int)(pow(10,i)));
	}

  /* To complete ... */

}


int vt_draw_frame(int width, int height, char attr, int r, int c) {
	char *address;
	address = (2 * r * scr_width + 2 * c) + video_mem;
	address++; //esta a apontar para o atributo
	int linha;
	int coluna;

	for (linha = 0; linha < height; linha++)
	{
		if ((linha == (height - 1)) || (linha == 0))
		{
			for (coluna = 0; coluna < width; coluna++)
						{
								*address = attr;
								address = address + 2;
						}
		}
		else
		for (coluna = 0; coluna < width; coluna++)
			{
				if (coluna == 0 || coluna == (width - 1))
				{
					*address = attr;
				}
				address = address + 2;
			}
		address = address + (scr_width - width) * 2;
		//address = address - 2;
	}
	return 0;
  /* To complete ... */

}

/*
 * THIS FUNCTION IS FINALIZED, do NOT touch it
 */

char *vt_init(vt_info_t *vi_p) {

  int r;
  struct mem_range mr;

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes)(vi_p->vram_base);
  mr.mr_limit = mr.mr_base + vi_p->vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
	  panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vi_p->vram_size);

  if(video_mem == MAP_FAILED)
	  panic("video_txt couldn't map video memory");

  /* Save text mode resolution */

  scr_lines = vi_p->scr_lines;
  scr_width = vi_p->scr_width;

  return video_mem;
}
