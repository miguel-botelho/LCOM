#include"mouse.h"

int mhook_id = 0x01;


int mouse_subscribe_int(){
	//para nao perder o valor original de khook_id (vai ser preciso para depois reconhecer a notificacao)
	int hook_temp = mhook_id;

	if (OK == sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mhook_id))
	{
		if (OK == sys_irqenable(&mhook_id))
		{
			return BIT(hook_temp);
		}
	}
	return -1;

}

int mouse_unsubscribe_int(){

	if (OK == sys_irqdisable(&mhook_id))
		if (OK == sys_irqrmpolicy(&mhook_id))
			return 0;
	return -1;
}

int mouse_int_handler(unsigned long cmd){
	int cmd_receive = 0;
	int cmd_receive2 = 0;
	int nr_tentativas = 0;


	while(1)
	{
		mouse_send_first_command();

		while (nr_tentativas < 5)
		{
			mouse_send_command(cmd);

			tickdelay(micros_to_ticks(DELAY_US));

			cmd_receive2 = mouse_cmd_receive();

			if(MOUSE_DATA == (MOUSE_DATA & cmd_receive2))
			{
				if (cmd_receive2 == ERROR)
				{
					nr_tentativas++;
					continue;
				}
				else break;
			}
			else continue;
		}
		if (cmd_receive2 == NACK)
			continue;
		break;
	}

}

int mouse_send_command(unsigned long cmd){

	unsigned long stat;

	while(1)
	{
		sys_inb(STAT_REG, &stat); /*assuming it returns OK*/
		/*loop while 8042 input buffer is not empty*/
		if ((stat & IBF) == 0)
		{
			sys_outb(COMMAND_PORT, cmd);
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}

}


int mouse_send_first_command(){

	unsigned long stat;


	while(1)
	{
		sys_inb(STAT_REG, &stat); /*assuming it returns OK*/
		/*loop while 8042 input buffer is not empty*/
		if ((stat & IBF) == 0)
		{
			sys_outb(0x64, MC);
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int mouse_cmd_receive(){
	unsigned long stat = 0;
	unsigned long data = 0;

	while(1)
	{
		sys_inb(STAT_REG, &stat); /*assuming it returns OK*/
		/*loop while 8042 input buffer is not empty*/
		if (stat & OBF)
		{
			sys_inb(OUT_BUF, &data); /*assuming it returns OK*/
			if ((stat & (PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return -1;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

void mouse_printf(char byte1, char byte2, char byte3){

	printf("B1=0x%2x",(byte1 & 0x0F));
	printf("B2=0x%3x", byte2);
	printf("B3=0x%3x", byte3);
	printf("LB=%2u", (byte1 & 0x01));
	printf("MB=%2u", (byte1 & 0x04));
	printf("RB=%2u", (byte1 & 0x02));
	printf("XOV=%2u", (byte1 & 0x40));
	printf("YOV=%2u", (byte1 & 0x80));


	if (0x10 == (0x10 & byte1))
	{
		printf("X=-%3u", byte2);
	}
	else
	{
		printf("X=%3u", byte2);
	}

	if (0x20 == (0x20 & byte1))
	{
		printf("Y=-%3u", byte3);
	}
	else
	{
		printf("Y=%3u", byte3);
	}
	printf("\n");
}
