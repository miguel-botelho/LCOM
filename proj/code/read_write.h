#ifndef __READ_WRITE_H
#define __READ_WRITE_H

#include "struct_bmp.h"
#include "struct_scores.h"

/**
 * @brief Read an array from a file
 *
 * Read the array with the size (the argument) of the file.
 *
 * @param *fp file to be read
 * @param size size of the array
 * @param *a array to be filled
 *
 */
void read_array(FILE *fp, int size, color_st *a);

/**
 * @brief Fill a struct from a file
 *
 * Read a struct (with the score information) from the file.
 *
 * @param *fp file to be read
 * @param *t struct to be filled
 *
 */
void read_position(FILE *fp, position_t *t);

/**
 * @brief Fill a struct from a file
 *
 * Read a struct (with the score information) from the file.
 *
 * @param *t struct to be filled
 *
 */
void read_all(scores_t *t);


/**
 * @brief Write an array from a file
 *
 * Write the array with the size (the argument) of the file.
 *
 * @param *fp file to be written
 * @param size size of the array
 * @param *a array that has the information
 *
 */
void write_array(FILE *fp, int size, color_st *a);

/**
 * @brief Write a struct to a file
 *
 * Write a struct (with the score information) to a file.
 *
 * @param *fp file to be written
 * @param *t struct that has the information to be written
 *
 */
void write_position(FILE *fp, position_t *t);

/**
 * @brief Write a struct to a file
 *
 * Write a struct (with the highcores) to a file.
 *
 * @param *t struct that has the information to be written
 *
 */
void write_all(scores_t *t);

#endif
