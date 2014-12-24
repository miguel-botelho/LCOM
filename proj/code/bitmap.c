#include "bitmap.h"

void createDBitmap()
{
	bmpfile_t *bmp;

	char * screen_buffer = getScreenBuffer();
	size_t ax, ay;
	screen_buffer += ((1024 * 768) - 1) * 2;

	int red, green, blue;
	////canvas: x = 120 a 1020; y = 187 a 717
	int i, j;
	bmp = bmp_create(1025 - 126, 717 - 186,16);

	for(i = 126; i < 1025; i++)
	{
		for (j = 187; j < 717; j++)
		{
			reverse_rgb(&red, &green, &blue, *((uint16_t *)screen_buffer + i + j * 1024));
			//getrgbBitmap(&red, &green, &blue, *((uint16_t *)screen_buffer + i + j * 1024));
			rgb_pixel_t pixel = {blue, green, red, 0};
			bmp_set_pixel(bmp,(uint32_t)(i - 126),(uint32_t)(j - 187),pixel);
		}
	}

	char a[] = "home/lcom/proj/code/files/d0.bmp";

	if (screen_current >= 9)
	{
		screen_current = 9;
		screen_abs = screen_current;
		remove("home/lcom/proj/code/files/d0.bmp");
		rename("home/lcom/proj/code/files/d1.bmp", "home/lcom/proj/code/files/d0.bmp");
		rename("home/lcom/proj/code/files/d2.bmp", "home/lcom/proj/code/files/d1.bmp");
		rename("home/lcom/proj/code/files/d3.bmp", "home/lcom/proj/code/files/d2.bmp");
		rename("home/lcom/proj/code/files/d4.bmp", "home/lcom/proj/code/files/d3.bmp");
		rename("home/lcom/proj/code/files/d5.bmp", "home/lcom/proj/code/files/d4.bmp");
		rename("home/lcom/proj/code/files/d6.bmp", "home/lcom/proj/code/files/d5.bmp");
		rename("home/lcom/proj/code/files/d7.bmp", "home/lcom/proj/code/files/d6.bmp");
		rename("home/lcom/proj/code/files/d8.bmp", "home/lcom/proj/code/files/d7.bmp");
		rename("home/lcom/proj/code/files/d9.bmp", "home/lcom/proj/code/files/d8.bmp");
	}
	else
	{
		screen_current++;
		screen_abs = screen_current;
	}

	a[Dx] = screen_current + '0';


	bmp_save(bmp,a);
	bmp_destroy(bmp);
}

void createBitmapsUndoRedo()
{
	bmpfile_t *bmp;

	bmp = bmp_create(1025 - 126, 717 - 186,16);

	int i, j;

	for(i = 126; i < 1025; i++)
	{
		for (j = 187; j < 717; j++)
		{
			rgb_pixel_t pixel = {255, 255, 255, 0}; //white
			bmp_set_pixel(bmp,(uint32_t)(i - 126),(uint32_t)(j - 187),pixel);
		}
	}


	char a[] = "home/lcom/proj/code/files/d0.bmp";

	for (i = 0; i < 10; i++)
	{
		a[Dx] = i + '0';
		bmp_save(bmp, a);
	}
	bmp_destroy(bmp);
}

void createBitmap()

{
	bmpfile_t *bmp;

	char * screen_buffer = getScreenBuffer();
	size_t ax, ay;
	screen_buffer += ((1024 * 768) - 1) * 2;

	int red, green, blue;
	////canvas: x = 120 a 1020; y = 187 a 717
	int i, j;
	bmp = bmp_create(1025 - 126, 717 - 186,16);

	for(i = 126; i < 1025; i++)
	{
		for (j = 187; j < 717; j++)
		{
			reverse_rgb(&red, &green, &blue, *((uint16_t *)screen_buffer + i + j * 1024));
			//getrgbBitmap(&red, &green, &blue, *((uint16_t *)screen_buffer + i + j * 1024));
			rgb_pixel_t pixel = {blue, green, red, 0};
			bmp_set_pixel(bmp,(uint32_t)(i - 126),(uint32_t)(j - 187),pixel);
		}
	}

	char a[] = "home/lcom/proj/code/files/current_draw.bmp";

	bmp_save(bmp,a);
	bmp_destroy(bmp);

}

