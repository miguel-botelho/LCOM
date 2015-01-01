#include "frame.h"

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void draw_line(mouse_st previous)
{

	long dx,dy;
	char * screen_buffer;
	int d,incry,incre,incrne,slopegt1=0;
	int temp;
	int xi = previous.x_mouse;
	int yi = previous.y_mouse;
	int xf = mouse_t.x_mouse;
	int yf = mouse_t.y_mouse;

	dx=abs(xi-xf);dy=abs(yi-yf);
	if(dy>dx)
	{
		temp = xi;
		xi = yi;
		yi = temp;
		//swap(&xi,&yi);
		temp = xf;
		xf = yf;
		yf = temp;
		//swap(&xf,&yf);
		temp = dx;
		dx = dy;
		dy = temp;
		//swap(&dx,&dy);
		slopegt1=1;
	}
	if(xi>xf)
	{
		temp = xi;
		xi = xf;
		xf = temp;
		//swap(&xi,&xf);
		temp = yi;
		yi = yf;
		yf = temp;
		//swap(&yi,&yf);
	}
	if(yi>yf)
		incry=-1;
	else
		incry=1;
	d=2*dy-dx;
	incre=2*dy;
	incrne=2*(dy-dx);
	while(xi<xf)
	{
		if(d<=0)
			d+=incre;
		else
		{
			d+=incrne;
			yi+=incry;
		}
		xi++;
		if(slopegt1)
		{
			screen_buffer = getScreenBuffer();
			screen_buffer = screen_buffer + yi * 2 + getHRes() * xi * 2;
			*(uint16_t *)screen_buffer = colour;
		}
		else
		{
			screen_buffer = getScreenBuffer();
			screen_buffer = screen_buffer + xi * 2 + getHRes() * yi * 2;
			*(uint16_t *)screen_buffer = colour;
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void draw_brush()
{
	int x = radius;
	if (x > 15)
		x = 15;
	int y = 0;
	int x0 = mouse_t.x_mouse;
	int y0 = mouse_t.y_mouse;

	int radiusError = 1-x;
	char * screen_buffer = getScreenBuffer();

	while ( x >= y)
	{
		screen_buffer = getScreenBuffer();
		screen_buffer += (x + x0)* 2 + (y + y0) * getHRes() * 2;
		if ( (x + x0 > CANVAS_X_F) || (y + y0 < CANVAS_X_I) || (x + x0 > CANVAS_Y_F) || (y + y0 < CANVAS_Y_I) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;



		screen_buffer = getScreenBuffer();
		screen_buffer += (y + x0)* 2 + (x + y0) * getHRes() * 2;
		if ( (y + x0 > CANVAS_X_F) || (y + x0 < CANVAS_X_I) || (x + y0 > CANVAS_Y_F) || (x + y0 < CANVAS_Y_I) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (-x + x0)* 2 + (y + y0) * getHRes() * 2;
		if ( (-x + x0 > CANVAS_X_F) || (-x + x0 < CANVAS_X_I) || (y + y0 > CANVAS_Y_F) || (y + y0 < CANVAS_Y_I) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (-y + x0)* 2 + (x + y0) * getHRes() * 2;
		if ( (-y + x0 > CANVAS_X_F) || (-y + x0 < CANVAS_X_I) || (x + y0 > CANVAS_Y_F) || (x + y0 < CANVAS_Y_I) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (-x + x0)* 2 + (-y + y0) * getHRes() * 2;
		if ( (-x + x0 > CANVAS_X_F) || (-x + x0 < CANVAS_X_I) || (-y + y0 > CANVAS_Y_F) || (-y + y0 < CANVAS_Y_I) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (-y + x0)* 2 + (-x + y0) * getHRes() * 2;
		if ( (-y + x0 > CANVAS_X_F) || (-y + x0 < CANVAS_X_I) || (-x + y0 > CANVAS_Y_F) || (-x + y0 < CANVAS_Y_I) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (x + x0)* 2 + (-y + y0) * getHRes() * 2;
		if ( (x + x0 > CANVAS_X_F) || (x + x0 < CANVAS_X_I) || (-y + y0 > CANVAS_Y_F) || (-y + y0 < CANVAS_Y_I) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (y + x0)* 2 + (-x + y0) * getHRes() * 2;
		if ( (y + x0 > CANVAS_X_F) || (y + x0 < CANVAS_X_I) || (-x + y0 > CANVAS_Y_F) || (-x + y0 < CANVAS_Y_I) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		y++;

		if (radiusError < 0)
		{
			radiusError += 2 * y + 1;
		}
		else
		{
			x--;
			radiusError += 2 * y + 1;
		}
	}
}

void draw_circle()
{
	int x0 = mouse_t.x_mouse;
	int y0 = mouse_t.y_mouse;
	int x = radius;
	int y = 0;
	int xChange = 1 - (radius << 1);
	int yChange = 0;
	int radiusError = 0;
	char * screen_buffer;

	while (x >= y)
	{
		int i;
		for (i = x0 - x; i <= x0 +x; i++)
		{
			screen_buffer = getScreenBuffer();
			screen_buffer += i * 2 +(y0 +y) * getHRes() * 2;
			if ( (i < CANVAS_X_I) || (i > CANVAS_X_F) || (y0 + y < CANVAS_Y_I) || (y0 + y > CANVAS_Y_F) )
			{

			}
			else *(uint16_t *)screen_buffer = colour;

			screen_buffer = getScreenBuffer();
			screen_buffer += i * 2 +(y0 -y) * getHRes() * 2;
			if ( (i < CANVAS_X_I) || (i > CANVAS_X_F) || (y0 - y < CANVAS_Y_I) || (y0 - y > CANVAS_Y_F) )
			{

			}
			else *(uint16_t *)screen_buffer = colour;
		}

		for (i = x0 -y; i <= x0 +y; i++)
		{
			screen_buffer = getScreenBuffer();
			screen_buffer += i * 2 +(y0 +x) * getHRes() * 2;
			if ( (i < CANVAS_X_I) || (i > CANVAS_X_F) || (y0 + x < CANVAS_Y_I) || (y0 + x > CANVAS_Y_F) )
			{

			}
			else *(uint16_t *)screen_buffer = colour;

			screen_buffer = getScreenBuffer();
			screen_buffer += i * 2 +(y0 -x) * getHRes() * 2;
			if ( (i < CANVAS_X_I) || (i > CANVAS_X_F) || (y0 - x < CANVAS_Y_I) || (y0 - x > CANVAS_Y_F) )
			{

			}
			else *(uint16_t *)screen_buffer = colour;
		}

		y++;

		radiusError += yChange;
		yChange += 2;

		if (((radiusError << 1) + xChange) > 0)
		{
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void draw_square()
{
	int x = mouse_t.x_mouse;
	int y = mouse_t.y_mouse;
	/*
	if (x - radius < CANVAS_X_I)
	{
		xi = CANVAS_X_I - (x - radius);
	}

	if (x + radius > CANVAS_X_F)
	{
		xi = x + radius - CANVAS_X_F;
	}

	if (y - radius < CANVAS_Y_I)
	{
		yi = CANVAS_Y_I - (y - radius);
	}

	if (y + radius > CANVAS_Y_F)
	{
		yi = y + radius - CANVAS_Y_F;
	}
	 */
	char * screen_buffer = getScreenBuffer() + (x * 2) + (getHRes() * y) * 2;
	screen_buffer = screen_buffer - (radius * 2) - (getHRes() * radius) * 2;
	unsigned int i = 0;
	unsigned int j = 0;
	int size = radius * 2;

	for (; i < size; i++)
	{
		for (; j < size; j++)
		{
			if ((x - radius + j > CANVAS_X_F) || (x - radius + j < CANVAS_X_I) || (y - radius + i > CANVAS_Y_F) || (y - radius + i < CANVAS_Y_I))
			{

			}
			else *(uint16_t *)screen_buffer = colour;
			screen_buffer+=2;
		}
		j = 0;
		screen_buffer+= getHRes() * 2 - size * 2;
	}
}

void undo()
{
	char a[] = "home/lcom/proj/code/files/d0.bmp";

	if ((screen_current - 1) <= 0)
	{
		white_screen();
	}
	else
	{
		a[NUMBER_TO_CHANGE] = screen_current + '0';
		screen_current--;
		printf("Undo: screen_current=%d | screen_abs=%d\n", screen_current, screen_abs);
		printf("Path Undo: %s\n", a);
		drawBitmap(loadBitmap(a), CANVAS_X_I, CANVAS_Y_I, ALIGN_LEFT, getScreenBuffer());
	}
}

void redo()
{
	char a[] = "home/lcom/proj/code/files/d0.bmp";

	if (screen_current >= screen_abs)
	{
		screen_current = screen_abs;
	}
	else
	{
		screen_current++;
		a[NUMBER_TO_CHANGE] = screen_current + '0';
		printf("Redo: screen_current=%d | screen_abs=%d\n", screen_current, screen_abs);
		printf("Path Redo: %s\n", a);
		drawBitmap(loadBitmap(a), CANVAS_X_I, CANVAS_Y_I, ALIGN_LEFT, getScreenBuffer());
	}
}

void plus()
{
	if (radius > MAX_RADIUS)
	{
		radius = MAX_RADIUS;
	}
	else
	{
		radius = radius + RADIUS_INC;
	}
}

void minus()
{
	if ((radius - MIN_RADIUS) <= MIN_RADIUS)
	{
		radius = MIN_RADIUS;
	}
	radius = radius - RADIUS_INC;
}

void draw_bucket()
{
	char * screen_buffer = getScreenBuffer() + mouse_t.x_mouse * 2 + mouse_t.y_mouse * 2 * getHRes();

	int cor = *(uint16_t *)screen_buffer;

	screen_buffer = getScreenBuffer() + CANVAS_X_I * 2 + getHRes() * CANVAS_Y_I * 2;

	unsigned int i;
	unsigned int j;
	char bool = 1;
	for (j = CANVAS_Y_I; j < CANVAS_Y_F; j++)
	{
		for (i = CANVAS_X_I; i < CANVAS_X_F; i++)
		{
			if (cor == *(uint16_t *)screen_buffer)
			{
				bool = 0;
				*(uint16_t *)screen_buffer = colour;
			}
			screen_buffer+=2;
		}
		i = 0;
		screen_buffer = screen_buffer + getHRes() * 2 - (CANVAS_X_F - CANVAS_X_I) * 2;
	}
}

void drawLINE()
{
	static mouse_st previous_before;
	static mouse_st previous_after;
	static int flag;
	if (flag == 0)
	{
		flag = 1;
		previous_before.LB = 0;
		previous_after.LB = 0;
	}

	if ((previous_before.LB == 0) && (previous_after.LB == 0))
	{
		if (mouse_t.LB == 1)
		{
			previous_after = mouse_t;
		}
	}
	else if ((previous_before.LB == 0) && (previous_after.LB == 1))
	{
		if (mouse_t.LB == 1)
		{
			previous_before = previous_after;
			previous_after = mouse_t;
		}
		else
		{
			previous_before = previous_after;
			previous_after = mouse_t;
		}
	}
	else if ((previous_before.LB == 1) && (previous_after.LB == 1))
	{
		if (mouse_t.LB == 0)
		{
			previous_before.LB = 0;
			previous_after.LB = 0;
		}
	}
	else if ((previous_before.LB == 1) && (previous_after.LB == 0))
	{
		if (mouse_t.LB == 1)
		{
			draw_line(previous_before);
			previous_before.LB = 0;
			previous_after.LB = 0;
		}
	}

}

void draw_pencil()
{
	static mouse_st previous;
	static int flag;

	if (flag == 0)
	{
		flag = 1;
		previous.LB = 0;
	}

	if (previous.LB == 0)
	{
		if (mouse_t.LB == 1)
		{
			previous = mouse_t;
			draw_line(previous);
		}
	}
	else
	{
		if (mouse_t.LB == 1)
		{
			draw_line(previous);
			previous = mouse_t;
		}
		else
		{
			previous = mouse_t;
		}
	}
}

void white_screen()
{
	char * screen_buffer = getScreenBuffer();

	screen_buffer = screen_buffer + CANVAS_X_I * 2 + CANVAS_Y_I * 2 * getHRes();

	unsigned int i = 0;
	unsigned int j = 0;


	for(; i < CANVAS_Y_F - CANVAS_Y_I; i++)
	{
		for (; j < CANVAS_X_F - CANVAS_X_I; j++)
		{
			*(uint16_t *) screen_buffer = WHITE;
			screen_buffer+=2;
		}
		j = 0;
		screen_buffer = screen_buffer - (CANVAS_X_F - CANVAS_X_I) * 2 + getHRes() * 2;
	}
}

void paintWhiteCanvas(int xi, int xf, int yi, int yf)
{
	char * screen_buffer = getScreenBuffer();
	screen_buffer = screen_buffer + xi * 2 + yi * 2 * getHRes();

	unsigned int i = 0;
	unsigned int j = 0;

	for(; j < yf - yi; j++)
	{
		for (; i < xf - xi; i++)
		{
			*(uint16_t *) screen_buffer = WHITE;
			screen_buffer+=2;
		}
		i = 0;
		screen_buffer = screen_buffer - (xf - xi) * 2 + getHRes() * 2;
	}
}
