#ifndef __VIDEO_GR_MACROS_H
#define __VIDEO_GR_MACROS_H

#define VBE_MODE 0x4F02 //4f para escrever na bios, 02 vbe mode
#define VBE_GET_MODE 0x4F01 //4f para biso, 01 vbe get mode
#define VBE_CONTROL_INFO 0x4F00
#define INTERRUPT_VBE 0x10
#define GRAPHIC_MODE 0x105
#define GRAPHIC_MODE16 0x117
#define VBE_MODE_SIZE 256


#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)
#define BIT(n) 			(0x01<<(n))
#define LINEAR_MODEL_BIT BIT(14)

#endif /* __VIDEO_GR_MACROS_H */
