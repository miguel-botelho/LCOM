#include <minix/drivers.h>

#include"test3.h"

int main(int argc, char **argv) {

  /* Initialize service */

  sef_startup();

  /* Enable IO-sensitive operations for ourselves */

  //sys_iopenable(SELF);

  kbd_test_scan(0);

  return 0;
}
