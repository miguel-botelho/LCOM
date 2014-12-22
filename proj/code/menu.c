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
	exit(0);
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
				menu_handler(bitmaps);
				return 0;
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
				drawBitmap(bitmaps.highscores, 0, 0, ALIGN_LEFT, getScreenBuffer());
				//exit_menu(bitmaps);
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
				drawBitmap(bitmaps.frame, 0, 0, ALIGN_LEFT, getScreenBuffer());
				//exit_menu(bitmaps);
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
				drawBitmap(bitmaps.pre_head_to_head, 0, 0, ALIGN_LEFT, getScreenBuffer());
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
				drawBitmap(bitmaps.frame, 0, 0, ALIGN_LEFT, getScreenBuffer());
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
	if (OPTION == HIGHSCORES)
	{

	}

	screen_to_mouse(getScreenBuffer(), getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());

	mouse_to_video(getMouseBuffer(), getVideoMem());

	return 0;
}

int online_menu(bitmap_struct bitmaps)
{
	if (OPTION == ONLINE)
	{

	}

	screen_to_mouse(getScreenBuffer(), getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());

	mouse_to_video(getMouseBuffer(), getVideoMem());

	return 0;
}

int Head_to_Head(bitmap_struct bitmaps)
{
	if (OPTION == HEAD_TO_HEAD)
	{

	}

	screen_to_mouse(getScreenBuffer(), getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());

	mouse_to_video(getMouseBuffer(), getVideoMem());

	return 0;
}

int HumanMachine(bitmap_struct bitmaps)
{
	if (OPTION == HUMAN_VS_MACHINE)
	{

	}

	screen_to_mouse(getScreenBuffer(), getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());

	mouse_to_video(getMouseBuffer(), getVideoMem());

	selectDraw();

	selectColour();

	if ((mouse_t.x_mouse >= 120) && (mouse_t.x_mouse <= 1020))
	{
		if ((mouse_t.y_mouse >= 183) && (mouse_t.y_mouse <= 717))
		{
			if (mouse_t.LB == 1)
			{
				//PINTAR NA TELA
				if (-1 == toolHandler())
				{
					return -1;
				}
			}
			else
			{
				if (tool = LINE)
				{
					drawLINE();
				}
				else if (tool == PENCIL)
				{
					draw_pencil();
				}
			}
		}
	}

	return 0;
}

int menu_handler (bitmap_struct bitmaps)
{
	switch (OPTION)
	{
	case MAIN_MENU:
	{
		position_menu(bitmaps);
		break;
	}
	case HUMAN_VS_MACHINE:
	{
		HumanMachine(bitmaps);
		break;
	}
	case HEAD_TO_HEAD:
	{
		Head_to_Head(bitmaps);
		break;
	}
	case ONLINE:
	{
		online_menu(bitmaps);
		break;
	}
	case HIGHSCORES:
	{
		HighScores_menu(bitmaps);
		break;
	}
	case EXIT_OPT:
	{
		exit_menu(bitmaps);
		return 0;
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

int toolHandler()
{
	switch (tool)
	{
	case BUCKET:
	{
		draw_bucket();
		break;
	}
	case PENCIL:
	{
		draw_pencil();
		break;
	}
	case BRUSH:
	{
		draw_brush();
		break;
	}
	case LINE:
	{
		drawLINE();
		break;
	}
	case CIRCLE:
	{
		draw_circle();
		break;
	}
	case SQUARE:
	{
		draw_square();
		return 0;
		break;
	}
	default:
	{
		printf("Error in tool handler() - no option available!\n");
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

void selectDraw()
{
	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 241) && (mouse_t.y_mouse <= 289))
		{
			if (mouse_t.LB == 1)
			{
				minus();
			}
		}
	}

	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 289) && (mouse_t.y_mouse <= 337))
		{
			if (mouse_t.LB == 1)
			{
				plus();
			}
		}
	}

	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 337) && (mouse_t.y_mouse <= 385))
		{
			if (mouse_t.LB == 1)
			{
				tool = BUCKET;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 385) && (mouse_t.y_mouse <= 433))
		{
			if (mouse_t.LB == 1)
			{
				tool = BRUSH;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 433) && (mouse_t.y_mouse <= 481))
		{
			if (mouse_t.LB == 1)
			{
				tool = PENCIL;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 481) && (mouse_t.y_mouse <= 529))
		{
			if (mouse_t.LB == 1)
			{
				tool = LINE;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 529) && (mouse_t.y_mouse <= 577))
		{
			if (mouse_t.LB == 1)
			{
				tool = CIRCLE;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 577) && (mouse_t.y_mouse <= 625))
		{
			if (mouse_t.LB == 1)
			{
				tool = SQUARE;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 625) && (mouse_t.y_mouse <= 673))
		{
			if (mouse_t.LB == 1)
			{
				//undo
			}
		}
	}

	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 673) && (mouse_t.y_mouse <= 721))
		{
			if (mouse_t.LB == 1)
			{
				//redo
			}
		}
	}
}

