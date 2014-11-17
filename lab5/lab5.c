#include <minix/drivers.h>

#include"test5.h"

int main()
{

	sef_startup();

	test_square(0, 0, 767, 0x3F);
	return 0;
}
