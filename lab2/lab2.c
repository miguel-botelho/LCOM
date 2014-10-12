#include <minix/drivers.h>

#include"i8254.h"
#include"timer.h"

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {

  /* Initialize service */

  sef_startup();

  printf("lab2: TIMERS \n");

  if ( argc == 1 ) {
      print_usage(argv);
      return 0;
  } else {
      proc_args(argc, argv);
  }
  return 0;

}

static void print_usage(char *argv[]) {
  printf("Usage: one of the following:\n"
	 "\t service run %s -args \"test_square <freq>\" \n"
	 "\t service run %s -args \"test_int <time>\" \n"
	 "\t service run %s -args \"test_config <timer>\" \n",
	 argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

  unsigned long timer, freq, time;

  /* check the function to test: if the first characters match, accept it */
  if (strncmp(argv[1], "test_square", strlen("test_square")) == 0) {
	  if( argc != 3 ) {
		  printf("timer: wrong no of arguments for test of timer_test_square() \n");
		  return 1;
	  }
	  if((freq = parse_ulong(argv[2], 10)) == ULONG_MAX)
		  return 1;
	  printf("timer:: timer_test_square(%u)\n\n", freq); /* Actually, it was already invoked */
	  return timer_test_square(freq);
  } else if (strncmp(argv[1], "test_int", strlen("test_int")) == 0) {
	  if( argc != 3 ) {
		  printf("timer: wrong no of arguments for test of timer_test_int() \n");
		  return 1;
	  }
	  if((time = parse_ulong(argv[2], 10)) == ULONG_MAX)
	  		  return 1;
	  printf("timer:: timer_test_int(%u)\n\n", time);
	  return timer_test_int(time);
  } else if (strncmp(argv[1], "test_config", strlen("test_config")) == 0) {
	  if( argc != 3 ) {
		  printf("timer: wrong no of arguments for test of timer_test_config() \n");
		  return 1;
	  }
	  if((timer = parse_ulong(argv[2], 10)) == ULONG_MAX)
	  	  		  return 1;
	  printf("timer:: timer_test_config(%u)\n\n", timer);
	  return timer_test_config(timer);
  } else {
	  printf("timer: non valid function \"%s\" to test\n", argv[1]);
	  return 1;
  }
}

static unsigned long parse_ulong(char *str, int base) {
  char *endptr;
  unsigned long val;

  val = strtoul(str, &endptr, base);

  if ((errno == ERANGE && val == ULONG_MAX )
	  || (errno != 0 && val == 0)) {
	  perror("strtol");
	  return ULONG_MAX;
  }

  if (endptr == str) {
	  printf("video_txt: parse_ulong: no digits were found in %s \n", str);//temos de mudar isto
	  return ULONG_MAX;
  }

  /* Successful conversion */
  return val;
}
