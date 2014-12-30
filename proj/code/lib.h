/**
 * @file lib.h
 * @author Miguel Botelho and Antonio Ramadas
 * @brief The file containing the c libraries and minix
 */

#ifndef __LIB_H
#define __LIB_H

/*
 * This header file does not have any implementation.
 * The purpose of this file is to simplify the code for the rest if the files.
 */

// Includes of minix drivers
#include <minix/drivers.h>
#include <minix/syslib.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>


// Includes of c libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#endif /* __LIB_H */
