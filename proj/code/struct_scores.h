#ifndef __STRUCT_SCORES_H
#define __STRUCT_SCORES_H

typedef struct
{
	char day;
	char month;
	char year;
	char hour;
	char minutes;

	int score;

	char name[11];

	int size_draw;
	char *draw;


} position_t;

typedef struct
{
	position_t first;
	position_t second;
	position_t third;
	position_t forth;
	position_t fifth;

} scores_t;


#endif
