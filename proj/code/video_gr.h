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

char * getMouseBuffer();
char * getScreenBuffer();
char * getHumanMachine();

/**
 * @brief returns video memory
 *
 * @return video_memory
 */
char* getVideoMem();

/**
 * @brief returns horizontal resolution
 *
 * @return h_res
 */
unsigned getHRes();

/**
 * @brief returns vertical resolution
 *
 * @return v_res
 */
unsigned getVRes();

/**
 * @brief returns bits per pixel
 *
 * @return bits_per_pixel
 */
unsigned getBitsPerPixel();


/**
 * @brief copies the screen buffer to the mouse buffer
 *
 * @param char screen buffer
 * @param char mouse buffer
 *
 */
void screen_to_mouse(char * screen_buffer, char * mouse_buffer);

/**
 * @brief copies the mouse buffer to video memory
 *
 * @param char mouse buffer
 * @param char video memory
 */
void mouse_to_video(char * mouse_buffer, char * video_memory);

/**
 * @brief maps the virtual memory in the selected mode
 *
 * @param mode Graphic mode
 * @param vmi_p struct for vbe
 *
 * @return 0 if mapping is successfull, 1 otherwise
 */
int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p); //NOT COMPLETED

/**
 * @brief sets the mode (graphic mode) with the desired function
 *
 * @param function (the VBE)
 * @param mode (graphic mode)
 *
 * @return 0 if mode is set correctly, 1 otherwise
 */
int vbe_set_mode(unsigned short function, unsigned short mode); //sets the mode mode in the function that the user sets

/**
 * @brief gets the vbe info(own function)
 *
 * @param vib_p struct for vbe
 *
 * @return 0 if mapping is successfull, 1 otherwise
 */
int get_vbe_info(vbe_info_block *vib_p);

/**
 * @brief changes an rgb color to an int only
 *
 * @param r red color
 * @param g green color
 * @param b blue color
 *
 * @return color
 */
int rgb(unsigned char r, unsigned char g, unsigned char b);

void reverse_rgb(int *red, int *green, int *blue, int color);
#endif /* __VIDEO_GR_H */
