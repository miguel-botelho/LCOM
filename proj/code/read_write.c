#include "read_write.h"

void read_array(FILE *fp, int size, char *a)
{
	//needs to be made
}

void read_position(FILE *fp, position_t *t)
{
	char ch1, ch2, ch3, ch4;

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

	//name
	char *a;
	fgets(a, 11, fp);
	int i = 0;
	while (i < 10)
	{
		(t->name)[i] = a[i];
	}

	// the new line '\n' is already ignored

	//reads the size of the array (max value = 3600)
	ch1 = fgetc(fp);
	ch2 = fgetc(fp);
	ch3 = fgetc(fp);
	ch4 = fgetc(fp);
	t->size_draw = (ch1 - '0') * 1000 + (ch1 - '0') * 100 + (ch1 - '0') * 10 + (ch2 - '0');

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
	read_position(fp, &(t->forth));
	read_position(fp, &(t->fifth));

	fclose(fp);
}


void write_array(FILE *fp, int size, char *a)
{
	//needs to be made
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
	write_position(fp, &(t->forth));
	write_position(fp, &(t->fifth));

	fclose(fp);
}