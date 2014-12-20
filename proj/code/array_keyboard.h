#ifndef __ARRAY_KEYBOARD_H
#define __ARRAY_KEYBOARD_H

#include "bitmap.h"

Bitmap *key_scancode[86];

key_scancode[0x0010] = loadBitmap("home/lcom/proj/code/images/font/word/Q.bmp");
key_scancode[0x0011] = loadBitmap("home/lcom/proj/code/images/font/word/W.bmp");
key_scancode[0x0012] = loadBitmap("home/lcom/proj/code/images/font/word/E.bmp");
key_scancode[0x0013] = loadBitmap("home/lcom/proj/code/images/font/word/R.bmp");
key_scancode[0x0014] = loadBitmap("home/lcom/proj/code/images/font/word/T.bmp");
key_scancode[0x0015] = loadBitmap("home/lcom/proj/code/images/font/word/Y.bmp");
key_scancode[0x0016] = loadBitmap("home/lcom/proj/code/images/font/word/U.bmp");
key_scancode[0x0017] = loadBitmap("home/lcom/proj/code/images/font/word/I.bmp");
key_scancode[0x0018] = loadBitmap("home/lcom/proj/code/images/font/word/O.bmp");
key_scancode[0x0019] = loadBitmap("home/lcom/proj/code/images/font/word/P.bmp");

key_scancode[0x001E] = loadBitmap("home/lcom/proj/code/images/font/word/A.bmp");
key_scancode[0x001F] = loadBitmap("home/lcom/proj/code/images/font/word/S.bmp");
key_scancode[0x0020] = loadBitmap("home/lcom/proj/code/images/font/word/D.bmp");
key_scancode[0x0021] = loadBitmap("home/lcom/proj/code/images/font/word/F.bmp");
key_scancode[0x0022] = loadBitmap("home/lcom/proj/code/images/font/word/G.bmp");
key_scancode[0x0023] = loadBitmap("home/lcom/proj/code/images/font/word/H.bmp");
key_scancode[0x0024] = loadBitmap("home/lcom/proj/code/images/font/word/J.bmp");
key_scancode[0x0025] = loadBitmap("home/lcom/proj/code/images/font/word/K.bmp");
key_scancode[0x0026] = loadBitmap("home/lcom/proj/code/images/font/word/L.bmp");

key_scancode[0x002C] = loadBitmap("home/lcom/proj/code/images/font/word/Z.bmp");
key_scancode[0x002D] = loadBitmap("home/lcom/proj/code/images/font/word/X.bmp");
key_scancode[0x002E] = loadBitmap("home/lcom/proj/code/images/font/word/C.bmp");
key_scancode[0x002F] = loadBitmap("home/lcom/proj/code/images/font/word/V.bmp");
key_scancode[0x0030] = loadBitmap("home/lcom/proj/code/images/font/word/B.bmp");
key_scancode[0x0031] = loadBitmap("home/lcom/proj/code/images/font/word/N.bmp");
key_scancode[0x0032] = loadBitmap("home/lcom/proj/code/images/font/word/M.bmp");

#endif
