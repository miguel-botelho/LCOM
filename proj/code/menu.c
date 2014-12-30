#include "menu.h"

void bitmaps_load(bitmap_struct *t)
{
	t->background = loadBitmap("home/lcom/proj/code/images/Fundo.bmp");
	t->highscores = loadBitmap("home/lcom/proj/code/images/Highscores.bmp");
	t->mouse = loadBitmap("home/lcom/proj/code/images/Mouse.bmp");
	t->frame = loadBitmap("home/lcom/proj/code/images/Frame.bmp");
	t->pre_head_to_head = loadBitmap("home/lcom/proj/code/images/Pre-Head_to_Head.bmp");
	t->lost = loadBitmap("home/lcom/proj/code/images/Lost.bmp");
	t->win = loadBitmap("home/lcom/proj/code/images/Win.bmp");
}

int exit_menu(bitmap_struct bitmaps, Bitmap ** numbers, Bitmap ** key_scancode)
{
	deleteBitmap(bitmaps.background);
	deleteBitmap(bitmaps.mouse);
	deleteBitmap(bitmaps.frame);
	deleteBitmap(bitmaps.highscores);
	deleteBitmap(bitmaps.pre_head_to_head);
	deleteBitmap(bitmaps.lost);
	deleteBitmap(bitmaps.win);
	int i = 0;
	for(; i < 10; i++)
	{
		deleteBitmap(numbers[i]);
	}
	i = 16;
	for(; i < 50; i++)
	{
		deleteBitmap(key_scancode[i]);
	}
	vg_exit();

	//estas duas opearacoes sao feitas para assegurar o normal funcionamento do rato quando acabar a funcao
	mouse_int_handler(DISABLE_STREAM); //desativa a stream
	mouse_int_handler(SET_STREAM); //volta a ativar a stream, isto foi feito para desativar o envio dos pacotes

	if (unsubscribe_all() == -1)
	{
		printf("Failure to unsubscribe!! \n\n");
		return -1;
	}
	write_all();
	exit(0);
}

char position_menu(bitmap_struct bitmaps, Bitmap ** numbers, Bitmap ** key_scancode)
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
				menu_handler(bitmaps, numbers, key_scancode);
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
				change_color(305, 718, 555, 644, BLACK, RED, getScreenBuffer());
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
				change_color(341, 633, 484, 550, BLACK, RED, getScreenBuffer());
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
				OPTION = GET_NAME;
				drawBitmap(bitmaps.pre_head_to_head, 0, 0, ALIGN_LEFT, getScreenBuffer());
				ai_or_pvp = 1;
			}
			else
			{
				change_color(248, 787, 412, 466, BLACK, RED, getScreenBuffer());
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
				OPTION = GET_NAME;
				ai_or_pvp = 0;
				drawBitmap(bitmaps.pre_head_to_head, 0, 0, ALIGN_LEFT, getScreenBuffer());
			}
			else
			{
				change_color(149, 871, 328, 396, BLACK, RED, getScreenBuffer());
			}
		}
	}

	if (bool == 0)
	{

	}
	else
	{
		if (OPTION == MAIN_MENU)
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

	return 0;
}

int online_menu(bitmap_struct bitmaps)
{
	if (OPTION == ONLINE)
	{

	}

	//se ele acertar, ou acabar o timer, chamar is highscore
	//pedir nome

	return 0;
}

int HumanMachine(bitmap_struct bitmaps)
{
	if (OPTION == HUMAN_VS_MACHINE)
	{

	}


	//se ele acertar, ou acabar o timer, chamar is highscore
	//pedir nome

	return 0;
}

int Head_to_Head(bitmap_struct bitmaps, Bitmap ** numbers)
{
	if (OPTION == HEAD_TO_HEAD)
	{
		drawMouse(numbers[tries], 162,8, ALIGN_LEFT, getScreenBuffer());
		if (tentativas != tries)
		{
			int a = 0;
			int l = 0;

			char* human_machine = getHumanMachine();
			char* screen_buffer = getScreenBuffer();
			drawBitmap(bitmaps.frame, 0, 0, ALIGN_LEFT, human_machine);
			human_machine = human_machine + 162 * 2 + 1024 * 8 * 2;
			screen_buffer = screen_buffer + 162 * 2 + 1024 * 8 * 2;
			for(; a < 50; a++)
			{
				for (; l < 40;l++)
				{
					*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
					screen_buffer+=2;
					human_machine+=2;
				}
				l = 0;
				screen_buffer += 1024 * 2 - 40 * 2;
				human_machine += 1024 * 2 - 40 * 2;
			}
			tentativas++;
		}


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
					if (tool == LINE)
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

		if ((RTC_COUNTER <= 0) || (tries > 4) )
		{
			tries = 0;
			OPTION = STATIC;
			tentativas = 0;
		}
	}


	//se ele acertar, ou acabar o timer, chamar is highscore
	//pedir nome

	return 0;
}

