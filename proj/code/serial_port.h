#ifndef __SERIAL_PORT_H
#define __SERIAL_PORT_H

#include"serial_port_macros.h"
#include"lib.h"
#include"global_variables.h"
#include"mouse_struct.h"

extern int key;
extern mouse_st mouse_t;

//return 0 se recebeu alguma coisa
int com1_receive();

/**
 * @brief Configures the serial port
 *
 * Configures the COM1 and COM2 of the serial port.
 *
 */
void sp_config();

//interrupts

/**
 * @brief Receive the bytes sent to COM1
 *
 * Loops until all bytes are read. The parameters are passed as reference and changed.
 *
 * @param *size_array Size of the new array
 * @param *a New array with the bytes received
 * @return Return 0 upon success and non-zero otherwise
 */
int com1_receive_interrupt(int *size_array, char *a);

/**
 * @brief Send a char to COM1
 *
 * Send the argument to COM1
 *
 * @param a Argument to be sent
 */
void com1_send_interrupt(char a);

/**
 * @brief Receive the bytes sent to COM2
 *
 * Loops until all bytes are read. The parameters are passed as reference and changed.
 *
 * @param *size_array Size of the new array
 * @param *a New array with the bytes received
 * @return Return 0 upon success and non-zero otherwise
 */
int com2_receive_interrupt(int *size_array, char *a);

/**
 * @brief Send a char to COM1
 *
 * Send the argument to COM1
 *
 * @param a Argument to be sent
 */
void com2_send_interrupt(char a);

#endif /* __SERIAL_PORT_H */
