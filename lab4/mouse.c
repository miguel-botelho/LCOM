#include"mouse.h"

int mhook_id = BIT(0);
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
	//para nao perder o valor original de mhook_id (vai ser preciso para depois reconhecer a notificacao)
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

			if(MOUSE_DATA == (MOUSE_DATA & cmd_receive2)) //verificar se o que estou a ler é do mouse
			{
				if (cmd_receive2 == NACK) // se e NACK, então repete só o cmd enviado, não necessita de enviar 0xD4
				{
					nr_tentativas++;
					continue;
				}
				else break;
			}
			else continue;
		}

		if (cmd_receive2 == ERROR) //erro, volta a repetir todo o processo
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

void mouse_printf(char a[]){

	printf("B1=0x%02x ",(a[0] & 0x0F)); //obtem um byte
	printf("B2=0x%02x ", (0xFF & a[1])); //obtem um byte
	printf("B3=0x%02x ", (0xFF & a[2])); //obtem um byte
	printf("LB=%u ", (a[0] & BIT(0))); //obtem o o primeiro bit
	printf("MB=%u ", ((a[0] & BIT(2)) >> 2)); //obtem o terceiro bit
	printf("RB=%u ", ((a[0] & BIT(1)) >> 1)); //obtem o segundo bit
	printf("XOV=%u ", ((a[0] & BIT(6)) >> 2)); //obtem o setimo bit
	printf("YOV=%u ", ((a[0] & BIT(7)) >> 3)); //obtem o oitavo bit

	if (BIT(4) == (BIT(4) & a[0])) // se for negativo
	{
		printf("X=-%u ", neg8bits(a[1]));
	}
	else //nr positivo
	{
		printf("X=%u ", a[1]);
	}

	if (BIT(5) == (BIT(5) & a[0])) //negativo
	{
		printf("Y=-%u ", neg8bits(a[2]));
	}
	else //positivo
	{
		printf("Y=%u ", a[2]);
	}
	printf("\n");
}

char neg8bits(char neg) //transforma um char de 8 bits em complemento para 2, para o seu equivalente positivo; i.e -24 transforma-se em 24
{
	int i = 0;
	char ret = 0;
	char negative = 0; //flag que verifica se foi encontrado o primeiro 1

	for (i; i < 8; i++)
	{
		if (negative == 0) //se não foi encontrado o primeiro 1, então copia o bit
		{
			if (BIT(i) == (BIT(i) & neg))
			{
				negative = 1;
				ret = ret + (BIT(i) & neg);
			}
			else ret = ret + (BIT(i) & neg);
		}
		else ret = ret + !(BIT(i) & neg); //troca o bit
	}

	return ret;
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
