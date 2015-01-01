#include "menu.h"

void bitmaps_load(bitmap_struct *t)
{
	t->background = loadBitmap(IMAGES_PATH"Fundo.bmp");
	t->highscores = loadBitmap(IMAGES_PATH"Highscores.bmp");
	t->mouse = loadBitmap(IMAGES_PATH"Mouse.bmp");
	t->frame = loadBitmap(IMAGES_PATH"Frame.bmp");
	t->pre_head_to_head = loadBitmap(IMAGES_PATH"Pre-Head_to_Head.bmp");
	t->lost = loadBitmap(IMAGES_PATH"Lost.bmp");
	t->win = loadBitmap(IMAGES_PATH"Win.bmp");
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

	if ((mouse_t.x_mouse >= EXIT_X_I) && (mouse_t.x_mouse <= EXIT_X_F))
	{
		if ((mouse_t.y_mouse >= EXIT_Y_I) && (mouse_t.y_mouse <= EXIT_Y_F))
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
				change_color(EXIT_X_I, EXIT_X_F, EXIT_Y_I, EXIT_Y_F, BLACK, RED, getScreenBuffer());
			}

		}
	}

	if ((mouse_t.x_mouse >= HIGH_X_I) && (mouse_t.x_mouse <= HIGH_X_F))
	{
		if ((mouse_t.y_mouse >= HIGH_Y_I) && (mouse_t.y_mouse <= HIGH_Y_F))
		{
			bool = 0;
			if (mouse_t.LB == 1)
			{
				OPTION = HIGHSCORES;
				drawBitmap(bitmaps.highscores, INITIAL, INITIAL, ALIGN_LEFT, getScreenBuffer());
				//exit_menu(bitmaps);
				//funcao HighScores
			}
			else
			{
				change_color(HIGH_X_I, HIGH_X_F, HIGH_Y_I, HIGH_Y_F, BLACK, RED, getScreenBuffer());
			}
		}
	}

	if ((mouse_t.x_mouse >= ONLINE_X_I) && (mouse_t.x_mouse <= ONLINE_X_F))
	{
		if ((mouse_t.y_mouse >= ONLINE_Y_I) && (mouse_t.y_mouse <= ONLINE_Y_F))
		{
			bool = 0;
			if (mouse_t.LB == 1)
			{
				OPTION = ONLINE;
				drawBitmap(bitmaps.frame, INITIAL, INITIAL, ALIGN_LEFT, getScreenBuffer());
				//exit_menu(bitmaps);
				//funcao online
			}
			else
			{
				change_color(ONLINE_X_I, ONLINE_X_F, ONLINE_Y_I, ONLINE_Y_F, BLACK, RED, getScreenBuffer());
			}
		}
	}

	if ((mouse_t.x_mouse >= HEAD_X_I) && (mouse_t.x_mouse <= HEAD_X_F))
	{
		if ((mouse_t.y_mouse >= HEAD_Y_I) && (mouse_t.y_mouse <= HEAD_Y_F))
		{
			bool = 0;
			if (mouse_t.LB == 1)
			{
				OPTION = GET_NAME;
				drawBitmap(bitmaps.pre_head_to_head, INITIAL, INITIAL, ALIGN_LEFT, getScreenBuffer());
				ai_or_pvp = 1;
				tentativas = 0;
				tries = 0;
				RTC_COUNTER = START_RTC_COUNTER;
			}
			else
			{
				change_color(HEAD_X_I, HEAD_X_F, HEAD_Y_I, HEAD_Y_F, BLACK, RED, getScreenBuffer());
			}
		}
	}

	if ((mouse_t.x_mouse >= HUMAN_X_I) && (mouse_t.x_mouse <= HUMAN_X_F))
	{
		if ((mouse_t.y_mouse >= HUMAN_Y_I) && (mouse_t.y_mouse <= HUMAN_Y_F))
		{
			bool = 0;
			if (mouse_t.LB == 1)
			{
				tentativas = 0;
				tries = 0;
				RTC_COUNTER = START_RTC_COUNTER;
				OPTION = GET_NAME;
				ai_or_pvp = 0;
				drawBitmap(bitmaps.pre_head_to_head, INITIAL, INITIAL, ALIGN_LEFT, getScreenBuffer());
			}
			else
			{
				change_color(HUMAN_X_I, HUMAN_X_F, HUMAN_Y_I, HUMAN_Y_F, BLACK, RED, getScreenBuffer());
			}
		}
	}

	if (bool == 0)
	{

	}
	else
	{
		if (OPTION == MAIN_MENU)
			drawBitmap(bitmaps.background, INITIAL,INITIAL, ALIGN_LEFT, getScreenBuffer());
	}
	return 1;
}

