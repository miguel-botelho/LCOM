#include "menu.h"

void bitmaps_load(bitmap_struct *t)
{
	t->background = loadBitmap("home/lcom/proj/code/images/Fundo.bmp");
	t->highscores = loadBitmap("home/lcom/proj/code/images/Highscores.bmp");
	t->mouse = loadBitmap("home/lcom/proj/code/images/Mouse.bmp");
	t->frame = loadBitmap("home/lcom/proj/code/images/Frame_test.bmp");
	t->pre_head_to_head = loadBitmap("home/lcom/proj/code/images/Pre-Head_to_Head.bmp");
	t->lost = loadBitmap("home/lcom/proj/code/images/Lost.bmp");
	t->win = loadBitmap("home/lcom/proj/code/images/Win.bmp");
}

int exit_menu(bitmap_struct bitmaps)
{
	deleteBitmap(bitmaps.background);
	deleteBitmap(bitmaps.mouse);
	deleteBitmap(bitmaps.frame);
	vg_exit();

	//estas duas opearacoes sao feitas para assegurar o normal funcionamento do rato quando acabar a funcao
	mouse_int_handler(DISABLE_STREAM); //desativa a stream
	mouse_int_handler(SET_STREAM); //volta a ativar a stream, isto foi feito para desativar o envio dos pacotes

	if (unsubscribe_all() == -1)
	{
		printf("Failure to unsubscribe!! \n\n");
		return -1;
	}
	return 0;
}

char position_menu(bitmap_struct bitmaps)
{
	char bool = 1;

	if ((mouse_t.x_mouse >= 438) && (mouse_t.x_mouse <= 591))
	{
		if ((mouse_t.y_mouse >= 650) && (mouse_t.y_mouse <= 716))
		{
			bool = 0;
			if (mouse_t.LB == 1)
			{
				OPTION = EXIT_OPT;
				if (0 == exit_menu(bitmaps))
					return 0;
				else return 1;
			}
			else
			{
				change_color(438, 591, 650, 716, BLACK, RED, getScreenBuffer());
			}
		}
	}

	if ((mouse_t.x_mouse >= 305) && (mouse_t.x_mouse <= 718))
	{
		if ((mouse_t.y_mouse >= 555) && (mouse_t.y_mouse <= 644))
		{
			bool = 0;
			if (mouse_t.LB == 1)
			{
				OPTION = HIGHSCORES;
				//exit_menu(bitmaps);
				HighScores_menu(bitmaps); //not done
				//funcao HighScores
			}
			else
			{
				change_color(305, 718, 555, 644, rgb(99,93,8), RED, getScreenBuffer());
			}
		}
	}

	if ((mouse_t.x_mouse >= 341) && (mouse_t.x_mouse <= 633))
	{
		if ((mouse_t.y_mouse >= 484) && (mouse_t.y_mouse <= 550))
		{
			bool = 0;
			if (mouse_t.LB == 1)
			{
				OPTION = ONLINE;
				//exit_menu(bitmaps);
				online_menu(bitmaps);
				//funcao online
			}
			else
			{
				change_color(341, 633, 484, 550, rgb(33,109,16), RED, getScreenBuffer());
			}
		}
	}

	if ((mouse_t.x_mouse >= 248) && (mouse_t.x_mouse <= 787))
	{
		if ((mouse_t.y_mouse >= 412) && (mouse_t.y_mouse <= 466))
		{
			bool = 0;
			if (mouse_t.LB == 1)
			{
				OPTION = HEAD_TO_HEAD;
				//exit_menu(bitmaps);
				Head_to_Head(bitmaps);
				//funcao Head To Head
			}
			else
			{
				change_color(248, 787, 412, 466, rgb(16,69,58), RED, getScreenBuffer());
			}
		}
	}

	if ((mouse_t.x_mouse >= 149) && (mouse_t.x_mouse <= 871))
	{
		if ((mouse_t.y_mouse >= 328) && (mouse_t.y_mouse <= 396))
		{
			bool = 0;
			if (mouse_t.LB == 1)
			{
				OPTION = HUMAN_VS_MACHINE;
				//exit_menu(bitmaps);
				HumanMachine(bitmaps);
				//funcao human vs machine
			}
			else
			{
				change_color(129, 871, 328, 396, rgb(99,16,148), RED, getScreenBuffer());
			}
		}
	}

	if (bool == 0)
	{

	}
	else
	{
		drawBitmap(bitmaps.background, 0,0, ALIGN_LEFT, getScreenBuffer());
	}
	return 1;
}