void selectColour()
{
	if ( (mouse_t.x_mouse >= 489) && (mouse_t.x_mouse <= 534) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				colour = BLACK;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 534) && (mouse_t.x_mouse <= 582) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				//GRAY
				colour = GRAY;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 582) && (mouse_t.x_mouse <= 631) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				//RED
				colour = RED;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 631) && (mouse_t.x_mouse <= 681) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				//ORANGE
				colour = ORANGE;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 681) && (mouse_t.x_mouse <= 730) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				//BLUE
				colour = BLUE;
			}
		}
	}
	if ( (mouse_t.x_mouse >= 730) && (mouse_t.x_mouse <= 778) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				//GREEN
				colour = GREEN;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 778) && (mouse_t.x_mouse <= 826) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				//YELLOW
				colour = YELLOW;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 826) && (mouse_t.x_mouse <= 876) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				//PURPLE
				colour = PURPLE;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 876) && (mouse_t.x_mouse <= 925) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				//PINK
				colour = PINK;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 925) && (mouse_t.x_mouse <= 973) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				//BROWN
				colour = BROWN;
			}
		}
	}

	if ( (mouse_t.x_mouse >= 973) && (mouse_t.x_mouse <= 1024) )
	{
		if ( (mouse_t.y_mouse >= 720) && (mouse_t.y_mouse <= 768))
		{
			if (mouse_t.LB == 1)
			{
				//WHITE
				colour = WHITE;
			}
		}
	}

}

int displayTimer(int contador, Bitmap ** numbers, bitmap_struct bitmaps)
{
	unsigned int l = 0;
	unsigned int a = 0;
	char * human_machine = getHumanMachine();
	char * screen_buffer = getScreenBuffer();
	human_machine = human_machine + (1024 - 100) * 2 + 100 * 1024 * 2;
	screen_buffer = screen_buffer + (1024 - 100) * 2 + 100 * 1024 * 2;
	for(; a < 100; a++)
	{
		for (; l < 100;l++)
		{
			*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
			screen_buffer+=2;
			human_machine+=2;
		}
		l = 0;
		screen_buffer += 1024 * 2 - 100 * 2;
		human_machine += 1024 * 2 - 100 * 2;
	}

	screen_buffer = getScreenBuffer();
	drawMouse(numbers[contador], 1024 - 60, 30, ALIGN_LEFT, screen_buffer);

	human_machine = getHumanMachine();
	screen_to_mouse(screen_buffer, getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());
	mouse_to_video(getMouseBuffer(), getVideoMem());
}

int displayTimer10(int contador, Bitmap ** numbers, bitmap_struct bitmaps)
{
	int nr1 = contador / 10;
	int nr2 = contador % 10;

	unsigned int l = 0;
	unsigned int a = 0;
	char * human_machine = getHumanMachine();
	char * screen_buffer = getScreenBuffer();
	human_machine = human_machine + (1024 - 100) * 2 + 100 * 1024 * 2;
	screen_buffer = screen_buffer + (1024 - 100) * 2 + 100 * 1024 * 2;
	for(; a < 100; a++)
	{
		for (; l < 100;l++)
		{
			*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
			screen_buffer+=2;
			human_machine+=2;
		}
		l = 0;
		screen_buffer += 1024 * 2 - 100 * 2;
		human_machine += 1024 * 2 - 100 * 2;
	}
	screen_buffer = getScreenBuffer();
	drawMouse(numbers[nr1], 1024 - 60, 30, ALIGN_LEFT, screen_buffer);
	drawMouse(numbers[nr2], 1024 - 30, 30, ALIGN_LEFT, screen_buffer);
	screen_to_mouse(screen_buffer, getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());
	mouse_to_video(getMouseBuffer(), getVideoMem());

}