int change_color(unsigned xi, unsigned xf, unsigned yi, unsigned yf, int color_init, int color_final, char * video_copy)
{
	video_copy = video_copy + xi * 2 + (getHRes() * yi) * 2;
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
		video_copy = video_copy + getHRes() * 2 - (xf - xi) * 2;
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

int HumanMachine(bitmap_struct bitmaps, Bitmap ** numbers)
{
	if (OPTION == HUMAN_VS_MACHINE)
	{
		drawMouse(numbers[tries], TRIES_X,TRIES_Y, ALIGN_LEFT, getScreenBuffer());
		if (tentativas != tries)
		{
			int a = 0;
			int l = 0;

			char* human_machine = getHumanMachine();
			char* screen_buffer = getScreenBuffer();
			drawBitmap(bitmaps.frame, INITIAL, INITIAL, ALIGN_LEFT, human_machine);
			human_machine = human_machine + TRIES_X * 2 + getHRes() * TRIES_Y * 2;
			screen_buffer = screen_buffer + TRIES_X * 2 + getHRes() * TRIES_Y * 2;
			for(; a < CLEAN_TRIES_X; a++)
			{
				for (; l < CLEAN_TRIES_Y;l++)
				{
					*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
					screen_buffer+=2;
					human_machine+=2;
				}
				l = 0;
				screen_buffer += getHRes() * 2 - CLEAN_TRIES_Y * 2;
				human_machine += getHRes() * 2 - CLEAN_TRIES_Y * 2;
			}
			tentativas++;
		}
		if ((RTC_COUNTER <= 0) || (tries > MAX_TRIES) )
		{
			tries = 0;
			OPTION = STATIC;
			drawBitmap(bitmaps.lost, INITIAL,INITIAL,ALIGN_LEFT, getScreenBuffer());
			tentativas = 0;
			RTC_COUNTER = START_RTC_COUNTER;
			contador_c = CANVAS_Y_F;
			cleanName();
			verdadeiro = 1;
		}
		return 0;
	}
}

int Head_to_Head(bitmap_struct bitmaps, Bitmap ** numbers)
{
	if (OPTION == HEAD_TO_HEAD)
	{
		drawMouse(numbers[tries], TRIES_X,TRIES_Y, ALIGN_LEFT, getScreenBuffer());
		if (tentativas != tries)
		{
			int a = 0;
			int l = 0;

			char* human_machine = getHumanMachine();
			char* screen_buffer = getScreenBuffer();
			drawBitmap(bitmaps.frame, INITIAL, INITIAL, ALIGN_LEFT, human_machine);
			human_machine = human_machine + TRIES_X * 2 + getHRes() * TRIES_Y * 2;
			screen_buffer = screen_buffer + TRIES_X * 2 + getHRes() * TRIES_Y * 2;
			for(; a < CLEAN_TRIES_X; a++)
			{
				for (; l < CLEAN_TRIES_Y;l++)
				{
					*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
					screen_buffer+=2;
					human_machine+=2;
				}
				l = 0;
				screen_buffer += getHRes() * 2 - CLEAN_TRIES_Y * 2;
				human_machine += getHRes() * 2 - CLEAN_TRIES_Y * 2;
			}
			tentativas++;
		}


		selectDraw();

		selectColour();

		if ((mouse_t.x_mouse >= TOOL_HANDLER_X_I) && (mouse_t.x_mouse <= TOOL_HANDLER_X_F))
		{
			if ((mouse_t.y_mouse >= TOOL_HANDLER_Y_I) && (mouse_t.y_mouse <= TOOL_HANDLER_Y_F))
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

		if ((RTC_COUNTER <= 0) || (tries > MAX_TRIES) )
		{
			tries = 0;
			OPTION = STATIC;
			drawBitmap(bitmaps.lost, INITIAL,INITIAL,ALIGN_LEFT, getScreenBuffer());
			tentativas = 0;
			RTC_COUNTER = START_RTC_COUNTER;
			cleanName();
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
		tries = 0;
		tentativas = 0;
		position_menu(bitmaps, numbers, key_scancode);
		break;
	}
	case HUMAN_VS_MACHINE:
	{
		HumanMachine(bitmaps, numbers);
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
	/*
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

		remove(FILES_PATH"5.bmp");
		rename(FILES_PATH"4.bmp", FILES_PATH"5.bmp");
		rename(FILES_PATH"3.bmp", FILES_PATH"4.bmp");
		rename(FILES_PATH"2.bmp", FILES_PATH"3.bmp");
		rename(FILES_PATH"1.bmp", FILES_PATH"2.bmp");
		rename(FILES_PATH"current_draw.bmp", FILES_PATH"1.bmp");

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

		remove(FILES_PATH"5.bmp");
		rename(FILES_PATH"4.bmp", FILES_PATH"5.bmp");
		rename(FILES_PATH"3.bmp", FILES_PATH"4.bmp");
		rename(FILES_PATH"2.bmp", FILES_PATH"3.bmp");
		rename(FILES_PATH"current_draw.bmp", FILES_PATH"2.bmp");

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

		remove(FILES_PATH"5.bmp");
		rename(FILES_PATH"4.bmp", FILES_PATH"5.bmp");
		rename(FILES_PATH"3.bmp", FILES_PATH"4.bmp");
		rename(FILES_PATH"current_draw.bmp", FILES_PATH"3.bmp");

		place = 3;
		OPTION = GET_NAME;
		return place;
	}
	else if(draw->score >= top_highscores.fourth.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		top_highscores.fifth = top_highscores.fourth;
		top_highscores.fourth = (*draw);

		remove(FILES_PATH"5.bmp");
		rename(FILES_PATH"4.bmp", FILES_PATH"5.bmp");
		rename(FILES_PATH"current_draw.bmp", FILES_PATH"4.bmp");


		place = 4;
		OPTION = GET_NAME;
		return place;
	}
	else if(draw->score >= top_highscores.fifth.score)
	{
		read_time(&(draw->year), &(draw->month), &(draw->day), &discard1, &(draw->hour), &(draw->minutes), &discard2);
		top_highscores.fifth = (*draw);

		remove(FILES_PATH"5.bmp");
		rename(FILES_PATH"current_draw.bmp", FILES_PATH"5.bmp");

		place = 5;
		OPTION = GET_NAME;
		return place;
	}

	return place;
	 */
}

int score(int tick)
{
	int ret;

	ret = -135 * (tick / 60.0) + 10000 - tries * 100;

	return ret;
}

void selectDraw()
{
	if ( (mouse_t.x_mouse >= TOOL_X_I) && (mouse_t.x_mouse <= TOOL_X_F) )
	{
		if ( (mouse_t.y_mouse >= MINUS_Y_I) && (mouse_t.y_mouse <= MINUS_Y_F))
		{
			if (mouse_t.LB == 1)
			{
				minus();
			}
		}
	}

	if ( (mouse_t.x_mouse >= TOOL_X_I) && (mouse_t.x_mouse <= TOOL_X_F) )
	{
		if ( (mouse_t.y_mouse >= PLUS_Y_I) && (mouse_t.y_mouse <= PLUS_Y_F))
		{
			if (mouse_t.LB == 1)
			{
				plus();
			}
		}
	}

	if ( (mouse_t.x_mouse >= TOOL_X_I) && (mouse_t.x_mouse <= TOOL_X_F) )
	{
		if ( (mouse_t.y_mouse >= BUCKET_Y_I) && (mouse_t.y_mouse <= BUCKET_Y_F))
		{
			if (mouse_t.LB == 1)
			{
				change_color(TOOL_X_I,TOOL_X_F,BUCKET_Y_I,SQUARE_Y_F,RED,BLACK, getScreenBuffer());
				change_color(TOOL_X_I, TOOL_X_F, BUCKET_Y_I, BUCKET_Y_F, BLACK, RED, getScreenBuffer());
				tool = BUCKET;
			}
		}
	}

	if ( (mouse_t.x_mouse >= TOOL_X_I) && (mouse_t.x_mouse <= TOOL_X_F) )
	{
		if ( (mouse_t.y_mouse >= BRUSH_Y_I) && (mouse_t.y_mouse <= BRUSH_Y_F))
		{
			if (mouse_t.LB == 1)
			{
				change_color(TOOL_X_I,TOOL_X_F,BUCKET_Y_I,SQUARE_Y_F,RED,BLACK, getScreenBuffer());
				change_color(TOOL_X_I, TOOL_X_F, BRUSH_Y_I, BRUSH_Y_F, BLACK, RED, getScreenBuffer());
				tool = BRUSH;
			}
		}
	}

	if ( (mouse_t.x_mouse >= TOOL_X_I) && (mouse_t.x_mouse <= TOOL_X_F) )
	{
		if ( (mouse_t.y_mouse >= PENCIL_Y_I) && (mouse_t.y_mouse <= PENCIL_Y_F))
		{
			if (mouse_t.LB == 1)
			{
				change_color(TOOL_X_I,TOOL_X_F,BUCKET_Y_I,SQUARE_Y_F,RED,BLACK, getScreenBuffer());
				change_color(TOOL_X_I, TOOL_X_F, PENCIL_Y_I, PENCIL_Y_F, BLACK, RED, getScreenBuffer());
				tool = PENCIL;
			}
		}
	}

	if ( (mouse_t.x_mouse >= TOOL_X_I) && (mouse_t.x_mouse <= TOOL_X_F) )
	{
		if ( (mouse_t.y_mouse >= LINE_Y_I) && (mouse_t.y_mouse <= LINE_Y_F))
		{
			if (mouse_t.LB == 1)
			{
				change_color(TOOL_X_I,TOOL_X_F,BUCKET_Y_I,SQUARE_Y_F,RED,BLACK, getScreenBuffer());
				change_color(TOOL_X_I, TOOL_X_F, LINE_Y_I, LINE_Y_F, BLACK, RED, getScreenBuffer());
				tool = LINE;
			}
		}
	}

	if ( (mouse_t.x_mouse >= TOOL_X_I) && (mouse_t.x_mouse <= TOOL_X_F) )
	{
		if ( (mouse_t.y_mouse >= CIRCLE_Y_I) && (mouse_t.y_mouse <= CIRCLE_Y_F))
		{
			if (mouse_t.LB == 1)
			{
				change_color(TOOL_X_I,TOOL_X_F,BUCKET_Y_I,SQUARE_Y_F,RED,BLACK, getScreenBuffer());
				change_color(TOOL_X_I, TOOL_X_F, CIRCLE_Y_I, CIRCLE_Y_F, BLACK, RED, getScreenBuffer());
				tool = CIRCLE;
			}
		}
	}

	if ( (mouse_t.x_mouse >= TOOL_X_I) && (mouse_t.x_mouse <= TOOL_X_F) )
	{
		if ( (mouse_t.y_mouse >= SQUARE_Y_I) && (mouse_t.y_mouse <= SQUARE_Y_F))
		{
			if (mouse_t.LB == 1)
			{
				change_color(TOOL_X_I,TOOL_X_F,BUCKET_Y_I,SQUARE_Y_F,RED,BLACK, getScreenBuffer());
				change_color(TOOL_X_I, TOOL_X_F, SQUARE_Y_I, SQUARE_Y_F, BLACK, RED, getScreenBuffer());
				tool = SQUARE;
			}
		}
	}

	if ( (mouse_t.x_mouse >= TOOL_X_I) && (mouse_t.x_mouse <= TOOL_X_F) )
	{
		if ( (mouse_t.y_mouse >= UNDO_Y_I) && (mouse_t.y_mouse <= UNDO_Y_F))
		{
			if (mouse_t.LB == 1)
			{
				undo();
			}
		}
	}

	if ( (mouse_t.x_mouse >= TOOL_X_I) && (mouse_t.x_mouse <= TOOL_X_F) )
	{
		if ( (mouse_t.y_mouse >= UNDO_Y_I) && (mouse_t.y_mouse <= UNDO_Y_F))
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
	if ( (mouse_t.x_mouse >= BLACK_X_I) && (mouse_t.x_mouse <= BLACK_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
		{
			if (mouse_t.LB == 1)
			{
				colour = BLACK;
			}
		}
	}

	if ( (mouse_t.x_mouse >= GRAY_X_I) && (mouse_t.x_mouse <= GRAY_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
		{
			if (mouse_t.LB == 1)
			{
				//GRAY
				colour = GRAY;
			}
		}
	}

	if ( (mouse_t.x_mouse >= RED_X_I) && (mouse_t.x_mouse <= RED_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
		{
			if (mouse_t.LB == 1)
			{
				//RED
				colour = RED;
			}
		}
	}

	if ( (mouse_t.x_mouse >= ORANGE_X_I) && (mouse_t.x_mouse <= ORANGE_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
		{
			if (mouse_t.LB == 1)
			{
				//ORANGE
				colour = ORANGE;
			}
		}
	}

	if ( (mouse_t.x_mouse >= BLUE_X_I) && (mouse_t.x_mouse <= BLUE_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
		{
			if (mouse_t.LB == 1)
			{
				//BLUE
				colour = BLUE;
			}
		}
	}
	if ( (mouse_t.x_mouse >= GREEN_X_I) && (mouse_t.x_mouse <= GREEN_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
		{
			if (mouse_t.LB == 1)
			{
				//GREEN
				colour = GREEN;
			}
		}
	}

	if ( (mouse_t.x_mouse >= YELLOW_X_I) && (mouse_t.x_mouse <= YELLOW_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
		{
			if (mouse_t.LB == 1)
			{
				//YELLOW
				colour = YELLOW;
			}
		}
	}

	if ( (mouse_t.x_mouse >= PURPLE_X_I) && (mouse_t.x_mouse <= PURPLE_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
		{
			if (mouse_t.LB == 1)
			{
				//PURPLE
				colour = PURPLE;
			}
		}
	}

	if ( (mouse_t.x_mouse >= PINK_X_I) && (mouse_t.x_mouse <= PINK_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
		{
			if (mouse_t.LB == 1)
			{
				//PINK
				colour = PINK;
			}
		}
	}

	if ( (mouse_t.x_mouse >= BROWN_X_I) && (mouse_t.x_mouse <= BROWN_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
		{
			if (mouse_t.LB == 1)
			{
				//BROWN
				colour = BROWN;
			}
		}
	}

	if ( (mouse_t.x_mouse >= WHITE_X_I) && (mouse_t.x_mouse <= WHITE_X_F) )
	{
		if ( (mouse_t.y_mouse >= COLOR_MAX) && (mouse_t.y_mouse <= getVRes()))
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
	drawBitmap(bitmaps.frame, INITIAL, INITIAL, ALIGN_LEFT, human_machine);
	human_machine = human_machine + (getHRes() - CLEAN_TIMER) * 2;
	screen_buffer = screen_buffer + (getHRes() - CLEAN_TIMER) * 2;

	for(; a < CLEAN_TIMER; a++)
	{
		for (; l < CLEAN_TIMER;l++)
		{
			*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
			screen_buffer+=2;
			human_machine+=2;
		}
		l = 0;
		screen_buffer += getHRes() * 2 - CLEAN_TIMER * 2;
		human_machine += getHRes() * 2 - CLEAN_TIMER * 2;
	}

	screen_buffer = getScreenBuffer();

	drawMouse(numbers[contador], getHRes() - 60, 30, ALIGN_LEFT, screen_buffer);

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
	drawBitmap(bitmaps.frame, INITIAL, INITIAL, ALIGN_LEFT, human_machine);
	human_machine = human_machine + (getHRes() - CLEAN_TIMER) * 2;
	screen_buffer = screen_buffer + (getHRes() - CLEAN_TIMER) * 2;
	for(; a < CLEAN_TIMER; a++)
	{
		for (; l < CLEAN_TIMER;l++)
		{
			*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
			screen_buffer+=2;
			human_machine+=2;
		}
		l = 0;
		screen_buffer += getHRes() * 2 - CLEAN_TIMER * 2;
		human_machine += getHRes() * 2 - CLEAN_TIMER * 2;
	}
	screen_buffer = getScreenBuffer();
	drawMouse(numbers[nr1], getHRes() - 60, 30, ALIGN_LEFT, screen_buffer);
	drawMouse(numbers[nr2], getHRes() - 30, 30, ALIGN_LEFT, screen_buffer);
	/*
	screen_to_mouse(screen_buffer, getMouseBuffer());
	drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, getMouseBuffer());
	mouse_to_video(getMouseBuffer(), getVideoMem());
	 */

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
			drawMouse(key_scancode[KEY_Q], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'W':
		{
			drawMouse(key_scancode[KEY_W], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'E':
		{
			drawMouse(key_scancode[KEY_E], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'R':
		{
			drawMouse(key_scancode[KEY_R], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'T':
		{
			drawMouse(key_scancode[KEY_T], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'Y':
		{
			drawMouse(key_scancode[KEY_Y], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'U':
		{
			drawMouse(key_scancode[KEY_U], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'I':
		{
			drawMouse(key_scancode[KEY_I], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'O':
		{
			drawMouse(key_scancode[KEY_O], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'P':
		{
			drawMouse(key_scancode[KEY_P], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'A':
		{
			drawMouse(key_scancode[KEY_A], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'S':
		{
			drawMouse(key_scancode[KEY_S], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'D':
		{
			drawMouse(key_scancode[KEY_D], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'F':
		{
			drawMouse(key_scancode[KEY_F], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'G':
		{
			drawMouse(key_scancode[KEY_G], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'H':
		{
			drawMouse(key_scancode[KEY_H], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'J':
		{
			drawMouse(key_scancode[KEY_J], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'K':
		{
			drawMouse(key_scancode[KEY_K], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'L':
		{
			drawMouse(key_scancode[KEY_L], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'Z':
		{
			drawMouse(key_scancode[KEY_Z], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'X':
		{
			drawMouse(key_scancode[KEY_X], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'C':
		{
			drawMouse(key_scancode[KEY_C], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'V':
		{
			drawMouse(key_scancode[KEY_V], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'B':
		{
			drawMouse(key_scancode[KEY_B], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'N':
		{
			drawMouse(key_scancode[KEY_N], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'M':
		{
			drawMouse(key_scancode[KEY_M], START_ARRAY_X + espaco, START_ARRAY_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
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
		*green = ERASE_NAME_X;
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
		*green = START_NAME_Y;
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
			drawMouse(key_scancode[KEY_Q], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'W':
		{
			drawMouse(key_scancode[KEY_W], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'E':
		{
			drawMouse(key_scancode[KEY_E], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'R':
		{
			drawMouse(key_scancode[KEY_R], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'T':
		{
			drawMouse(key_scancode[KEY_T], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'Y':
		{
			drawMouse(key_scancode[KEY_Y], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'U':
		{
			drawMouse(key_scancode[KEY_U], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'I':
		{
			drawMouse(key_scancode[KEY_I], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'O':
		{
			drawMouse(key_scancode[KEY_O], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'P':
		{
			drawMouse(key_scancode[KEY_P], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'A':
		{
			drawMouse(key_scancode[KEY_A], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'S':
		{
			drawMouse(key_scancode[KEY_S], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'D':
		{
			drawMouse(key_scancode[KEY_D], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'F':
		{
			drawMouse(key_scancode[KEY_F], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'G':
		{
			drawMouse(key_scancode[KEY_G], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'H':
		{
			drawMouse(key_scancode[KEY_H], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'J':
		{
			drawMouse(key_scancode[KEY_J], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'K':
		{
			drawMouse(key_scancode[KEY_K], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'L':
		{
			drawMouse(key_scancode[KEY_L], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'Z':
		{
			drawMouse(key_scancode[KEY_Z], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'X':
		{
			drawMouse(key_scancode[KEY_X], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'C':
		{
			drawMouse(key_scancode[KEY_C], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'V':
		{
			drawMouse(key_scancode[KEY_V], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'B':
		{
			drawMouse(key_scancode[KEY_B], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'N':
		{
			drawMouse(key_scancode[KEY_N], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'M':
		{
			drawMouse(key_scancode[KEY_M], START_NAME_X + espaco, START_NAME_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
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
			drawMouse(key_scancode[KEY_Q], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'W':
		{
			drawMouse(key_scancode[KEY_W], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'E':
		{
			drawMouse(key_scancode[KEY_E], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'R':
		{
			drawMouse(key_scancode[KEY_R], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'T':
		{
			drawMouse(key_scancode[KEY_T], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'Y':
		{
			drawMouse(key_scancode[KEY_Y], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'U':
		{
			drawMouse(key_scancode[KEY_U], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'I':
		{
			drawMouse(key_scancode[KEY_I], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'O':
		{
			drawMouse(key_scancode[KEY_O], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'P':
		{
			drawMouse(key_scancode[KEY_P], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'A':
		{
			drawMouse(key_scancode[KEY_A], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'S':
		{
			drawMouse(key_scancode[KEY_S], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'D':
		{
			drawMouse(key_scancode[KEY_D], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'F':
		{
			drawMouse(key_scancode[KEY_F], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'G':
		{
			drawMouse(key_scancode[KEY_G], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'H':
		{
			drawMouse(key_scancode[KEY_H], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'J':
		{
			drawMouse(key_scancode[KEY_J], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'K':
		{
			drawMouse(key_scancode[KEY_K], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'L':
		{
			drawMouse(key_scancode[KEY_L], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'Z':
		{
			drawMouse(key_scancode[KEY_Z], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'X':
		{
			drawMouse(key_scancode[KEY_X], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'C':
		{
			drawMouse(key_scancode[KEY_C], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'V':
		{
			drawMouse(key_scancode[KEY_V], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'B':
		{
			drawMouse(key_scancode[KEY_B], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'N':
		{
			drawMouse(key_scancode[KEY_N], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'M':
		{
			drawMouse(key_scancode[KEY_M], START_GUESS_X + espaco, START_GUESS_Y, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		}
	}
}

Bitmap* randImage()
{
	int random = rand() % NUMBER_IMAGES;
	int i;

	switch(random)
	{
	case 0:
	{
		i = 4;
		guess_ai[0] = 'D';
		guess_ai[1] = 'O';
		guess_ai[2] = 'G';
		guess_ai[3] = '0';
		for (; i < 10; i++)
		{
			guess_ai[i] = '0';
		}
		return loadBitmap(IMAGES_PATH"0.bmp");
	}
	case 1:
	{
		i = 6;
		guess_ai[0] = 'P';
		guess_ai[1] = 'U';
		guess_ai[2] = 'S';
		guess_ai[3] = 'S';
		guess_ai[4] = 'Y';
		guess_ai[5] = '0';
		for (; i < 10; i++)
		{
			guess_ai[i] = '0';
		}
		return loadBitmap(IMAGES_PATH"1.bmp");
	}
	case 2:
	{
		i = 7;
		guess_ai[0] = 'C';
		guess_ai[1] = 'I';
		guess_ai[2] = 'G';
		guess_ai[3] = 'A';
		guess_ai[4] = 'N';
		guess_ai[5] = 'O';
		guess_ai[6] = '0';
		for (; i < 10; i++)
		{
			guess_ai[i] = '0';
		}
		return loadBitmap(IMAGES_PATH"2.bmp");
	}
	case 3:
	{
		i = 6;
		guess_ai[0] = 'F';
		guess_ai[1] = 'I';
		guess_ai[2] = 'O';
		guess_ai[3] = 'R';
		guess_ai[4] = 'A';
		guess_ai[5] = '0';
		for (; i < 10; i++)
		{
			guess_ai[i] = '0';
		}
		return loadBitmap(IMAGES_PATH"3.bmp");
	}
	case 4:
	{
		i = 5;
		guess_ai[0] = 'M';
		guess_ai[1] = 'I';
		guess_ai[2] = 'C';
		guess_ai[3] = 'O';
		guess_ai[4] = '0';
		for (; i < 10; i++)
		{
			guess_ai[i] = '0';
		}
		return loadBitmap(IMAGES_PATH"4.bmp");
	}
	case 5:
	{
		i = 4;
		guess_ai[0] = 'S';
		guess_ai[1] = 'A';
		guess_ai[2] = 'M';
		guess_ai[3] = '0';
		for (; i < 10; i++)
		{
			guess_ai[i] = '0';
		}
		return loadBitmap(IMAGES_PATH"5.bmp");
	}
	case 6:
	{
		i = 7;
		guess_ai[0] = 'T';
		guess_ai[1] = 'A';
		guess_ai[2] = 'Y';
		guess_ai[3] = 'L';
		guess_ai[4] = 'O';
		guess_ai[5] = 'R';
		guess_ai[6] = '0';
		for (; i < 10; i++)
		{
			guess_ai[i] = '0';
		}
		return loadBitmap(IMAGES_PATH"6.bmp");
	}
	case 7:
	{
		i = 5;
		guess_ai[0] = 'C';
		guess_ai[1] = 'A';
		guess_ai[2] = 'G';
		guess_ai[3] = 'E';
		guess_ai[4] = '0';
		for (; i < 10; i++)
		{
			guess_ai[i] = '0';
		}
		return loadBitmap(IMAGES_PATH"7.bmp");
	}
	case 8:
	{
		i = 9;
		guess_ai[0] = 'L';
		guess_ai[1] = 'E';
		guess_ai[2] = 'N';
		guess_ai[3] = 'H';
		guess_ai[4] = 'A';
		guess_ai[5] = 'D';
		guess_ai[6] = 'O';
		guess_ai[7] = 'R';
		guess_ai[8] = '0';
		for (; i < 10; i++)
		{
			guess_ai[i] = '0';
		}
		return loadBitmap(IMAGES_PATH"8.bmp");
	}
	case 9:
	{
		i = 4;
		guess_ai[0] = 'K';
		guess_ai[1] = 'I';
		guess_ai[2] = 'M';
		guess_ai[3] = '0';
		for (; i < 10; i++)
		{
			guess_ai[i] = '0';
		}
		return loadBitmap(IMAGES_PATH"9.bmp");
	}
	}
}

void cleanWord()
{
	int k = 0;
	for (; k < 10; k++)
	{
		word[k] = '1';
	}
	length_word = 0;
}

void cleanGuess()
{
	int k = 0;
	for (; k < 10; k++)
	{
		guess_ai[k] = '1';
	}
}

void cleanName()
{
	int k = 0;
	for (; k < 10; k++)
	{
		name[k] = '1';
	}
	length = 0;
}

void printName(bitmap_struct bitmaps, Bitmap ** key_scancode, int key)
{
	char * screen_buffer = getScreenBuffer();
	char * mouse_buffer = getMouseBuffer();
	char * video_memory = getVideoMem();
	if (length == 10)
	{
		if (key == KEY_ENTER || key == KEY_NUM_ENTER)
		{
			length++;
			name[length] = '\0';
			OPTION = MAIN_MENU;
		}
	}
	else if ((key == KEY_ENTER || key == KEY_NUM_ENTER) && (length > 0))
	{
		length++;
		name[length] = '\0';
		drawBitmap(bitmaps.frame, INITIAL,INITIAL, ALIGN_LEFT, screen_buffer);
		WriteArrayFrame(name, length, key_scancode, bitmaps);
		if (ai_or_pvp == 1)
			OPTION = HEAD_TO_HEAD;
		else
		{
			OPTION = HUMAN_VS_MACHINE;
			screen_to_mouse(screen_buffer, mouse_buffer);
			drawMouse(bitmaps.mouse, mouse_t.x_mouse, mouse_t.y_mouse, ALIGN_LEFT, mouse_buffer);

			mouse_to_video(mouse_buffer, video_memory);
		}
	}
	else {

		if (get_char(key) >= 'A' && get_char(key) <= 'Z')
		{
			name[length] = get_char(key);
			WriteArray(name, length, key_scancode, bitmaps);
			length++;
		}
		if (key == KEY_BACKSPACE)
		{
			unsigned int l = 0;
			unsigned int a = 0;
			char * human_machine = getHumanMachine();
			drawBitmap(bitmaps.pre_head_to_head, INITIAL, INITIAL, ALIGN_LEFT, human_machine);
			human_machine = human_machine + ERASE_NAME_X * 2 + getHRes() * ERASE_NAME_Y * 2;
			screen_buffer = screen_buffer + ERASE_NAME_X * 2 + getHRes() * ERASE_NAME_Y * 2;
			for(; a < (581 - ERASE_NAME_Y); a++)
			{
				for (; l < (719 - ERASE_NAME_X);l++)
				{
					*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
					screen_buffer+=2;
					human_machine+=2;
				}
				l = 0;
				screen_buffer += getHRes() * 2 - (719 - ERASE_NAME_X) * 2;
				human_machine += getHRes() * 2 - (719 - ERASE_NAME_X) * 2;
			}
			cleanName();
		}
	}
}

void printHead(bitmap_struct bitmaps, Bitmap ** key_scancode, int key)
{
	char * screen_buffer = getScreenBuffer();
	char * mouse_buffer = getMouseBuffer();
	char * video_memory = getVideoMem();
	unsigned int l = 0;
	unsigned int a = 0;
	char * human_machine = getHumanMachine();
	int j = 0;
	if (key == KEY_BACKSPACE)
	{
		drawBitmap(bitmaps.frame, INITIAL, INITIAL, ALIGN_LEFT, human_machine);
		human_machine = human_machine + ERASE_GUESS_X * 2 + getHRes() * ERASE_GUESS_Y * 2;
		screen_buffer = screen_buffer + ERASE_GUESS_X * 2 + getHRes() * ERASE_GUESS_Y * 2;
		for(; a < (183 - ERASE_GUESS_Y); a++)
		{
			for (; l < (470 - ERASE_GUESS_X);l++)
			{
				*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
				screen_buffer+=2;
				human_machine+=2;
			}
			l = 0;
			screen_buffer += getHRes() * 2 - (470 - ERASE_GUESS_X) * 2;
			human_machine += getHRes() * 2 - (470 - ERASE_GUESS_X) * 2;
		}
		l = 0;
		a = 0;

		//cleanWord();
	}
	if (key == KEY_SPACE)
	{
		tries++;
		drawBitmap(bitmaps.frame, INITIAL, INITIAL, ALIGN_LEFT, human_machine);
		human_machine = human_machine + ERASE_GUESS_X * 2 + getHRes() * ERASE_GUESS_Y * 2;
		screen_buffer = screen_buffer + ERASE_GUESS_X * 2 + getHRes() * ERASE_GUESS_Y * 2;
		for(; a < (183 - ERASE_GUESS_Y); a++)
		{
			for (; l < (470 - ERASE_GUESS_X);l++)
			{
				*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
				screen_buffer+=2;
				human_machine+=2;
			}
			l = 0;
			screen_buffer += getHRes() * 2 - (470 - ERASE_GUESS_X) * 2;
			human_machine += getHRes() * 2 - (470 - ERASE_GUESS_X) * 2;
		}
		a = 0;
		l = 0;

		cleanWord();
	}

	if (get_char(key) >= 'A' && get_char(key) <= 'Z')
	{
		word[length_word] = get_char(key);
		WriteArrayFrame2(word, length_word, key_scancode, bitmaps);
		length_word++;
	}

	if (key == KEY_TAB)
	{
		int score_conta;
		score_conta = score(contador_high);
		createBitmap();
		drawBitmap(bitmaps.win, INITIAL,INITIAL, ALIGN_LEFT, getScreenBuffer());
		OPTION = STATIC;
		tries = 0;
		cleanName();
		cleanWord();
		RTC_COUNTER = START_RTC_COUNTER;
		tries = 0;
		tentativas = 0;
	}
}

void printMachine(bitmap_struct bitmaps, Bitmap ** key_scancode, int key, Bitmap ** numbers)
{
	if (OPTION == HUMAN_VS_MACHINE)
	{
		/*if (verdadeiro == 1)
		{
			Bitmap* temp2 = randImage();
			printf("entrei\n");
			return temp2;
		}
		 */
		unsigned int l = 0;
		static int temp = 0;
		unsigned int a = 0;
		char * human_machine = getHumanMachine();
		char * screen_buffer = getScreenBuffer();
		int j = 0;
		int bool = 1; //0 acertou, 1 falhou
		if (key == KEY_BACKSPACE)
		{
			drawBitmap(bitmaps.frame, INITIAL, INITIAL, ALIGN_LEFT, human_machine);
			human_machine = human_machine + ERASE_GUESS_X * 2 + getHRes() * ERASE_GUESS_Y * 2;
			screen_buffer = screen_buffer + ERASE_GUESS_X * 2 + getHRes() * ERASE_GUESS_Y * 2;
			for(; a < (183 - ERASE_GUESS_Y); a++)
			{
				for (; l < (470 - ERASE_GUESS_X);l++)
				{
					*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
					screen_buffer+=2;
					human_machine+=2;
				}
				l = 0;
				screen_buffer += getHRes() * 2 - (470 - ERASE_GUESS_X) * 2;
				human_machine += getHRes() * 2 - (470 - ERASE_GUESS_X) * 2;
			}
			l = 0;
			a = 0;

			cleanWord();
		}
		if (key == KEY_ENTER)
		{
			int i = 0;
			if (temp == 0)
			{
				temp++;
				tries--;
			}
			word[length_word] = '0';
			j = 0;
			for (; j < 11; j++)
			{
				if ((guess_ai[j] == '0') && (word[j] == '0'))
				{
					bool = 0;
					break;
				}
				if (word[j] != guess_ai[j])
				{
					bool = 1;
					break;
				}
				if (guess_ai[j] == '0')
				{
					bool = 1;
					break;
				}
			}
			if (bool == 1)
			{
				tries++;
				human_machine = getHumanMachine();
				screen_buffer = getScreenBuffer();
				drawBitmap(bitmaps.frame, INITIAL, INITIAL, ALIGN_LEFT, human_machine);
				human_machine = human_machine + ERASE_GUESS_X * 2 + getHRes() * ERASE_GUESS_Y * 2;
				screen_buffer = screen_buffer + ERASE_GUESS_X * 2 + getHRes() * ERASE_GUESS_Y * 2;
				for(; a < (183 - ERASE_GUESS_Y); a++)
				{
					for (; l < (470 - ERASE_GUESS_X);l++)
					{
						*(uint16_t *)screen_buffer = *(uint16_t *)human_machine;
						screen_buffer+=2;
						human_machine+=2;
					}
					l = 0;
					screen_buffer += getHRes() * 2 - (470 - ERASE_GUESS_X) * 2;
					human_machine += getHRes() * 2 - (470 - ERASE_GUESS_X) * 2;
				}
				a = 0;
				l = 0;
				cleanWord();
			}
			else
			{
				position_t jogador;
				int score_conta;
				score_conta = score(contador_high);
				jogador.score = score_conta;
				for(i; i < 10; i++)
				{
					jogador.name[i] = name[i];
					jogador.word[i] = word[i];
				}
				jogador.day = day;
				jogador.month = month;
				jogador.year = year;
				jogador.hour = hour;
				jogador.minutes = minutes;

				//chamar is highscore

				drawBitmap(bitmaps.win, INITIAL,INITIAL, ALIGN_LEFT, getScreenBuffer());
				displayScore(numbers, jogador, key_scancode);

				OPTION = STATIC;
				tries = 0;
				cleanName();
				cleanWord();
				RTC_COUNTER = START_RTC_COUNTER;
				tries = 0;
				tentativas = 0;
				contador_c = CANVAS_Y_F;
				verdadeiro = 1;

				//acertou
			}
		}

		if (get_char(key) >= 'A' && get_char(key) <= 'Z')
		{
			word[length_word] = get_char(key);
			WriteArrayFrame2(word, length_word, key_scancode, bitmaps);
			length_word++;
		}
	}

}

void displayScore(Bitmap ** numbers, position_t player, Bitmap ** key_scancode)
{
	int score = player.score;
	int y = 800;
	int x = getVRes() / 2;
	int i = 0;
	char * screen_buffer = getScreenBuffer();
	while(score != 0)
	{
		int temp = score % 10;
		score = score / 10;
		drawMouse(numbers[temp], y, getVRes() / 2, ALIGN_LEFT, screen_buffer);
		y = y - SPACE_KEYS;
	}

	espaco = 0;
	for(; i <= 10; i++)
	{
		switch (player.name[i])
		{
		case 'Q':
		{
			drawMouse(key_scancode[KEY_Q], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'W':
		{
			drawMouse(key_scancode[KEY_W], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'E':
		{
			drawMouse(key_scancode[KEY_E], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'R':
		{
			drawMouse(key_scancode[KEY_R], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'T':
		{
			drawMouse(key_scancode[KEY_T], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'Y':
		{
			drawMouse(key_scancode[KEY_Y], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'U':
		{
			drawMouse(key_scancode[KEY_U], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'I':
		{
			drawMouse(key_scancode[KEY_I], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'O':
		{
			drawMouse(key_scancode[KEY_O], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'P':
		{
			drawMouse(key_scancode[KEY_P], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'A':
		{
			drawMouse(key_scancode[KEY_A], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'S':
		{
			drawMouse(key_scancode[KEY_S], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'D':
		{
			drawMouse(key_scancode[KEY_D], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'F':
		{
			drawMouse(key_scancode[KEY_F], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'G':
		{
			drawMouse(key_scancode[KEY_G], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'H':
		{
			drawMouse(key_scancode[KEY_H], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'J':
		{
			drawMouse(key_scancode[KEY_J], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'K':
		{
			drawMouse(key_scancode[KEY_K], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'L':
		{
			drawMouse(key_scancode[KEY_L], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'Z':
		{
			drawMouse(key_scancode[KEY_Z], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'X':
		{
			drawMouse(key_scancode[KEY_X], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'C':
		{
			drawMouse(key_scancode[KEY_C], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'V':
		{
			drawMouse(key_scancode[KEY_V], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'B':
		{
			drawMouse(key_scancode[KEY_B], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'N':
		{
			drawMouse(key_scancode[KEY_N], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		case 'M':
		{
			drawMouse(key_scancode[KEY_M], 100 + espaco, x, ALIGN_LEFT, screen_buffer);
			espaco = espaco + SPACE_KEYS;
			break;
		}
		}
	}



}
