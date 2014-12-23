#ifndef __STRUCT_SCORES_H
#define __STRUCT_SCORES_H

#define MAX_DRAW_SIZE			999

typedef struct
{
	char day;
	char month;
	char year;
	char hour;
	char minutes;

	int score;

	char name[11];

	char word[11];


} position_t;

typedef struct
{
	position_t first;
	position_t second;
	position_t third;
	position_t fourth;
	position_t fifth;

} scores_t;


#endif
