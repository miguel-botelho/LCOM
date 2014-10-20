#include <minix/drivers.h>

#include"test3.h"
#include"keyboard.h"

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {

  /* Initialize service */

  sef_startup();

  /* Enable IO-sensitive operations for ourselves */

  //sys_iopenable(SELF);

  /*unsigned short a[] = {1,2,2,1};

  kbd_test_leds(4, a);

  //kbd_test_scan(0);

  return 0;*/

  printf("lab3: Keyboard \n");

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
 	 "\t service run %s -args \"test_scan <c->0 assembly->non-0>\" \n"
 	 "\t service run %s -args \"test_leds <array [0..2]>\" \n"
 	 "\t service run %s -args \"test_timed_scan <time>\" \n",
 	 argv[0], argv[0], argv[0]);
   printf("\n Example: \n"
		   "\t test_scan 0\n"
		   "\t test_leds 1 2 2 1\n"
		   "\t test_timed_scan 1\n");
 }

 static int proc_args(int argc, char *argv[]) {

   unsigned short assembly, time;

   /* check the function to test: if the first characters match, accept it */
   if (strncmp(argv[1], "test_scan", strlen("test_scan")) == 0) {
 	  if( argc != 3 ) {
 		  printf("Keyboard: wrong no of arguments for test of kbd_test_scan() \n");
 		  return 1;
 	  }
 	  if((assembly = parse_ulong(argv[2], 10)) == ULONG_MAX)
 		  return 1;
 	  printf("Keyboard:: kbd_test_scan(%u)\n\n", assembly); /* Actually, it was already invoked */
 	  return kbd_test_scan(assembly);
   } else if (strncmp(argv[1], "test_leds", strlen("test_leds")) == 0) {
 	  if( argc < 3) {
 		  printf("Keyboard: wrong no of arguments for test of kbd_test_leds() \n");
 		  return 1;
 	  }
 	  unsigned short *a = malloc (sizeof(unsigned short) * (argc - 2));
 	  unsigned int i = 0;
 	  unsigned int n = (argc - 2);
 	  for (i; i < n; i++)
 	  {
 		  a[i] = parse_ulong(argv[2+i], 10);
 	  }
 	  //if((size_of_array = parse_ushort(argv[2], 10)) == USHRT_MAX) //completar o array
 	  	//	  return 1;
 	  printf("Keyboard:: kbd_test_leds(array_of_size: %u)\n\n", (argc - 2));
 	  return kbd_test_leds(argc - 2, a);
   } else if (strncmp(argv[1], "test_timed_scan", strlen("test_timed_scan")) == 0) {
 	  if( argc != 3 ) {
 		  printf("Keyboard: wrong no of arguments for test of kbd_test_timed_scan() \n");
 		  return 1;
 	  }
 	  if((time = parse_ulong(argv[2], 10)) == ULONG_MAX)
 	  	  		  return 1;
 	  printf("Keyboard:: kbd_test_timed_scan(%u)\n\n", time);
 	  return kbd_test_timed_scan(time);
   } else {
 	  printf("Keyboard: non valid function \"%s\" to test\n", argv[1]);
 	  return 1;
   }
 }

 static unsigned long parse_ulong(char *str, int base) {
   char *endptr;
   unsigned short val;

   val = strtoul(str, &endptr, base);

   if ((errno == ERANGE && val == ULONG_MAX )
 	  || (errno != 0 && val == 0)) {
 	  perror("strtol");
 	  return USHRT_MAX;
   }

   if (endptr == str) {
 	  printf("video_txt: parse_ulong: no digits were found in %s \n", str);
 	  return ULONG_MAX;
   }

   /* Successful conversion */
   return val;
 }