void getrgbBitmap(int *red, int *green, int *blue, int rgbaaaa)
{
	/**red = 255;//255 - 255; //255
	 *green = 106;//106 - 1; //106
	 *blue = 0;//255 - 0; //0
		return;*/
	if (rgbaaaa == BLACK)
	{
		*red = 0;
		*green = 0;
		*blue = 0;
	}
	else if (rgbaaaa == YELLOW){
		*red = 255;
		*green = 251;
		*blue = 0;
	}
	else if (rgbaaaa == BLUE){
		*red = 0;
		*green = 12;
		*blue = 255;
	}
	else if (rgbaaaa == PINK){
		*red = 255;
		*green = 0;
		*blue = 173;
	}
	else if (rgbaaaa == WHITE){
		*red = 255;
		*green = 255;
		*blue = 255;
	}
	else if (rgbaaaa == GREEN){
		*red = 16;
		*green = 138;
		*blue = 0;
	}
	else if (rgbaaaa == RED){
		*red = 255;
		*green = 0;
		*blue = 0;
	}
	else if (rgbaaaa == GRAY){
		*red = 107;
		*green = 109;
		*blue = 107;
	}
	else if (rgbaaaa == CYAN){
		*red = 0;
		*green = 255;
		*blue = 255;
	}
	else if (rgbaaaa == ORANGE){
		*red = 255;
		*green = 113;
		*blue = 0;
	}
	else if (rgbaaaa == NAVY){
		*red = 0;
		*green = 0;
		*blue = 128;
	}
	else if (rgbaaaa == SILVER){
		*red = 192;
		*green = 192;
		*blue = 192;
	}
	else if (rgbaaaa == TEAL){
		*red = 0;
		*green = 128;
		*blue = 128;
	}
	else if (rgbaaaa == PURPLE){
		*red = 123;
		*green = 4;
		*blue = 156;
	}
	else if (rgbaaaa == BROWN){
		*red = 132;
		*green = 61;
		*blue = 8;
	}
	else if (rgbaaaa == DARK_GRAY){
		*red = 169;
		*green = 169;
		*blue = 169;
	}
	else /*if (rgbaaaa == LIGHT_GRAY)*/{
		*red = 211;
		*green = 211;
		*blue = 211;
	}
}

Bitmap* loadBitmap(const char* filename) {
	// allocating necessary size
	Bitmap* bmp = (Bitmap*) malloc(sizeof(Bitmap));

	// open filename in read binary mode
	FILE *filePtr;
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// read the bitmap file header
	BitmapFileHeader bitmapFileHeader;
	fread(&bitmapFileHeader, 2, 1, filePtr);

	// verify that this is a bmp file by check bitmap id
	if (bitmapFileHeader.type != 0x4D42) {
		fclose(filePtr);
		return NULL;
	}

	int rd;
	do {
		if ((rd = fread(&bitmapFileHeader.size, 4, 1, filePtr)) != 1)
			break;
		if ((rd = fread(&bitmapFileHeader.reserved, 4, 1, filePtr)) != 1)
			break;
		if ((rd = fread(&bitmapFileHeader.offset, 4, 1, filePtr)) != 1)
			break;
	} while (0);

	if (rd = !1) {
		fprintf(stderr, "Error reading file\n");
		exit(-1);
	}

	// read the bitmap info header
	BitmapInfoHeader bitmapInfoHeader;
	fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePtr);

	// move file pointer to the begining of bitmap data
	fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

	// allocate enough memory for the bitmap image data
	unsigned char* bitmapImage = (unsigned char*) malloc(
			bitmapInfoHeader.imageSize);

	// verify memory allocation
	if (!bitmapImage) {
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	size_t i;
	uint16_t garbage;
	if ((bitmapInfoHeader.width % 2) != 0)
	{
		for (i = 0; i < bitmapInfoHeader.height; ++i)
		{
			fread((uint16_t *)bitmapImage + i * bitmapInfoHeader.width, bitmapInfoHeader.width * bitmapInfoHeader.bits / 8, 1, filePtr);
			fread(&garbage, 2, 1, filePtr);
		}
	}
	else
	{
		fread(bitmapImage, bitmapInfoHeader.imageSize, 1, filePtr);
	}

	// make sure bitmap image data was read
	if (bitmapImage == NULL) {
		fclose(filePtr);
		return NULL;
	}

	// close file and return bitmap image data
	fclose(filePtr);

	bmp->bitmapData = bitmapImage;
	bmp->bitmapInfoHeader = bitmapInfoHeader;

	return bmp;
}

