#include <minix/drivers.h>

#include"test5.h"

int main()
{

	sef_startup();

	test_line(100, 100, 200, 300, 0x3F);
	return 0;
}
