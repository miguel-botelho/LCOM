/**
 * @file serial_port_macros.h
 * @author Miguel Botelho and Antonio Ramadas
 * @brief The file containing the macros for the serial port
 */

#ifndef __SERIAL_PORT_MACROS_H
#define __SERIAL_PORT_MACROS_H

#define BIT(n) 									(0x01<<(n))

#define BASE_ADDRESS_COM1						0x3F8 //to 0x3FF
#define BASE_ADDRESS_COM2						0x2F8 //to 0x2FF

// -----------------------------UART Registers-----------------------------
#define RECEIVER_BUFFER							0
#define TRANSMITTER_HOLDING						0
#define INTERRUPT_ENABLE						1
#define	INTERRUPT_IDENTIFICATION				2
#define	FIFO_CONTROL							2
#define LINE_CONTROL							3
#define LINE_STATUS								5
#define DLSB									0 //Divisor Latch Least Significant Byte
#define DMSB									1 //Divisor Latch Most Significant Byte

// -----------------------------Line Control Register (LCR)-----------------------------
#define WORD_LENGTH_5							0
#define WORD_LENGTH_6							BIT(0)
#define WORD_LENGTH_7							BIT(1)
#define WORD_LENGTH_8							(BIT(1) | BIT(0))

#define STOP_BITS_1								0
#define STOP_BITS_2								BIT(2)

#define PARITY_NONE								0
#define PARITY_ODD								BIT(3)
#define PARITY_EVEN								(BIT(4) | BIT(3))
#define PARITY_1								(BIT(5) | BIT(3))
#define PARITY_0								(BIT(5) | BIT(4) | BIT(3))

#define BREAK_ENABLE							BIT(6)

#define DL										BIT(7)
#define DATA									0

// -----------------------------Line Status Register (LSR)-----------------------------
#define RECEIVER_READY							BIT(0)
#define OVERRUN_ERROR							BIT(1)
#define PARITY_ERROR							BIT(2)
#define FRAMING_ERROR							BIT(3)
#define TRANSMITTER_EMPTY						BIT(5)

// -----------------------------Interrupt Enable Register (IER)-----------------------------
#define ENABLE_RECEIVED_DATA_INTERRUPT			BIT(0)
#define ENABLE_TRANSMITTER_EMPTY_INTERRUPT		BIT(1)
#define ENABLE_RECEIVER_LINE_SATUS_INTERRUPT	BIT(2)

// -----------------------------Interrupt Identification Register (IIR)-----------------------------
#define INTERRUPT_STATUS_PENDING				0
#define INTERRUPT_STATUS_NOT_PENDING			BIT(0)

#define INTERRUPT_ORIGIN_MODEM					0
#define INTERRUPT_ORIGIN_TRANSMITTER_EMPTY		BIT(1)
#define INTERRUPT_ORIGIN_CHARACTER_TIMEOUT		BIT(3)
#define INTERRUPT_ORIGIN_RECEIVED_DATA			BIT(2)
#define INTERRUPT_ORIGIN_LINE_STATUS			(BIT(2) | BIT(1))

#define NO_FIFO									0
#define FIFO_UNUSABLE							BIT(7)
#define FIFO_ENABLED							(BIT(7) | BIT(6))

// -----------------------------FIFO Control Register (FCR)-----------------------------
#define ENABLE_FIFO								BIT(0)
#define CLEAR_RECEIVE_FIFO						BIT(1)
#define CLEAR_TRANSMIT_FIFO						BIT(2)

#define FIFO_INTERRUPT_TRIGGER_LEVEL_1			0
#define FIFO_INTERRUPT_TRIGGER_LEVEL_4			BIT(6)
#define FIFO_INTERRUPT_TRIGGER_LEVEL_8			BIT(7)
#define FIFO_INTERRUPT_TRIGGER_LEVEL_14			(BIT(7) | BIT(6))


#endif /* __SERIAL_PORT_MACROS_H */