int change_color(unsigned xi, unsigned xf, unsigned yi, unsigned yf, int color_init, int color_final, char * video_copy)
{
	video_copy = video_copy + xi * 2 + (1024 * yi) * 2;
	unsigned int i;
	unsigned int j;
	char bool = 1;
	for (j = yi; j < yf; j++)
	{
		for (i = xi; i < xf; i++)
		{
			if (color_init == *(uint16_t *)video_copy)
			{
				bool = 0;
				*(uint16_t *)video_copy = color_final;
			}
			video_copy+=2;
		}
		i = 0;
		video_copy = video_copy + 1024 * 2 - (xf - xi) * 2;
	}
	return bool;
}

int HighScores_menu(bitmap_struct bitmaps)
{
	drawBitmap(bitmaps.highscores, 0, 0, ALIGN_LEFT, getScreenBuffer());

	screen_to_mouse(getScreenBuffer(), getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());

	mouse_to_video(getMouseBuffer(), getVideoMem());
	return 0;
}

int online_menu(bitmap_struct bitmaps)
{
	drawBitmap(bitmaps.frame, 0, 0, ALIGN_LEFT, getScreenBuffer());

	screen_to_mouse(getScreenBuffer(), getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());

	mouse_to_video(getMouseBuffer(), getVideoMem());
	return 0;
}

int Head_to_Head(bitmap_struct bitmaps)
{
	drawBitmap(bitmaps.pre_head_to_head, 0, 0, ALIGN_LEFT, getScreenBuffer());

	screen_to_mouse(getScreenBuffer(), getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());

	mouse_to_video(getMouseBuffer(), getVideoMem());
	return 0;
}

int HumanMachine(bitmap_struct bitmaps)
{
	drawBitmap(bitmaps.frame, 0, 0, ALIGN_LEFT, getScreenBuffer());

	screen_to_mouse(getScreenBuffer(), getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());

	mouse_to_video(getMouseBuffer(), getVideoMem());
	return 0;
}

int menu_handler (bitmap_struct bitmaps)
{
	switch (OPTION)
	{
	case MAIN_MENU:
	{
		return position_menu(bitmaps);
		break;
	}
	case HUMAN_VS_MACHINE:
	{

		break;
	}
	case HEAD_TO_HEAD:
	{

		break;
	}
	case ONLINE:
	{

		break;
	}
	case HIGHSCORES:
	{

		break;
	}
	case EXIT_OPT:
	{
		break;
	}
	default:
	{
		printf("Error in menu_handler() - no option available!\n");
		return -1;
	}
	}
	return 1;
}

int is_highscore(scores_t *t, position_t *draw)
{
	int place = -1;
	char discard1, discard2;

	if (draw->score >= t->first.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		t->fifth = t->fourth;
		t->fourth = t->third;
		t->third = t-> second;
		t->second = t->first;
		t->first = (*draw);
		place = 1;
		OPTION = GET_NAME;
		return place;
	}
	else if(draw->score >= t->second.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		t->fifth = t->fourth;
		t->fourth = t->third;
		t->third = t-> second;
		t->second = (*draw);
		place = 2;
		OPTION = GET_NAME;
		return place;
	}
	else if(draw->score >= t->third.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		t->fifth = t->fourth;
		t->fourth = t->third;
		t->third = (*draw);
		place = 3;
		OPTION = GET_NAME;
		return place;
	}
	else if(draw->score >= t->fourth.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		t->fifth = t->fourth;
		t->fourth = (*draw);
		place = 4;
		OPTION = GET_NAME;
		return place;
	}
	else if(draw->score >= t->fifth.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		t->fifth = (*draw);
		place = 5;
		OPTION = GET_NAME;
		return place;
	}

	return place;
}

int score(int tick)
{
	int ret;

	ret = -135 * (tick / 60.0) + 10000;

	return ret;
}
