#ifndef __VIDEO_GR_MACROS_H
#define __VIDEO_GR_MACROS_H

#define VBE_MODE 0x4F02 //4f para escrever na bios, 02 vbe mode
#define VBE_GET_MODE 0x4F01 //4f para biso, 01 vbe get mode
#define VBE_CONTROL_INFO 0x4F00
#define INTERRUPT_VBE 0x10
#define GRAPHIC_MODE 0x105
#define GRAPHIC_MODE_16_BITS 0x117
#define VBE_MODE_SIZE 256


#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)
#define BIT(n) 			(0x01<<(n))
#define LINEAR_MODEL_BIT BIT(14)

////////////////////////////////////colors//////////////////////////////////////
#define BLACK	rgb(0,0,0)
#define YELLOW	rgb(255,255,0)
#define BLUE	rgb(0,0,255)
#define PINK	rgb(204,0,102)
#define WHITE	rgb(255,255,255)
#define GREEN	rgb(0,255,0)
#define	RED		rgb(255,0,0)
#define	GRAY	rgb(64,64,64)
#define	CYAN	rgb(0,255,255)
#define	ORANGE	rgb(255,128,0)
#define NAVY	rgb(0,0,128)
#define SILVER	rgb(192,192,192)
#define	TEAL	rgb(0,128,128)
#define DARK_GRAY	rgb(169,169,169)
#define LIGHT_GRAY	rgb(211,211,211)

#endif /* __VIDEO_GR_MACROS_H */
