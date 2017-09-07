#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "test6.h"

static int proc_args(int argc, char *argv[]);
static unsigned short parse_ushort(char *str, int base);
static short parse_short(char *str, int base);
static void print_usage(char *argv[]);


int main(int argc, char *argv[])
{

	sef_startup();
	sys_enable_iop(SELF);

	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else
		return proc_args(argc, argv);
}

static void print_usage(char *argv[]) {
	printf("Usage: one of the following:\n\n"
			"service run %s -args \"conf\" \n"
			"service run %s -args \"date\" \n"
			"service run %s -args \"int\" \n",
			argv[0], argv[0], argv[0], argv[0]);
}


static int proc_args(int argc, char *argv[]) {

	unsigned short cnt,idle_time, tolerance;
	short length;

	/* check the function to test: if the first characters match, accept it */
	if (strncmp(argv[1], "conf", strlen("conf")) == 0) {
		if( argc != 2 ) {
			printf("RTC: wrong no. of arguments for test_conf() \n");
			return 1;
		}
		printf("RTC::test_conf() \n");
		rtc_test_conf();

		return 0;
	}

	else if (strncmp(argv[1], "date", strlen("date")) == 0) {
		if( argc != 2) {
			printf("RTC: wrong no. of arguments for test_date() \n");
			return 1;
		}
		printf("RTC::test_date() \n");
		rtc_test_date();
		return 0;
	}

	else if (strncmp(argv[1], "int", strlen("int")) == 0) {
		if( argc != 2 ) {
			printf("RTC: wrong no. of arguments for test_int() \n");
			return 1;
		}
		printf("RTC::test_int() \n");
		rtc_test_int();
		return 0;
	}
	else {
		printf("RTC: %s - no valid function!\n", argv[1]);
		return 1;
	}
}




static unsigned short parse_ushort(char *str, int base)
{
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

static short parse_short(char *str, int base)
{
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
