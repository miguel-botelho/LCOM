#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

#include "lib.h"
#include "lmlib.h"

#include "subscribe_macros.h"

#include "video_gr_macros.h"
#include "vbe_struct.h"
#include "keyboard_mouse_macros.h"

/**
 * @brief Initializes the video module in graphics mode
 *
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen,
 *  and the number of colors
 *
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

/**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 *
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);

/**
 * @brief Tests drawing a square with a given color
 *
 * Tests drawing a square with the specified size and color, at the specified
 *  coordinates (which specify the upper left corner (ULC)) in video mode 0x105
 *
 * @param x horizontal coordinate of ULC, starts at 0 (leftmost pixel)
 * @param y vertical coordinate of ULC, starts at 0 (top pixel)
 * @param size of each side in pixels
 * @param color color to set the pixel
 * @return 0 on success, non-zero otherwise
 */
int test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color);

char* getVideoMem();
unsigned getHRes();
unsigned getVRes();

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p); //NOT COMPLETED
int vbe_set_mode(unsigned short function, unsigned short mode); //sets the mode mode in the function that the user sets
int get_vbe_info(vbe_info_block *vib_p);

char *read_xpm(char *map[], int *width, int *height);
int xpm_cre(int *altura, int *largura, unsigned short x, unsigned short y, char *xpm[]);
int xpm_del(int *altura, int *largura, unsigned short x, unsigned short y);

int rgb(unsigned char r, unsigned char g, unsigned char b);
#endif /* __VIDEO_GR_H */
