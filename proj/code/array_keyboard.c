#include "array_keyboard.h"

void fill_key_scancode(Bitmap ** scan_code)
{
	scan_code[0x0001] = NULL;
	scan_code[0x0002] = NULL;
	scan_code[0x0003] = NULL;
	scan_code[0x0004] = NULL;
	scan_code[0x0005] = NULL;
	scan_code[0x0006] = NULL;
	scan_code[0x0007] = NULL;
	scan_code[0x0008] = NULL;
	scan_code[0x0009] = NULL;
	scan_code[0x0010] = loadBitmap("home/lcom/proj/code/images/font/word/Q.bmp");
	scan_code[0x0011] = loadBitmap("home/lcom/proj/code/images/font/word/W.bmp");
	scan_code[0x0012] = loadBitmap("home/lcom/proj/code/images/font/word/E.bmp");
	scan_code[0x0013] = loadBitmap("home/lcom/proj/code/images/font/word/R.bmp");
	scan_code[0x0014] = loadBitmap("home/lcom/proj/code/images/font/word/T.bmp");
	scan_code[0x0015] = loadBitmap("home/lcom/proj/code/images/font/word/Y.bmp");
	scan_code[0x0016] = loadBitmap("home/lcom/proj/code/images/font/word/U.bmp");
	scan_code[0x0017] = loadBitmap("home/lcom/proj/code/images/font/word/I.bmp");
	scan_code[0x0018] = loadBitmap("home/lcom/proj/code/images/font/word/O.bmp");
	scan_code[0x0019] = loadBitmap("home/lcom/proj/code/images/font/word/P.bmp");

	scan_code[0x001E] = loadBitmap("home/lcom/proj/code/images/font/word/A.bmp");
	scan_code[0x001F] = loadBitmap("home/lcom/proj/code/images/font/word/S.bmp");
	scan_code[0x0020] = loadBitmap("home/lcom/proj/code/images/font/word/D.bmp");
	scan_code[0x0021] = loadBitmap("home/lcom/proj/code/images/font/word/F.bmp");
	scan_code[0x0022] = loadBitmap("home/lcom/proj/code/images/font/word/G.bmp");
	scan_code[0x0023] = loadBitmap("home/lcom/proj/code/images/font/word/H.bmp");
	scan_code[0x0024] = loadBitmap("home/lcom/proj/code/images/font/word/J.bmp");
	scan_code[0x0025] = loadBitmap("home/lcom/proj/code/images/font/word/K.bmp");
	scan_code[0x0026] = loadBitmap("home/lcom/proj/code/images/font/word/L.bmp");

	scan_code[0x002C] = loadBitmap("home/lcom/proj/code/images/font/word/Z.bmp");
	scan_code[0x002D] = loadBitmap("home/lcom/proj/code/images/font/word/X.bmp");
	scan_code[0x002E] = loadBitmap("home/lcom/proj/code/images/font/word/C.bmp");
	scan_code[0x002F] = loadBitmap("home/lcom/proj/code/images/font/word/V.bmp");
	scan_code[0x0030] = loadBitmap("home/lcom/proj/code/images/font/word/B.bmp");
	scan_code[0x0031] = loadBitmap("home/lcom/proj/code/images/font/word/N.bmp");
	scan_code[0x0032] = loadBitmap("home/lcom/proj/code/images/font/word/M.bmp");

	unsigned int i = 51;
	for (i; i < 86; i++)
	{
		scan_code[i] = NULL;
	}
}

