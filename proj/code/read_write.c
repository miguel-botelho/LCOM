#include "read_write.h"

void read_array(FILE *fp, int size, color_st *a)
{
	char x[1];
	char ch1, ch2, ch3, ch4;

	a = (color_st*) realloc (x, size * sizeof(color_st));

	int i;

	for (i = 0; i < size; i++)
	{
		//tick
		ch1 = fgetc(fp);
		ch2 = fgetc(fp);
		ch3 = fgetc(fp);
		ch4 = fgetc(fp);
		a[i].tick = (ch1 - '0') * 1000 + (ch2 - '0') * 100 + (ch3 - '0') * 10 + (ch4 - '0');

		// ignores the new line '\n'
		ch1 = fgetc(fp);

		//red
		ch1 = fgetc(fp);
		ch2 = fgetc(fp);
		ch3 = fgetc(fp);
		a[i].red = (ch1 - '0') * 100 + (ch2 - '0') * 10 + (ch3 - '0');

		// ignores the space ' '
		ch1 = fgetc(fp);

		//green
		ch1 = fgetc(fp);
		ch2 = fgetc(fp);
		ch3 = fgetc(fp);
		a[i].green = (ch1 - '0') * 100 + (ch2 - '0') * 10 + (ch3 - '0');

		// ignores the space ' '
		ch1 = fgetc(fp);

		//blue
		ch1 = fgetc(fp);
		ch2 = fgetc(fp);
		ch3 = fgetc(fp);
		a[i].blue = (ch1 - '0') * 100 + (ch2 - '0') * 10 + (ch3 - '0');

		// ignores the new line '\n'
		ch1 = fgetc(fp);
	}
}

void read_position(FILE *fp, position_t *t)
{
	char ch1, ch2, ch3, ch4, ch5;

	//day
	ch1 = fgetc(fp);
	ch2 = fgetc(fp);
	t->day = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the space ' '
	ch1 = fgetc(fp);

	//month
	ch1 = fgetc(fp);
	ch2 = fgetc(fp);
	t->month = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the space ' '
	ch1 = fgetc(fp);

	//year
	ch1 = fgetc(fp);
	ch2 = fgetc(fp);
	t->year = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the space ' '
	ch1 = fgetc(fp);

	//hour
	ch1 = fgetc(fp);
	ch2 = fgetc(fp);
	t->year = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the space ' '
	ch1 = fgetc(fp);

	//minutes
	ch1 = fgetc(fp);
	ch2 = fgetc(fp);
	t->year = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the new line '\n'
	ch1 = fgetc(fp);

	//reads the score (max value = 11500)
	ch1 = fgetc(fp);
	ch2 = fgetc(fp);
	ch3 = fgetc(fp);
	ch4 = fgetc(fp);
	ch5 = fgetc(fp);
	t->score = (ch1 - '0') * 10000 + (ch2 - '0') * 1000 + (ch3 - '0') * 100 + (ch4 - '0') * 10 + (ch5 - '0');

	// ignores the new line '\n'
	ch1 = fgetc(fp);

	//name
	char a[11];
	fgets(a, 11, fp);
	int i = 0;
	while (a[i] != '\0')
	{
		(t->name)[i] = a[i];
	}

	// the new line '\n' is already ignored

	//reads the size of the array (max value = 3600)
	ch1 = fgetc(fp);
	ch2 = fgetc(fp);
	ch3 = fgetc(fp);
	ch4 = fgetc(fp);
	t->size_draw = (ch1 - '0') * 1000 + (ch2 - '0') * 100 + (ch3 - '0') * 10 + (ch4 - '0');

	// ignores the new line '\n'
	ch1 = fgetc(fp);

	//reads the array
	read_array(fp, t->size_draw, t->draw);
}

void read_all(scores_t *t)
{
	FILE *fp;

	fp = fopen("home/lcom/proj/code/files/scores.txt","r");

	if( fp == NULL )
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	read_position(fp, &(t->first));
	read_position(fp, &(t->second));
	read_position(fp, &(t->third));
	read_position(fp, &(t->fourth));
	read_position(fp, &(t->fifth));

	fclose(fp);
}


void write_array(FILE *fp, int size, color_st *a)
{
	int i;

	for (i = 0; i < size; i++)
	{
		//tick
		if (a->tick >= 1000)
		{
			fputc((a->tick / 1000) + '0', fp);
			fputc((a->tick / 100) % 10 + '0', fp);
			fputc((a->tick / 10) % 10 + '0', fp);
			fputc((a->tick) % 10 + '0', fp);
		}
		else if (a->tick >= 100)
		{
			fputc('0', fp);
			fputc((a->tick / 100) % 10 + '0', fp);
			fputc((a->tick / 10) % 10 + '0', fp);
			fputc((a->tick) % 10 + '0', fp);
		}
		else if (a->tick >= 10)
		{
			fputc('0', fp);
			fputc('0', fp);
			fputc((a->tick / 10) % 10 + '0', fp);
			fputc((a->tick) % 10 + '0', fp);
		}
		else
		{
			fputc('0', fp);
			fputc('0', fp);
			fputc('0', fp);
			fputc((a->tick) % 10 + '0', fp);
		}
		fputc('\n', fp);

		//red
		if (a->red >= 100)
		{
			fputc((a->red / 100) % 10 + '0', fp);
			fputc((a->red / 10) % 10 + '0', fp);
			fputc((a->red) % 10 + '0', fp);
		}
		else if (a->red >= 10)
		{
			fputc('0', fp);
			fputc((a->red / 10) % 10 + '0', fp);
			fputc((a->red) % 10 + '0', fp);
		}
		else
		{
			fputc('0', fp);
			fputc('0', fp);
			fputc((a->red) % 10 + '0', fp);
		}
		fputc(' ', fp);

		//green
		if (a->green >= 100)
		{
			fputc((a->green / 100) % 10 + '0', fp);
			fputc((a->green / 10) % 10 + '0', fp);
			fputc((a->green) % 10 + '0', fp);
		}
		else if (a->green >= 10)
		{
			fputc('0', fp);
			fputc((a->green / 10) % 10 + '0', fp);
			fputc((a->green) % 10 + '0', fp);
		}
		else
		{
			fputc('0', fp);
			fputc('0', fp);
			fputc((a->green) % 10 + '0', fp);
		}
		fputc(' ', fp);

		//blue
		if (a->blue >= 100)
		{
			fputc((a->blue / 100) % 10 + '0', fp);
			fputc((a->blue / 10) % 10 + '0', fp);
			fputc((a->blue) % 10 + '0', fp);
		}
		else if (a->blue >= 10)
		{
			fputc('0', fp);
			fputc((a->blue / 10) % 10 + '0', fp);
			fputc((a->blue) % 10 + '0', fp);
		}
		else
		{
			fputc('0', fp);
			fputc('0', fp);
			fputc((a->blue) % 10 + '0', fp);
		}
		fputc('\n', fp);
	}

}

