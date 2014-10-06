#include"i8254.h"
#include"timer.h"

int main(int argc, char *argv[])
{
	/* Initialize service */
	sef_startup();

	if (argc == 1)
	{
	printf("\tTimer 0 \n");
	timer_test_config(TIMER_0);

	printf("\tTimer 1 \n");
	timer_test_config(TIMER_1);

	printf("\tTimer 2 \n");
	timer_test_config(TIMER_2);

	printf("To display a selected timer just enter a number between [0..2]\n\n");
	}
	else
		if ((strncmp(argv[1], "0", strlen("0")) == 0))
		{
			printf("\tTimer 0 \n");
			timer_test_config(TIMER_0);
		}
		else
			if ((strncmp(argv[1], "1", strlen("1")) == 0))
			{
				printf("\tTimer 1 \n");
				timer_test_config(TIMER_1);
			}
			else
				if ((strncmp(argv[1], "2", strlen("2")) == 0))
				{
					printf("\tTimer 2 \n");
					timer_test_config(TIMER_2);
				}
				else
					{
					printf("Enter a valid number! %u\n\n", *argv[1]);
					return 1;
					}


	return 0;
}
