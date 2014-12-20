#include"serial_port.h"


void sp_config()
{
	// COM1
	//configure Line Control to activate DL, 8 bits, 2 stop bits, parity even
	sys_outb(BASE_ADDRESS_COM1 + LINE_CONTROL, DL | PARITY_EVEN | STOP_BITS_2 | WORD_LENGTH_8);

	//set the bit rate
	sys_outb(BASE_ADDRESS_COM1 + DLSB, 0x1D); //9600
	sys_outb(BASE_ADDRESS_COM1 + DMSB, 0x00);

	//configure Line Control to activate Data
	sys_outb(BASE_ADDRESS_COM1 + LINE_CONTROL, DATA | PARITY_EVEN | STOP_BITS_2 | WORD_LENGTH_8);

	//enable FIFO, clear receive FIFO, clear transmit FIFO
	sys_outb(BASE_ADDRESS_COM1 + INTERRUPT_IDENTIFICATION, FIFO_INTERRUPT_TRIGGER_LEVEL_1 | CLEAR_TRANSMIT_FIFO | CLEAR_RECEIVE_FIFO | ENABLE_FIFO);

	//enable interrupts
	sys_outb(BASE_ADDRESS_COM1 + INTERRUPT_ENABLE, ENABLE_RECEIVER_LINE_SATUS_INTERRUPT | ENABLE_TRANSMITTER_EMPTY_INTERRUPT | ENABLE_RECEIVED_DATA_INTERRUPT);


	// COM2
	//configure Line Control to activate DL, 8 bits, 2 stop bits, parity even
	sys_outb(BASE_ADDRESS_COM2 + LINE_CONTROL, DL | PARITY_EVEN | STOP_BITS_2 | WORD_LENGTH_8);

	//set the bit rate
	sys_outb(BASE_ADDRESS_COM2 + DLSB, 0x1D); //9600
	sys_outb(BASE_ADDRESS_COM2 + DMSB, 0x00);

	//configure Line Control to activate Data
	sys_outb(BASE_ADDRESS_COM2 + LINE_CONTROL, DATA | PARITY_EVEN | STOP_BITS_2 | WORD_LENGTH_8);

	//enable FIFO, clear receive FIFO, clear transmit FIFO
	sys_outb(BASE_ADDRESS_COM2 + INTERRUPT_IDENTIFICATION, FIFO_INTERRUPT_TRIGGER_LEVEL_1 | CLEAR_TRANSMIT_FIFO | CLEAR_RECEIVE_FIFO | ENABLE_FIFO);

	//enable interrupts
	sys_outb(BASE_ADDRESS_COM2 + INTERRUPT_ENABLE, ENABLE_RECEIVER_LINE_SATUS_INTERRUPT | ENABLE_TRANSMITTER_EMPTY_INTERRUPT | ENABLE_RECEIVED_DATA_INTERRUPT);

}

int com1_receive_interrupt(int *size_array, char *a)
{
	long unsigned int line_status;
	long unsigned int received;

	*size_array = 1;
	char *temp = NULL;

	sys_inb(BASE_ADDRESS_COM1 + INTERRUPT_IDENTIFICATION, &line_status);

	while (INTERRUPT_ORIGIN_RECEIVED_DATA & line_status) // receiver ready
	{
		sys_inb(BASE_ADDRESS_COM1, &received);

		temp = (char *) realloc (a, (*size_array) * sizeof(char));
		if (temp != NULL)
		{
			a = temp;
			a[(*size_array)-1] = received;
		}
		else
		{
			free(a);
			printf("Error allocating memory!\n");
			return -1;
		}

		(*size_array) = (*size_array) + 1;

		sys_inb(BASE_ADDRESS_COM1 + INTERRUPT_IDENTIFICATION, &line_status);
	}

	(*size_array) = (*size_array) - 1;

	return 0;
}

void com1_send_interrupt(char a)
{
	sys_outb(BASE_ADDRESS_COM1, a);
}

int com2_receive_interrupt(int *size_array, char *a)
{
	long unsigned int line_status;
	long unsigned int received;

	*size_array = 1;
	char *temp = NULL;

	sys_inb(BASE_ADDRESS_COM2 + INTERRUPT_IDENTIFICATION, &line_status);

	while (INTERRUPT_ORIGIN_RECEIVED_DATA & line_status) // receiver ready
	{
		sys_inb(BASE_ADDRESS_COM2, &received);

		temp = (char *) realloc (a, (*size_array) * sizeof(char));
		if (temp != NULL)
		{
			a = temp;
			a[(*size_array)-1] = received;
		}
		else
		{
			free(a);
			printf("Error allocating memory!\n");
			return -1;
		}

		(*size_array) = (*size_array) + 1;

		sys_inb(BASE_ADDRESS_COM2 + INTERRUPT_IDENTIFICATION, &line_status);
	}

	(*size_array) = (*size_array) - 1;

	return 0;
}

void com2_send_interrupt(char a)
{
	sys_outb(BASE_ADDRESS_COM1, a);
}