int menu_handler (bitmap_struct bitmaps, Bitmap ** numbers, Bitmap ** key_scancode)
{
	switch (OPTION)
	{
	case MAIN_MENU:
	{
		position_menu(bitmaps, numbers, key_scancode);
		break;
	}
	case HUMAN_VS_MACHINE:
	{
		HumanMachine(bitmaps);
		break;
	}
	case HEAD_TO_HEAD:
	{
		Head_to_Head(bitmaps, numbers);
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
		exit_menu(bitmaps, numbers, key_scancode);
		return 0;
		break;
	}
	case GET_NAME:
	{
		break;
	}
	case STATIC:
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

int toolHandler()
{
	static int previous_tool = 0;//PENCIL;
	char is_not_previous; //1 = TRUE

	if (previous_tool != tool)
	{
		is_not_previous = 1;
		previous_tool = tool;
	}
	else
	{
		is_not_previous = 0;
	}

	switch (tool)
	{
	case BUCKET:
	{
		draw_bucket();
		if (is_not_previous)
		{
			createDBitmap();
		}
		break;
	}
	case PENCIL:
	{
		draw_pencil();
		if (is_not_previous)
		{
			createDBitmap();
		}
		break;
	}
	case BRUSH:
	{
		draw_brush();
		if (is_not_previous)
		{
			createDBitmap();
		}
		break;
	}
	case LINE:
	{
		drawLINE();
		if (is_not_previous)
		{
			createDBitmap();
		}
		break;
	}
	case CIRCLE:
	{
		draw_circle();
		if (is_not_previous)
		{
			createDBitmap();
		}
		break;
	}
	case SQUARE:
	{
		draw_square();
		if (is_not_previous)
		{
			createDBitmap();
		}
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

int is_highscore(position_t *draw)
{
	int place = -1;
	char discard1, discard2;

	if (draw->score >= top_highscores.first.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		top_highscores.fifth = top_highscores.fourth;
		top_highscores.fourth = top_highscores.third;
		top_highscores.third = top_highscores. second;
		top_highscores.second = top_highscores.first;
		top_highscores.first = (*draw);

		remove("home/lcom/proj/code/files/5.bmp");
		rename("home/lcom/proj/code/files/4.bmp", "home/lcom/proj/code/files/5.bmp");
		rename("home/lcom/proj/code/files/3.bmp", "home/lcom/proj/code/files/4.bmp");
		rename("home/lcom/proj/code/files/2.bmp", "home/lcom/proj/code/files/3.bmp");
		rename("home/lcom/proj/code/files/1.bmp", "home/lcom/proj/code/files/2.bmp");
		rename("home/lcom/proj/code/files/current_draw.bmp", "home/lcom/proj/code/files/1.bmp");

		place = 1;
		OPTION = GET_NAME;
		return place;
	}
	else if(draw->score >= top_highscores.second.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		top_highscores.fifth = top_highscores.fourth;
		top_highscores.fourth = top_highscores.third;
		top_highscores.third = top_highscores. second;
		top_highscores.second = (*draw);

		remove("home/lcom/proj/code/files/5.bmp");
		rename("home/lcom/proj/code/files/4.bmp", "home/lcom/proj/code/files/5.bmp");
		rename("home/lcom/proj/code/files/3.bmp", "home/lcom/proj/code/files/4.bmp");
		rename("home/lcom/proj/code/files/2.bmp", "home/lcom/proj/code/files/3.bmp");
		rename("home/lcom/proj/code/files/current_draw.bmp", "home/lcom/proj/code/files/2.bmp");

		place = 2;
		OPTION = GET_NAME;
		return place;
	}
	else if(draw->score >= top_highscores.third.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		top_highscores.fifth = top_highscores.fourth;
		top_highscores.fourth = top_highscores.third;
		top_highscores.third = (*draw);

		remove("home/lcom/proj/code/files/5.bmp");
		rename("home/lcom/proj/code/files/4.bmp", "home/lcom/proj/code/files/5.bmp");
		rename("home/lcom/proj/code/files/3.bmp", "home/lcom/proj/code/files/4.bmp");
		rename("home/lcom/proj/code/files/current_draw.bmp", "home/lcom/proj/code/files/3.bmp");

		place = 3;
		OPTION = GET_NAME;
		return place;
	}
	else if(draw->score >= top_highscores.fourth.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		top_highscores.fifth = top_highscores.fourth;
		top_highscores.fourth = (*draw);

		remove("home/lcom/proj/code/files/5.bmp");
		rename("home/lcom/proj/code/files/4.bmp", "home/lcom/proj/code/files/5.bmp");
		rename("home/lcom/proj/code/files/current_draw.bmp", "home/lcom/proj/code/files/4.bmp");


		place = 4;
		OPTION = GET_NAME;
		return place;
	}
	else if(draw->score >= top_highscores.fifth.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		top_highscores.fifth = (*draw);

		remove("home/lcom/proj/code/files/5.bmp");
		rename("home/lcom/proj/code/files/current_draw.bmp", "home/lcom/proj/code/files/5.bmp");

		place = 5;
		OPTION = GET_NAME;
		return place;
	}

	return place;
}

int score(int tick)
{
	int ret;

	ret = -135 * (tick / 60.0) + 10000 - tries * 100;

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
				change_color(25,84,337,625,RED,BLACK, getScreenBuffer());
				change_color(25, 84, 337, 385, BLACK, RED, getScreenBuffer());
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
				change_color(25,84,337,625,RED,BLACK, getScreenBuffer());
				change_color(25, 84, 385, 433, BLACK, RED, getScreenBuffer());
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
				change_color(25,84,337,625,RED,BLACK, getScreenBuffer());
				change_color(25, 84, 433, 481, BLACK, RED, getScreenBuffer());
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
				change_color(25,84,337,625,RED,BLACK, getScreenBuffer());
				change_color(25, 84, 481, 529, BLACK, RED, getScreenBuffer());
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
				change_color(25,84,337,625,RED,BLACK, getScreenBuffer());
				change_color(25, 84, 529, 577, BLACK, RED, getScreenBuffer());
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
				change_color(25,84,337,625,RED,BLACK, getScreenBuffer());
				change_color(25, 84, 577, 625, BLACK, RED, getScreenBuffer());
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
				undo();
			}
		}
	}

	if ( (mouse_t.x_mouse >= 25) && (mouse_t.x_mouse <= 84) )
	{
		if ( (mouse_t.y_mouse >= 673) && (mouse_t.y_mouse <= 721))
		{
			if (mouse_t.LB == 1)
			{
				redo();
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
	drawBitmap(bitmaps.frame, 0, 0, ALIGN_LEFT, human_machine);
	human_machine = human_machine + (1024 - 100) * 2;
	screen_buffer = screen_buffer + (1024 - 100) * 2;

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
	drawBitmap(bitmaps.frame, 0, 0, ALIGN_LEFT, human_machine);
	human_machine = human_machine + (1024 - 100) * 2;
	screen_buffer = screen_buffer + (1024 - 100) * 2;
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

void WriteArray(char * name, int length, Bitmap ** key_scancode, bitmap_struct bitmaps)
{
	int i = 0;
	char * screen_buffer = getScreenBuffer();
	espaco = 0;
	for(; i <= length; i++)
	{
		switch (name[i])
		{
		case 'Q':
		{
			drawMouse(key_scancode[KEY_Q], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'W':
		{
			drawMouse(key_scancode[KEY_W], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'E':
		{
			drawMouse(key_scancode[KEY_E], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'R':
		{
			drawMouse(key_scancode[KEY_R], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'T':
		{
			drawMouse(key_scancode[KEY_T], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'Y':
		{
			drawMouse(key_scancode[KEY_Y], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'U':
		{
			drawMouse(key_scancode[KEY_U], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'I':
		{
			drawMouse(key_scancode[KEY_I], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'O':
		{
			drawMouse(key_scancode[KEY_O], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'P':
		{
			drawMouse(key_scancode[KEY_P], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'A':
		{
			drawMouse(key_scancode[KEY_A], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'S':
		{
			drawMouse(key_scancode[KEY_S], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'D':
		{
			drawMouse(key_scancode[KEY_D], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'F':
		{
			drawMouse(key_scancode[KEY_F], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'G':
		{
			drawMouse(key_scancode[KEY_G], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'H':
		{
			drawMouse(key_scancode[KEY_H], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'J':
		{
			drawMouse(key_scancode[KEY_J], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'K':
		{
			drawMouse(key_scancode[KEY_K], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'L':
		{
			drawMouse(key_scancode[KEY_L], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'Z':
		{
			drawMouse(key_scancode[KEY_Z], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'X':
		{
			drawMouse(key_scancode[KEY_X], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'C':
		{
			drawMouse(key_scancode[KEY_C], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'V':
		{
			drawMouse(key_scancode[KEY_V], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'B':
		{
			drawMouse(key_scancode[KEY_B], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'N':
		{
			drawMouse(key_scancode[KEY_N], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'M':
		{
			drawMouse(key_scancode[KEY_M], 258 + espaco, 492, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		}
	}

}

void getrgb(int *red, int *green, int *blue)
{
	if (colour == BLACK)
	{
		*red = 0;
		*green = 0;
		*blue = 0;
	}
	else if (colour == YELLOW){
		*red = 255;
		*green = 251;
		*blue = 0;
	}
	else if (colour == BLUE){
		*red = 0;
		*green = 16;
		*blue = 255;
	}
	else if (colour == PINK){
		*red = 255;
		*green = 0;
		*blue = 173;
	}
	else if (colour == WHITE){
		*red = 255;
		*green = 255;
		*blue = 255;
	}
	else if (colour == GREEN){
		*red = 16;
		*green = 138;
		*blue = 0;
	}
	else if (colour == RED){
		*red = 254;
		*green = 0;
		*blue = 0;
	}
	else if (colour == GRAY){
		*red = 107;
		*green = 109;
		*blue = 107;
	}
	else if (colour == CYAN){
		*red = 0;
		*green = 255;
		*blue = 255;
	}
	else if (colour == ORANGE){
		*red = 255;
		*green = 113;
		*blue = 0;
	}
	else if (colour == NAVY){
		*red = 0;
		*green = 0;
		*blue = 128;
	}
	else if (colour == SILVER){
		*red = 192;
		*green = 192;
		*blue = 192;
	}
	else if (colour == TEAL){
		*red = 0;
		*green = 128;
		*blue = 128;
	}
	else if (colour == PURPLE){
		*red = 123;
		*green = 4;
		*blue = 156;
	}
	else if (colour == BROWN){
		*red = 132;
		*green = 61;
		*blue = 8;
	}
	else if (colour == DARK_GRAY){
		*red = 169;
		*green = 169;
		*blue = 169;
	}
	else if (colour == LIGHT_GRAY){
		*red = 211;
		*green = 211;
		*blue = 211;
	}
}


void WriteArrayFrame(char * name, int length, Bitmap ** key_scancode, bitmap_struct bitmaps)
{
	int i = 0;
	char * screen_buffer = getScreenBuffer();
	espaco = 0;
	for(; i <= length; i++)
	{
		switch (name[i])
		{
		case 'Q':
		{
			drawMouse(key_scancode[KEY_Q], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'W':
		{
			drawMouse(key_scancode[KEY_W], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'E':
		{
			drawMouse(key_scancode[KEY_E], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'R':
		{
			drawMouse(key_scancode[KEY_R], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'T':
		{
			drawMouse(key_scancode[KEY_T], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'Y':
		{
			drawMouse(key_scancode[KEY_Y], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'U':
		{
			drawMouse(key_scancode[KEY_U], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'I':
		{
			drawMouse(key_scancode[KEY_I], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'O':
		{
			drawMouse(key_scancode[KEY_O], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'P':
		{
			drawMouse(key_scancode[KEY_P], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'A':
		{
			drawMouse(key_scancode[KEY_A], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'S':
		{
			drawMouse(key_scancode[KEY_S], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'D':
		{
			drawMouse(key_scancode[KEY_D], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'F':
		{
			drawMouse(key_scancode[KEY_F], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'G':
		{
			drawMouse(key_scancode[KEY_G], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'H':
		{
			drawMouse(key_scancode[KEY_H], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'J':
		{
			drawMouse(key_scancode[KEY_J], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'K':
		{
			drawMouse(key_scancode[KEY_K], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'L':
		{
			drawMouse(key_scancode[KEY_L], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'Z':
		{
			drawMouse(key_scancode[KEY_Z], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'X':
		{
			drawMouse(key_scancode[KEY_X], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'C':
		{
			drawMouse(key_scancode[KEY_C], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'V':
		{
			drawMouse(key_scancode[KEY_V], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'B':
		{
			drawMouse(key_scancode[KEY_B], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'N':
		{
			drawMouse(key_scancode[KEY_N], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'M':
		{
			drawMouse(key_scancode[KEY_M], 117 + espaco, 61, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		}
	}

}

void WriteArrayFrame2(char * name, int length, Bitmap ** key_scancode, bitmap_struct bitmaps)
{
	int i = 0;
	char * screen_buffer = getScreenBuffer();
	espaco = 0;
	for(; i <= length; i++)
	{
		switch (name[i])
		{
		case 'Q':
		{
			drawMouse(key_scancode[KEY_Q], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'W':
		{
			drawMouse(key_scancode[KEY_W], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'E':
		{
			drawMouse(key_scancode[KEY_E], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'R':
		{
			drawMouse(key_scancode[KEY_R], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'T':
		{
			drawMouse(key_scancode[KEY_T], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'Y':
		{
			drawMouse(key_scancode[KEY_Y], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'U':
		{
			drawMouse(key_scancode[KEY_U], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'I':
		{
			drawMouse(key_scancode[KEY_I], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'O':
		{
			drawMouse(key_scancode[KEY_O], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'P':
		{
			drawMouse(key_scancode[KEY_P], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'A':
		{
			drawMouse(key_scancode[KEY_A], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'S':
		{
			drawMouse(key_scancode[KEY_S], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'D':
		{
			drawMouse(key_scancode[KEY_D], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'F':
		{
			drawMouse(key_scancode[KEY_F], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'G':
		{
			drawMouse(key_scancode[KEY_G], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'H':
		{
			drawMouse(key_scancode[KEY_H], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'J':
		{
			drawMouse(key_scancode[KEY_J], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'K':
		{
			drawMouse(key_scancode[KEY_K], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'L':
		{
			drawMouse(key_scancode[KEY_L], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'Z':
		{
			drawMouse(key_scancode[KEY_Z], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'X':
		{
			drawMouse(key_scancode[KEY_X], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'C':
		{
			drawMouse(key_scancode[KEY_C], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'V':
		{
			drawMouse(key_scancode[KEY_V], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'B':
		{
			drawMouse(key_scancode[KEY_B], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'N':
		{
			drawMouse(key_scancode[KEY_N], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		case 'M':
		{
			drawMouse(key_scancode[KEY_M], 117 + espaco, 134, ALIGN_LEFT, screen_buffer);
			espaco = espaco + 35;
			break;
		}
		}
	}
}

Bitmap* randImage()
{
	int random = rand() % 10;
	random = 0;
	int i;

	switch(random)
	{
	case 0:
	{
		return loadBitmap("home/lcom/proj/code/images/0.bmp");
		i = 3;
		word[0] = 'D';
		word[1] = 'O';
		word[2] = 'G';
		for (; i < length_word; i++)
		{
			word[i] = '0';
		}
	}
	case 1:
	{
		return loadBitmap("home/lcom/proj/code/images/1.bmp");
	}
	case 2:
	{
		return loadBitmap("home/lcom/proj/code/images/2.bmp");
	}
	case 3:
	{
		return loadBitmap("home/lcom/proj/code/images/3.bmp");
	}
	case 4:
	{
		return loadBitmap("home/lcom/proj/code/images/4.bmp");
	}
	case 5:
	{
		return loadBitmap("home/lcom/proj/code/images/5.bmp");
	}
	case 6:
	{
		return loadBitmap("home/lcom/proj/code/images/6.bmp");
	}
	case 7:
	{
		return loadBitmap("home/lcom/proj/code/images/7.bmp");
	}
	case 8:
	{
		return loadBitmap("home/lcom/proj/code/images/8.bmp");
	}
	case 9:
	{
		return loadBitmap("home/lcom/proj/code/images/8.bmp");
	}
	}
}
