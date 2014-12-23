#ifndef __READ_WRITE_H
#define __READ_WRITE_H

#include "struct_bmp.h"
#include "struct_scores.h"
extern scores_t top_highscores;

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
void read_all();

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
void write_all();

#endif
