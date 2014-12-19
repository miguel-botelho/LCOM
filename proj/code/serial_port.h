#ifndef __SERIAL_PORT_H
#define __SERIAL_PORT_H

#include"serial_port_macros.h"
#include"lib.h"

//polling

/*int com1_receive_poll(int *size_array, char *a);
int com1_send_poll(int size_array, char *a);

int com2_receive_poll(int *size_array, char *a);
int com2_send_poll(int size_array, char *a);*/


//interrupts

int com1_receive_interrupt(int *size_array, char *a);
void com1_send_interrupt(char a);

int com2_receive_interrupt(int *size_array, char *a);
void com2_send_interrupt(char a);

#endif /* __SERIAL_PORT_H */