void write_position(FILE *fp, position_t *t)
{
	//day
	if (t->day < 10)
	{
		fputc('0', fp);
		fputc(t->day + '0', fp);
	}
	else
	{
		fputc((t->day / 10) + '0', fp);
		fputc((t->day % 10) + '0', fp);
	}
	fputc(' ', fp);

	//month
	if (t->month < 10)
	{
		fputc('0', fp);
		fputc(t->month + '0', fp);
	}
	else
	{
		fputc((t->month / 10) + '0', fp);
		fputc((t->month % 10) + '0', fp);
	}
	fputc(' ', fp);

	//year
	if (t->year < 10)
	{
		fputc('0', fp);
		fputc(t->year + '0', fp);
	}
	else
	{
		fputc((t->year / 10) + '0', fp);
		fputc((t->year % 10) + '0', fp);
	}
	fputc(' ', fp);

	//hour
	if (t->hour < 10)
	{
		fputc('0', fp);
		fputc(t->hour + '0', fp);
	}
	else
	{
		fputc((t->hour / 10) + '0', fp);
		fputc((t->hour % 10) + '0', fp);
	}
	fputc(' ', fp);

	//minutes
	if (t->minutes < 10)
	{
		fputc('0', fp);
		fputc(t->minutes + '0', fp);
	}
	else
	{
		fputc((t->minutes / 10) + '0', fp);
		fputc((t->minutes % 10) + '0', fp);
	}
	fputc('\n', fp);

	//score
	if (t->score >= 10000)
	{
		fputc((t->score / 10000) + '0', fp);
		fputc((t->score / 1000) % 10 + '0', fp);
		fputc((t->score / 100) % 10 + '0', fp);
		fputc((t->score / 10) % 10 + '0', fp);
		fputc((t->score) % 10 + '0', fp);
	}
	else if (t->score >= 1000)
	{
		fputc('0', fp);
		fputc((t->score / 1000) + '0', fp);
		fputc((t->score / 100) % 10 + '0', fp);
		fputc((t->score / 10) % 10 + '0', fp);
		fputc((t->score) % 10 + '0', fp);
	}
	else if (t->score >= 100)
	{
		fputc('0', fp);
		fputc('0', fp);
		fputc((t->score / 100) + '0', fp);
		fputc((t->score / 10) % 10 + '0', fp);
		fputc((t->score) % 10 + '0', fp);
	}
	else if (t->size_draw >= 10)
	{
		fputc('0', fp);
		fputc('0', fp);
		fputc('0', fp);
		fputc((t->score / 10) + '0', fp);
		fputc((t->score) % 10 + '0', fp);
	}
	else
	{
		fputc('0', fp);
		fputc('0', fp);
		fputc('0', fp);
		fputc('0', fp);
		fputc((t->score) % 10 + '0', fp);
	}
	fputc('\n', fp);

	//name
	fputs(t->name, fp);
	fputc('\n', fp);

	//size of the array
	if (t->size_draw >= 1000)
	{
		fputc((t->size_draw / 1000) + '0', fp);
		fputc((t->size_draw / 100) % 10 + '0', fp);
		fputc((t->size_draw / 10) % 10 + '0', fp);
		fputc((t->size_draw) % 10 + '0', fp);
	}
	else if (t->size_draw >= 100)
	{
		fputc('0', fp);
		fputc((t->size_draw / 100) + '0', fp);
		fputc((t->size_draw / 10) % 10 + '0', fp);
		fputc((t->size_draw) % 10 + '0', fp);
	}
	else if (t->size_draw >= 10)
	{
		fputc('0', fp);
		fputc('0', fp);
		fputc((t->size_draw / 10) + '0', fp);
		fputc((t->size_draw) % 10 + '0', fp);
	}
	else
	{
		fputc('0', fp);
		fputc('0', fp);
		fputc('0', fp);
		fputc((t->size_draw) % 10 + '0', fp);
	}
	fputc('\n', fp);

	write_array(fp, t->size_draw, t->draw);

}

void write_all(scores_t *t)
{
	FILE *fp;

	fp = fopen("home/lcom/proj/code/files/scores.txt","w");

	if( fp == NULL )
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	write_position(fp, &(t->first));
	write_position(fp, &(t->second));
	write_position(fp, &(t->third));
	write_position(fp, &(t->fourth));
	write_position(fp, &(t->fifth));

	fclose(fp);
}
