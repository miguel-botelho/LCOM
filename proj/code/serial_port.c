#include"serial_port.h"


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
		(*size_array) = (*size_array) + 1;
		if (temp != NULL)
		{
			a = temp;
			a[n-1] = received;
		}
		else
		{
			free(a);
			printf("Error allocating memory!\n");
			return -1;
		}

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
		(*size_array) = (*size_array) + 1;
		if (temp != NULL)
		{
			a = temp;
			a[n-1] = received;
		}
		else
		{
			free(a);
			printf("Error allocating memory!\n");
			return -1;
		}

		sys_inb(BASE_ADDRESS_COM2 + INTERRUPT_IDENTIFICATION, &line_status);
	}

	(*size_array) = (*size_array) - 1;

	return 0;
}

void com2_send_interrupt(char a)
{
	sys_outb(BASE_ADDRESS_COM1, a);
}
