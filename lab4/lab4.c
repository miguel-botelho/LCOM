#include <minix/drivers.h>

 #include"test4.h"

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {

	/* Initialize service */

	sef_startup();

	//test_packet(20); //working (small bug)
	//test_async(2); //working
	//test_config(); //working
	//test_gesture(-10, 500); //working (negative numbers (small bug))


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
			"\t service run %s -args \"test_packet <number_packets>\" \n"
			"\t service run %s -args \"test_async <time>\" \n"
			"\t service run %s -args \"test_config\" \n"
			"\t service run %s -args \"test_gesture <length> <tolerance>\" \n",
			argv[0], argv[0], argv[0], argv[0]);
	printf("\n Example: \n"
			"\t test_packet 5\n"
			"\t test_async 2\n"
			"\t test_config\n"
			"\t test_gesture -10 50\n");
}

static int proc_args(int argc, char *argv[]) {

	unsigned short number, time, tolerance;
	short length;

	/* check the function to test: if the first characters match, accept it */
	if (strncmp(argv[1], "test_packet", strlen("test_packet")) == 0) {
		if( argc != 3 ) {
			printf("Keyboard: wrong no of arguments for test of test_packet() \n");
			return 1;
		}
		if((number = parse_ulong(argv[2], 10)) == ULONG_MAX)
			return 1;
		printf("Mouse:: test_packet(%u)\n\n", number); /* Actually, it was already invoked */
		return test_packet(number);
	} else if (strncmp(argv[1], "test_async", strlen("test_async")) == 0) {
		if( argc != 3) {
			printf("Mouse: wrong no of arguments for test of test_async() \n");
			return 1;
		}
		if((time = parse_ulong(argv[2], 10)) == ULONG_MAX)
					return 1;
		if(time <= 0)
			return 1;
		printf("Mouse:: test_async(%u)\n\n", time);
		return test_async(time);
	} else if (strncmp(argv[1], "test_config", strlen("test_config")) == 0) {
		if( argc != 2 ) {
			printf("Mouse: wrong no of arguments for test of test_config() \n");
			return 1;
		}
		printf("Mouse:: test_config()\n\n");
		return test_config();
	} else if (strncmp(argv[1], "test_gesture", strlen("test_gesture")) == 0) {
		if( argc != 4 ) {
			printf("Mouse: wrong no of arguments for test of test_gesture() \n");
			return 1;
		}
		if((length = parse_ulong(argv[2], 10)) == ULONG_MAX)
							return 1;
		if((tolerance = parse_ulong(argv[3], 10)) == ULONG_MAX)
							return 1;
		printf("Mouse:: test_gesture(%d, %u)\n\n", length, tolerance);
		return test_gesture(length, tolerance);
	} else {
		printf("Mouse: non valid function \"%s\" to test\n", argv[1]);
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
