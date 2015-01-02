/**
 * @file menu_macros.h
 * @author Miguel Botelho and Antonio Ramadas
 * @brief The file containing the macros for the menu (mostly state machines)
 */

#ifndef __MENU_MACROS_H
#define __MENU_MACROS_H

#define MAIN_MENU							0
#define HUMAN_VS_MACHINE					1
#define HEAD_TO_HEAD						2
#define ONLINE								3
#define HIGHSCORES							4
#define EXIT_OPT							5 //otherwise there is a conflict
#define GET_NAME							6
#define STATIC								7

#define BUCKET								50
#define BRUSH								51
#define PENCIL								52
#define LINE								53
#define CIRCLE								54
#define	SQUARE								55
#define UNDO								56
#define REDO								57

//////////pathways///////////

#define CODE_PATH "home/lcom/proj/code/"
#define FILE_PATH CODE_PATH"files/"
#define IMAGES_PATH CODE_PATH"images/"
#define FONT_PATH IMAGES_PATH"font/word/"
#define NUMBERS_PATH IMAGES_PATH"numbers/"

//////////MENU OPTIONS (coordinates)///////////
#define INITIAL		0

#define EXIT_X_I	438
#define EXIT_X_F	591
#define EXIT_Y_I	650
#define EXIT_Y_F	716

#define HIGH_X_I	305
#define HIGH_X_F	718
#define HIGH_Y_I	555
#define HIGH_Y_F	644

#define ONLINE_X_I	341
#define ONLINE_X_F	633
#define ONLINE_Y_I	484
#define ONLINE_Y_F	550

#define HEAD_X_I	248
#define HEAD_X_F	787
#define HEAD_Y_I	412
#define HEAD_Y_F	466

#define HUMAN_X_I	149
#define HUMAN_X_F	871
#define HUMAN_Y_I	328
#define HUMAN_Y_F	396

#define TRIES_X		162
#define TRIES_Y		8
#define CLEAN_TRIES_X	40
#define CLEAN_TRIES_Y	50

#define TOOL_HANDLER_X_I	120
#define TOOL_HANDLER_X_F	1020
#define TOOL_HANDLER_Y_I	183
#define TOOL_HANDLER_Y_F	717

#define TOOL_X_I	25
#define TOOL_X_F	84

#define MINUS_Y_I	241
#define MINUS_Y_F	289

#define PLUS_Y_I	289
#define PLUS_Y_F	337

#define BUCKET_Y_I	337
#define BUCKET_Y_F	385

#define BRUSH_Y_I	385
#define BRUSH_Y_F	433

#define PENCIL_Y_I	433
#define PENCIL_Y_F	481

#define LINE_Y_I	481
#define LINE_Y_F	529

#define CIRCLE_Y_I	529
#define CIRCLE_Y_F	577

#define SQUARE_Y_I	577
#define SQUARE_Y_F	625

#define UNDO_Y_I	625
#define UNDO_Y_F	673

#define REDO_Y_I	673
#define REDO_Y_F	721


#define COLOR_MAX	720

#define BLACK_X_I	489
#define BLACK_X_F	534

#define GRAY_X_I	534
#define GRAY_X_F	582

#define	RED_X_I		582
#define RED_X_F		631

#define ORANGE_X_I	631
#define ORANGE_X_F	681

#define BLUE_X_I	681
#define BLUE_X_F	730

#define GREEN_X_I	730
#define GREEN_X_F	778

#define YELLOW_X_I	778
#define YELLOW_X_F	826

#define PURPLE_X_I	826
#define PURPLE_X_F	876

#define PINK_X_I	876
#define PINK_X_F	925

#define BROWN_X_I	925
#define BROWN_X_F	973

#define WHITE_X_I	973
#define WHITE_X_F	1024

#define CLEAN_TIMER	100

#define START_ARRAY_X	258
#define START_ARRAY_Y	492

#define SPACE_KEYS	35

#define START_NAME_X	117
#define START_NAME_Y	61

#define START_GUESS_X	117
#define START_GUESS_Y	134

#define MAX_TRIES			3
#define START_RTC_COUNTER	99
#define NUMBER_IMAGES		10

#define CANVAS_X_I	120
#define CANVAS_X_F	1020
#define CANVAS_Y_I	186
#define CANVAS_Y_F	718

#define ERASE_NAME_X	251
#define ERASE_NAME_Y	481

#define ERASE_GUESS_X	116
#define ERASE_GUESS_Y	127

#define MAX_RADIUS	100
#define MIN_RADIUS	3
#define RADIUS_INC	5


#endif
