#include "read_write.h"

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
	t->hour = (ch1 - '0') * 10 + (ch2 - '0');

	// ignores the space ' '
	ch1 = fgetc(fp);

	//minutes
	ch1 = fgetc(fp);
	ch2 = fgetc(fp);
	t->minutes = (ch1 - '0') * 10 + (ch2 - '0');

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
		i++;
	}

	// the new line '\n' is already ignored

	//word
	char b[11];
	fgets(b, 11, fp);
	i = 0;
	while (b[i] != '\0')
	{
		(t->word)[i] = b[i];
		i++;
	}

	// the new line '\n' is already ignored
}

void read_all()
{
	FILE *fp;

	fp = fopen("home/lcom/proj/code/files/scores.txt","r");

	if( fp == NULL )
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	read_position(fp, &(top_highscores.first));
	read_position(fp, &(top_highscores.second));
	read_position(fp, &(top_highscores.third));
	read_position(fp, &(top_highscores.fourth));
	read_position(fp, &(top_highscores.fifth));

	fclose(fp);
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
	else if (t->score >= 10)
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
	//fputc('\n', fp);

	//word
	fputs(t->word, fp);
	//fputc('\n', fp);
}

void write_all()
{
	FILE *fp;

	fp = fopen("home/lcom/proj/code/files/scores.txt","w");

	if( fp == NULL )
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	write_position(fp, &(top_highscores.first));
	write_position(fp, &(top_highscores.second));
	write_position(fp, &(top_highscores.third));
	write_position(fp, &(top_highscores.fourth));
	write_position(fp, &(top_highscores.fifth));

	fclose(fp);
}
