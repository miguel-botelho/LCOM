/**
 * @file mouse_struct.h
 * @author Miguel Botelho and Antonio Ramadas
 * @brief The file containing the mouse struct
 */

#ifndef __MOUSE_STRUCT_H
#define __MOUSE_STRUCT_H

/**
 * @brief the struct that has the mouse (all of its properties)
 */
typedef struct
{
	int LB;
	int RB;
	int MB;
	int XOV;
	int YOV;
	int x;
	int y;
	int x_mouse;
	int y_mouse;
} mouse_st;

mouse_st mouse_t;

#endif /* __MOUSE_STRUCT_H */
