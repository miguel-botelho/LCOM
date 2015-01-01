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
	scan_code[0x0010] = loadBitmap(FONT_PATH"Q.bmp");
	scan_code[0x0011] = loadBitmap(FONT_PATH"W.bmp");
	scan_code[0x0012] = loadBitmap(FONT_PATH"E.bmp");
	scan_code[0x0013] = loadBitmap(FONT_PATH"R.bmp");
	scan_code[0x0014] = loadBitmap(FONT_PATH"T.bmp");
	scan_code[0x0015] = loadBitmap(FONT_PATH"Y.bmp");
	scan_code[0x0016] = loadBitmap(FONT_PATH"U.bmp");
	scan_code[0x0017] = loadBitmap(FONT_PATH"I.bmp");
	scan_code[0x0018] = loadBitmap(FONT_PATH"O.bmp");
	scan_code[0x0019] = loadBitmap(FONT_PATH"P.bmp");

	scan_code[0x001E] = loadBitmap(FONT_PATH"A.bmp");
	scan_code[0x001F] = loadBitmap(FONT_PATH"S.bmp");
	scan_code[0x0020] = loadBitmap(FONT_PATH"D.bmp");
	scan_code[0x0021] = loadBitmap(FONT_PATH"F.bmp");
	scan_code[0x0022] = loadBitmap(FONT_PATH"G.bmp");
	scan_code[0x0023] = loadBitmap(FONT_PATH"H.bmp");
	scan_code[0x0024] = loadBitmap(FONT_PATH"J.bmp");
	scan_code[0x0025] = loadBitmap(FONT_PATH"K.bmp");
	scan_code[0x0026] = loadBitmap(FONT_PATH"L.bmp");

	scan_code[0x002C] = loadBitmap(FONT_PATH"Z.bmp");
	scan_code[0x002D] = loadBitmap(FONT_PATH"X.bmp");
	scan_code[0x002E] = loadBitmap(FONT_PATH"C.bmp");
	scan_code[0x002F] = loadBitmap(FONT_PATH"V.bmp");
	scan_code[0x0030] = loadBitmap(FONT_PATH"B.bmp");
	scan_code[0x0031] = loadBitmap(FONT_PATH"N.bmp");
	scan_code[0x0032] = loadBitmap(FONT_PATH"M.bmp");

	unsigned int i = 51;
	for (i; i < 86; i++)
	{
		scan_code[i] = NULL;
	}
}

void fill_number(Bitmap ** numbers)
{
	numbers[0] = loadBitmap(NUMBERS_PATH"0.bmp");
	numbers[1] = loadBitmap(NUMBERS_PATH"1.bmp");
	numbers[2] = loadBitmap(NUMBERS_PATH"2.bmp");
	numbers[3] = loadBitmap(NUMBERS_PATH"3.bmp");
	numbers[4] = loadBitmap(NUMBERS_PATH"4.bmp");
	numbers[5] = loadBitmap(NUMBERS_PATH"5.bmp");
	numbers[6] = loadBitmap(NUMBERS_PATH"6.bmp");
	numbers[7] = loadBitmap(NUMBERS_PATH"7.bmp");
	numbers[8] = loadBitmap(NUMBERS_PATH"8.bmp");
	numbers[9] = loadBitmap(NUMBERS_PATH"9.bmp");
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
}