void drawMouse(Bitmap* bmp, int x, int y, Alignment alignment, char * buffer) {
	if (bmp == NULL)
		return;

	int width = bmp->bitmapInfoHeader.width;
	int drawWidth = width;
	int height = bmp->bitmapInfoHeader.height;

	if (alignment == ALIGN_CENTER)
		x -= width / 2;
	else if (alignment == ALIGN_RIGHT)
		x -= width;

	if (x + width < 0 || x > H_RES || y + height < 0
			|| y > V_RES)
		return;

	int xCorrection = 0;
	if (x < 0) {
		xCorrection = -x;
		drawWidth -= xCorrection;
		x = 0;

		if (drawWidth > H_RES)
			drawWidth = H_RES;
	} else if (x + drawWidth >= H_RES) {
		drawWidth = H_RES - x;
	}

	char* bufferStartPos;
	char* imgStartPos;

	int i;
	for (i = 0; i < height; i++) {
		int pos = y + height - 1 - i;

		if (pos < 0 || pos >= V_RES)
			continue;

		bufferStartPos = buffer;
		bufferStartPos += x * 2 + pos * H_RES * 2;

		imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;
		unsigned int k = 0;
		for (k; k < drawWidth; k++)
		{
			if (*(uint16_t *)imgStartPos == 0x7E0)
			{

			}
			else
			{
				memcpy(bufferStartPos, imgStartPos, 2);
			}
			bufferStartPos += 2;
			imgStartPos += 2;
		}
	}
}

void drawBitmap(Bitmap* bmp, int x, int y, Alignment alignment, char * buffer)
{
	if (bmp == NULL)
		return;

	int width = bmp->bitmapInfoHeader.width;
	int drawWidth = width;
	int height = bmp->bitmapInfoHeader.height;

	if (alignment == ALIGN_CENTER)
		x -= width / 2;
	else if (alignment == ALIGN_RIGHT)
		x -= width;

	if (x + width < 0 || x > H_RES || y + height < 0
			|| y > V_RES)
		return;

	int xCorrection = 0;
	if (x < 0) {
		xCorrection = -x;
		drawWidth -= xCorrection;
		x = 0;

		if (drawWidth > H_RES)
			drawWidth = H_RES;
	} else if (x + drawWidth >= H_RES) {
		drawWidth = H_RES - x;
	}

	char* bufferStartPos;
	char* imgStartPos;

	int i;
	for (i = 0; i < height; i++) {
		int pos = y + height - 1 - i;

		if (pos < 0 || pos >= V_RES)
			continue;

		bufferStartPos = buffer;
		bufferStartPos += x * 2 + pos * H_RES * 2;

		imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;
		memcpy(bufferStartPos, imgStartPos, drawWidth * 2);
	}
}

void deleteBitmap(Bitmap* bmp) {
	if (bmp == NULL)
		return;

	free(bmp->bitmapData);
	free(bmp);
}
