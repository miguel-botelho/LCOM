#include"mouse.h"

int mhook_id = 0x01;
int hook_id = 0x00;

char global_bool1 = 0;
char global_bool2 = 0;

int timer_subscribe_int(void ) {

	//para nao perder o valor original de hook_id (vai ser preciso para depois reconhecer a notificacao)
	int hook_temp = hook_id;

	if (OK == sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id))
		if (OK == sys_irqenable(&hook_id))
			return BIT(hook_temp);
	return -1;
}

int timer_unsubscribe_int() {

	if (OK == sys_irqdisable(&hook_id))
		if (OK == sys_irqrmpolicy(&hook_id))
			return 0;
	return -1;
}

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
		while(nr_tentativas < 5)
		{
   			mouse_send_first_command();

			/*cmd_receive = mouse_cmd_receive();

			printf("done\n");

			if(MOUSE_DATA == (MOUSE_DATA & cmd_receive))
			{
				if (NACK == cmd_receive || ERROR == cmd_receive)
				{
					printf("cmd1\n");
					nr_tentativas++;
					continue;
				}
			} else continue;
*/
			break;
		}

		nr_tentativas = 0;

		while (nr_tentativas < 5)
		{
			mouse_send_command(cmd);

			cmd_receive2 = mouse_cmd_receive();

			if(MOUSE_DATA == (MOUSE_DATA & cmd_receive2))
			{
				if (cmd_receive2 == NACK)
				{
					nr_tentativas++;
					continue;
				}
				else break;
			}
			else continue;
		}

		if (cmd_receive2 == ERROR)
		{
			continue;
		}

		break;
	}

	return 0;
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
			sys_outb(STAT_REG, MC);
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

int mouse_clean_buffer(){
	unsigned long stat = 0;
	unsigned long data = 0;

	while(1)
	{
		sys_inb(STAT_REG, &stat); /*assuming it returns OK*/
		/*loop while 8042 input buffer is not empty*/
		if ((stat & OBF) == 0)
		{
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
		printf("clean\n");
	}
}

void mouse_printf(char a[]){

	printf("B1=0x%x ",(a[0] & 0x0F));
	printf("B2=0x%x ", a[1]);
	printf("B3=0x%x ", a[2]);
	printf("LB=%u ", (a[0] & 0x01));
	printf("MB=%u ", ((a[0] & 0x04) >> 2));
	printf("RB=%u ", ((a[0] & 0x02) >> 1));
	printf("XOV=%u ", (a[0] & 0x40));
	printf("YOV=%u ", (a[0] & 0x80));


	if (0x10 == (0x10 & a[0]))
	{
		printf("X=-%u ", -a[1]);
	}
	else
	{
		printf("X=%u ", a[1]);
	}

	if (0x20 == (0x20 & a[0]))
	{
		printf("Y=-%u ", -a[2]);
	}
	else
	{
		printf("Y=%u ", a[2]);
	}
	printf("\n");
}

int get_packets(char mouse)
{

	if (global_bool1 == 0)
	{
		if (0x08 == (0x08 & mouse))
		{
			global_bool1 = 1;
			return 0;
		}
		else return -1;

	}
	else
	{
		if (global_bool2 == 0)
		{
			global_bool2 = 1;
			return 1;
		}
		else
		{

			//bool3 = 1;
			global_bool1 = 0;
			global_bool2 = 0;
			return 2;
		}
	}

	return -1;
}

/*typedef enum {INIT, DRAW, COMP} state_t;
typedef enum {LDOW, LUP, MOVE} ev_type_t;

void check_hor_line(event_t *evt)
{
	static state_t st = INIT; //initial state; keep state
	switch (st) {
	case INIT:
		if (evt->type == LDOWN)
			state = DRAW;
		break;
	case DRAW:
		if (evt->type == MOVE){
			//need to check if HOR_LINE event occurs
		} else if (evt->type == LUP)
			state = INIT;
		break;
	default:
		break;
		}
	}
}*/
