#include <minix/drivers.h>

#include"test5.h"

int main()
{

	sef_startup();

	test_line(20, -20, 500, 700, 0x3F);
	return 0;
}
