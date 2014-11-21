#include <minix/drivers.h>

#include"test5.h"
#include"pixmap.h"

#define PIC_MAX 4

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {

	/* Initialize service */

	sef_startup();

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
			"\t service run %s -args \"test_init <mode> <delay>\" \n"
			"\t service run %s -args \"test_square <x_coord> <y_coord> <size> <color>\" \n"
			"\t service run %s -args \"test_line <xi_point> <yi_point> <xf_point> <yf_point> <color>\" \n"
			"\t service run %s -args \"test_xpm <x_coord> <y_coord> <0..4>\" \n"
			"\t service run %s -args \"test_move <x_coord> <x_coord> <0..4> <hor> <delta> <time>\" \n"
			"\t service run %s -args \"test_controller\" \n",
			argv[0], argv[0], argv[0], argv[0], argv[0], argv[0]);
	printf("\n Example: \n"
			"\t test_init 105 2\n"
			"\t test_square 100 100 50 23\n"
			"\t test_line 100 100 200 200 23\n"
			"\t test_xpm 200 200 0\n"
			"\t test_move 200 200 0 0 300 2\n"
			"\t test_controller \n");
}

static int proc_args(int argc, char *argv[]) {

	unsigned short mode, delay, x_coord, y_coord, size, xi_coord, yi_coord, xf_coord, yf_coord, hor, time;
	short delta;
	unsigned long color;
	unsigned int i;
	char **a[PIC_MAX + 1];

	//preenche o array com os xpm
	a[0] = pic1;
	a[1] = pic2;
	a[2] = cross;
	a[3] = pic3;
	a[4] = penguin;

	/* check the function to test: if the first characters match, accept it */
	if (strncmp(argv[1], "test_init", strlen("test_init")) == 0) {
		if( argc != 4 ) {
			printf("Video Card: wrong no of arguments for test of test_init() \n");
			return 1;
		}
		if((mode = parse_ulong(argv[2], 16)) == ULONG_MAX)
			return 1;
		if((delay = parse_ulong(argv[3], 10)) == ULONG_MAX)
			return 1;
		if (delay <= 0)
			return 1;
		printf("Video Card:: test_init(%x, %u)\n\n", mode, delay);
		test_init(mode, delay);
		return 0;
	} else if (strncmp(argv[1], "test_square", strlen("test_square")) == 0) {
		if( argc != 6) {
			printf("Video Card: wrong no of arguments for test of test_square() \n");
			return 1;
		}
		if((x_coord = parse_ulong(argv[2], 10)) == ULONG_MAX)
					return 1;
		if((y_coord = parse_ulong(argv[3], 10)) == ULONG_MAX)
					return 1;
		if((size = parse_ulong(argv[4], 10)) == ULONG_MAX)
					return 1;
		if((color = parse_ulong(argv[5], 16)) == ULONG_MAX)
					return 1;
		printf("Video Card:: test_square(%u, %u, %u, %x)\n\n", x_coord, y_coord, size, color);
		return test_square(x_coord, y_coord, size, color);
	} else if (strncmp(argv[1], "test_line", strlen("test_line")) == 0) {
		if( argc != 7 ) {
			printf("Video Card: wrong no of arguments for test of test_line() \n");
			return 1;
		}
		if((xi_coord = parse_ulong(argv[2], 10)) == ULONG_MAX)
					return 1;
		if(((yi_coord) = parse_ulong(argv[3], 10)) == ULONG_MAX)
					return 1;
		if((xf_coord = parse_ulong(argv[4], 10)) == ULONG_MAX)
					return 1;
		if((yf_coord = parse_ulong(argv[5], 10)) == ULONG_MAX)
					return 1;
		if((color = parse_ulong(argv[6], 16)) == ULONG_MAX)
					return 1;
		printf("Video Card:: test_line(%u, %u, %u, %u, %x)\n\n", xi_coord, yi_coord, xf_coord, yf_coord, color);
		return test_line(xi_coord, yi_coord, xf_coord, yf_coord, color);
	} else if (strncmp(argv[1], "test_xpm", strlen("test_xpm")) == 0) {
		if( argc != 5 ) {
			printf("Video Card: wrong no of arguments for test of test_xpm() \n");
			return 1;
		}
		if((x_coord = parse_ulong(argv[2], 10)) == ULONG_MAX)
							return 1;
		if((y_coord = parse_ulong(argv[3], 10)) == ULONG_MAX)
							return 1;
		if((i = parse_ulong(argv[4], 10)) == ULONG_MAX)
							return 1;

		if (i < 0 || i > PIC_MAX)
			return 1;

		printf("Video Card:: test_xpm(%u, %u, %u)\n\n", x_coord, y_coord, i);
		return test_xpm(x_coord, y_coord, a[i]);
	}  else if (strncmp(argv[1], "test_move", strlen("test_move")) == 0) {
		if( argc != 8 ) {
			printf("Video Card: wrong no of arguments for test of test_move() \n");
			return 1;
		}
		if((x_coord = parse_ulong(argv[2], 10)) == ULONG_MAX)
							return 1;
		if((y_coord = parse_ulong(argv[3], 10)) == ULONG_MAX)
							return 1;
		if((i = parse_ulong(argv[4], 10)) == ULONG_MAX)
							return 1;
		if((hor = parse_ulong(argv[5], 10)) == ULONG_MAX)
							return 1;
		if((delta = parse_ulong(argv[6], 10)) == ULONG_MAX)
							return 1;
		if((time = parse_ulong(argv[7], 10)) == ULONG_MAX)
							return 1;

		if (i < 0 || i > PIC_MAX)
			return 1;

		printf("Video Card:: test_move(%u, %u, %u, %u, %u, %u)\n\n", x_coord, y_coord, i, hor, delta, time);
		return test_move(x_coord, y_coord, a[i], hor, delta, time);
	}  else if (strncmp(argv[1], "test_controller", strlen("test_controller")) == 0) {
		if( argc != 2 ) {
			printf("Video Card: wrong no of arguments for test of test_controller() \n");
			return 1;
		}
		printf("Video Card:: test_controller()\n\n");
		return test_controller();
	} else {
		printf("Video Card: non valid function \"%s\" to test\n", argv[1]);
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
