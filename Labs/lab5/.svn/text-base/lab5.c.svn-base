#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#include "test5.h"
#include "pixmap.h"


static int proc_args(int argc, char *argv[]);
static unsigned short parse_ushort(char *str, int base);
static unsigned long parse_ulong(char *str, int base);
static short parse_short(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char *argv[]) {

	sef_startup();

	/* Prints usage of the program if no arguments are passed */
	if (argc == 1) {
		print_usage(argv);
		return 0;
	}
	else
		return proc_args(argc, argv);
}

static void print_usage(char *argv[]) {

	printf("Usage: one of the following:\n\n"
			"service run %s -args \"init <0x mode> <delay (seconds)>\" \n"
			"service run %s -args \"square <x position> <y position> <size> <hexadecimal - color>\" \n"
			"service run %s -args \"line <xi position> <yi position> <xf position> <yf position> <hexadecimal - color>\" \n"
			"service run %s -args \"xpm <xi position> <yi position> <string - xpm's name>\" \n"
			"service run %s -args \"move <xi position> <yi position> <string - xpm's name> <decimal no. hor> <decimal no.- delta> <time (seconds)>\" \n"
			"service run %s -args \"controller\" \n\n",
			argv[0], argv[0], argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	unsigned long mode, delay, x,y, size, xi, yi, xf, yf, hor, time, n;
	unsigned long color;
	short delta;
	char **xpm;

	/* check the function to test: if the first characters match, accept it */
	if (strncmp(argv[1], "init", strlen("init")) == 0) {
		if( argc != 4 ) {
			printf("Graphic: wrong no. of arguments for test_init() \n");
			return 1;
		}

		mode=parse_ulong(argv[2], 16);
		delay=parse_ulong(argv[3], 10);

		if((mode == ULONG_MAX )||(delay==ULONG_MAX))
			return 1;

		printf("Graphic::test_init(0x%x, %d) \n", mode, delay);
		test_init(mode, delay);
		return 0;
	}

	else if (strncmp(argv[1], "square", strlen("square")) == 0) {
		if( argc != 6) {
			printf("Graphic: wrong no. of arguments for test_square() \n");
			return 1;
		}
		x=parse_ulong(argv[2], 10);
		y=parse_ulong(argv[3], 10);
		size=parse_ulong(argv[4], 10);
		color=parse_ulong(argv[5], 16);

		if((x == ULONG_MAX )||(y == ULONG_MAX )||(size == ULONG_MAX )||(color == ULONG_MAX ))
			return 1;

		printf("Graphic::test_square(%d, %d, %d, 0x%02X) \n", x, y, size, color);
		test_square(x, y, size, color);
		return 0;
	}

	else if (strncmp(argv[1], "line", strlen("line")) == 0) {
		if( argc != 7 ) {
			printf("Graphic: wrong no. of arguments for test_line() \n");
			return 1;
		}
		xi=parse_ulong(argv[2], 10);
		yi=parse_ulong(argv[3], 10);
		xf=parse_ulong(argv[4], 10);
		yf=parse_ulong(argv[5], 10);
		color=parse_ulong(argv[6], 16);

		if((xi == ULONG_MAX )||(yi == ULONG_MAX )||(xf == ULONG_MAX )||(yf ==  ULONG_MAX)||(color == ULONG_MAX ))
			return 1;

		printf("Graphic::test_line(%d, %d, %d, %d, 0x%X) \n", xi, yi, xf, yf, color);
		test_line(xi, yi, xf, yf, color);
		return 0;
	}

	else if (strncmp(argv[1], "xpm", strlen("xpm")) == 0) {
		if( argc != 5) {
			printf("Graphic: wrong no. of arguments for test_xpm() \n");
			return 1;
		}

		xi=parse_ulong(argv[2], 10);
		yi=parse_ulong(argv[3], 10);

		if((xi == ULONG_MAX )||(yi == ULONG_MAX ))
			return 1;

		if(strncmp(argv[4], "pic1", strlen("pic1")) == 0) {
			xpm = pic1;
		}
		else if (strncmp(argv[4], "pic2", strlen("pic2")) == 0)	{
			xpm = pic2;
		}
		else if (strncmp(argv[4], "cross", strlen("cross")) == 0) {
			xpm = cross;
		}
		else if (strncmp(argv[4], "pic3", strlen("pic3")) == 0)	{
			xpm = pic3;
		}
		else if (strncmp(argv[4], "penguin", strlen("penguin")) == 0){
			xpm = penguin;
		}
		else
		{
			printf("\nInvalid xpm selected. Valid images are: \n\n");
			return 1;
		}

		printf("Graphic::test_xpm(%d, %d,%x)\n ", xi, yi,xpm);
		test_xpm(xi, yi,xpm);
		return 0;
	}

	else if (strncmp(argv[1], "move", strlen("move")) == 0) {
		if( argc != 8) {
			printf("Graphic: wrong no. of arguments for test_move() \n");
			return 1;
		}
		xi=parse_ulong(argv[2], 10);
		yi=parse_ulong(argv[3], 10);
		hor=parse_ulong(argv[5], 10);
		delta=parse_ulong(argv[6], 10);
		time=parse_ulong(argv[7], 10);
		if((xi == ULONG_MAX )||(yi == ULONG_MAX )||(hor == ULONG_MAX )||(delta == ULONG_MAX )||(time == ULONG_MAX ))
			return 1;

		if(strncmp(argv[4], "pic1", strlen("pic1")) == 0)
		{
			xpm = pic1;
		}
		else if (strncmp(argv[4], "pic2", strlen("pic2")) == 0)
		{
			xpm = pic2;
		}
		else if (strncmp(argv[4], "cross", strlen("cross")) == 0)
		{
			xpm = cross;
		}
		else if (strncmp(argv[4], "pic3", strlen("pic3")) == 0)
		{
			xpm = pic3;
		}
		else if (strncmp(argv[4], "penguin", strlen("penguin")) == 0)
		{
			xpm = penguin;
		}
		else
		{
			printf("\nInvalid xpm selected. Valid images are: \n\n");
			return 1;
		}

		printf("Graphic::test_move(%d, %d, %x, %d, %d, %d ", xi, yi,xpm, hor, delta, time);
		test_move(xi, yi,xpm, hor, delta, time);
		return 0;
	}

	else if (strncmp(argv[1], "controller", strlen("controller")) == 0) {
		if( argc != 2 ) {
			printf("Graphic: wrong no. of arguments for test_controller() \n");
			return 1;
		}

		printf("Graphic::test_controller() \n");
		test_controller();
		return 0;
	}

	else {
		printf("Graphic: %s - no valid function!\n", argv[1]);
		return 1;
	}
}

static unsigned short parse_ushort(char *str, int base){

	char *endptr;
	unsigned short val;

	/* Convert string to unsigned short */
	val = (unsigned short) strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == USHRT_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return USHRT_MAX;
	}

	if (endptr == str) {
		printf("keyboard: parse_ushort: no digits were found in %s\n", str);
		return USHRT_MAX;
	}

	/* Successful conversion */
	return val;
}

static short parse_short(char *str, int base){

	char *endptr;
	short val;

	/* Convert string to short */
	val = (short) strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == USHRT_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return SHRT_MAX;
	}

	if (endptr == str) {
		printf("keyboard: parse_short: no digits were found in %s\n", str);
		return SHRT_MAX;
	}

	/* Successful conversion */
	return val;
}

static unsigned long parse_ulong(char *str, int base){

	char *endptr;
	unsigned long val;

	/* Convert string to unsigned long */
	val = strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == ULONG_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("timer: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}
