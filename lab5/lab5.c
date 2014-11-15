#include <minix/drivers.h>

#include"test5.h"

int main()
{

	sef_startup();

	test_line(600,40, 200, 330,23);
	return 0;
}
