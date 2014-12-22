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
			screen_buffer = screen_buffer + yi * 2 + 1024 * xi * 2;
			*(uint16_t *)screen_buffer = colour;
		}
		else
		{
			screen_buffer = getScreenBuffer();
			screen_buffer = screen_buffer + xi * 2 + 1024 * yi * 2;
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
		screen_buffer += (x + x0)* 2 + (y + y0) * 1024 * 2;
		if ( (x + x0 > 1020) || (y + y0 < 120) || (x + x0 > 717) || (y + y0 < 183) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;



		screen_buffer = getScreenBuffer();
		screen_buffer += (y + x0)* 2 + (x + y0) * 1024 * 2;
		if ( (y + x0 > 1020) || (y + x0 < 120) || (x + y0 > 717) || (x + y0 < 187) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (-x + x0)* 2 + (y + y0) * 1024 * 2;
		if ( (-x + x0 > 1020) || (-x + x0 < 120) || (y + y0 > 717) || (y + y0 < 187) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (-y + x0)* 2 + (x + y0) * 1024 * 2;
		if ( (-y + x0 > 1020) || (-y + x0 < 120) || (x + y0 > 717) || (x + y0 < 187) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (-x + x0)* 2 + (-y + y0) * 1024 * 2;
		if ( (-x + x0 > 1020) || (-x + x0 < 120) || (-y + y0 > 717) || (-y + y0 < 187) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (-y + x0)* 2 + (-x + y0) * 1024 * 2;
		if ( (-y + x0 > 1020) || (-y + x0 < 120) || (-x + y0 > 717) || (-x + y0 < 187) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (x + x0)* 2 + (-y + y0) * 1024 * 2;
		if ( (x + x0 > 1020) || (x + x0 < 120) || (-y + y0 > 717) || (-y + y0 < 187) )
		{

		}
		else *(uint16_t *)screen_buffer = colour;

		screen_buffer = getScreenBuffer();
		screen_buffer += (y + x0)* 2 + (-x + y0) * 1024 * 2;
		if ( (y + x0 > 1020) || (y + x0 < 120) || (-x + y0 > 717) || (-x + y0 < 187) )
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
			screen_buffer += i * 2 +(y0 +y) * 1024 * 2;
			if ( (i < 120) || (i > 1020) || (y0 + y < 187) || (y0 + y > 717) )
			{

			}
			else *(uint16_t *)screen_buffer = colour;

			screen_buffer = getScreenBuffer();
			screen_buffer += i * 2 +(y0 -y) * 1024 * 2;
			if ( (i < 120) || (i > 1020) || (y0 - y < 187) || (y0 - y > 717) )
			{

			}
			else *(uint16_t *)screen_buffer = colour;
		}

		for (i = x0 -y; i <= x0 +y; i++)
		{
			screen_buffer = getScreenBuffer();
			screen_buffer += i * 2 +(y0 +x) * 1024 * 2;
			if ( (i < 120) || (i > 1020) || (y0 + x < 187) || (y0 + x > 717) )
			{

			}
			else *(uint16_t *)screen_buffer = colour;

			screen_buffer = getScreenBuffer();
			screen_buffer += i * 2 +(y0 -x) * 1024 * 2;
			if ( (i < 120) || (i > 1020) || (y0 - x < 187) || (y0 - x > 717) )
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
	if (x - radius < 120)
	{
		xi = 120 - (x - radius);
	}

	if (x + radius > 1020)
	{
		xi = x + radius - 1020;
	}

	if (y - radius < 183)
	{
		yi = 183 - (y - radius);
	}

	if (y + radius > 717)
	{
		yi = y + radius - 717;
	}
	 */
	char * screen_buffer = getScreenBuffer() + (x * 2) + (1024 * y) * 2;
	screen_buffer = screen_buffer - (radius * 2) - (1024 * radius) * 2;
	unsigned int i = 0;
	unsigned int j = 0;
	int size = radius * 2;

	for (; i < size; i++)
	{
		for (; j < size; j++)
		{
			if ((x - radius + j > 1020) || (x - radius + j < 120) || (y - radius + i > 717) || (y - radius + i < 187))
			{

			}
			else *(uint16_t *)screen_buffer = colour;
			screen_buffer+=2;
		}
		j = 0;
		screen_buffer+= 1024 * 2 - size * 2;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void undo()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void redo()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void plus()
{
	radius = radius + 5;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// NEEDS TO BE MADE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void minus()
{
	if ((radius - 5) < 3)
	{
		radius = 3;
	}
	radius = radius - 5;
}

void draw_bucket()
{
	char * screen_buffer = getScreenBuffer() + mouse_t.x_mouse * 2 + mouse_t.y_mouse * 2 * 1024;

	int cor = *(uint16_t *)screen_buffer;

	screen_buffer = getScreenBuffer() + 120 * 2 + 1024 * 183 * 2;

	unsigned int i;
	unsigned int j;
	char bool = 1;
	for (j = 183; j < 717; j++)
	{
		for (i = 120; i < 1020; i++)
		{
			if (cor == *(uint16_t *)screen_buffer)
			{
				bool = 0;
				*(uint16_t *)screen_buffer = colour;
			}
			screen_buffer+=2;
		}
		i = 0;
		screen_buffer = screen_buffer + 1024 * 2 - (1020 - 120) * 2;
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
	static mouse_st previous_before;
	/*
static mouse_st previous_after;
	static int flag;

	if (flag == 0)
	{
		flag = 1;
		previous_before.LB = 0;
		previous_after = mouse_t;
	}

	if ((previous_before.LB == 1) && (previous_after.LB == 0) && (mouse_t.LB == 1))
	{
		draw_line(previous_before);
		previous_before = previous_after;
		previous_after = mouse_t;
	}
	else if ( (previous_before.LB == 0) && (previous_after.LB == 1) && (mouse_t.LB == 1) )
	{
		previous_after = mouse_t;
	}
	else if ( (previous_before.LB == 1) && (previous_after.LB == 1) && (mouse_t.LB == 0) )
	{
		previous_before = previous_after;
		previous_after = mouse_t;
	}
	 */
	static int flag;
	if (flag == 0)
	{
		flag = 1;
		previous_before = mouse_t;
	}
	else
	{
		draw_line(previous_before);
		previous_before = mouse_t;
	}

}
