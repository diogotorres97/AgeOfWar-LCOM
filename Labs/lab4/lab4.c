#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "test4.h"

static int proc_args(int argc, char *argv[]);

static unsigned short parse_ushort(char *str, int base);

static short parse_short(char *str, int base);

static void print_usage(char *argv[]);


int main(int argc, char *argv[]) {
    sef_startup();

    if (argc == 1) {                    /* Prints usage of the program if no arguments are passed */
        print_usage(argv);
        return 0;
    } else
        return proc_args(argc, argv);
}

static void print_usage(char *argv[]) {
    printf("Usage: one of the following:\n\n"
           "service run %s -args \"packet <positive decimal no.- cnt>\" \n"
           "service run %s -args \"async <positive decimal no.- idle_time>\" \n"
           "service run %s -args \"config\" \n"
           "service run %s -args \"gesture <decimal no.- length>\" \n\n",
           argv[0], argv[0], argv[0], argv[0]);
}


static int proc_args(int argc, char *argv[]) {

    unsigned short cnt, idle_time, tolerance;
    short length;

    /* check the function to test: if the first characters match, accept it */
    if (strncmp(argv[1], "packet", strlen("packet")) == 0) {
        if (argc != 3) {
            printf("Mouse: wrong no. of arguments for test_packet() \n");
            return 1;
        }
        cnt = parse_ushort(argv[2], 10);

        if (cnt == USHRT_MAX)
            return 1;
        printf("Mouse::test_packet(%d) \n", cnt);
        test_packet(cnt);
        return 0;
    } else if (strncmp(argv[1], "async", strlen("async")) == 0) {
        if (argc != 3) {
            printf("Mouse: wrong no. of arguments for test_async() \n");
            return 1;
        }
        idle_time = parse_ushort(argv[2], 10);

        if (idle_time == USHRT_MAX)
            return 1;
        printf("Mouse::test_async(%d) \n", idle_time);
        test_async(idle_time);
        return 0;
    } else if (strncmp(argv[1], "config", strlen("config")) == 0) {
        if (argc != 2) {
            printf("Mouse: wrong no. of arguments for test_config() \n");
            return 1;
        }
        printf("Mouse::test_config(void) \n");
        test_config();
        return 0;
    } else if (strncmp(argv[1], "gesture", strlen("gesture")) == 0) {
        if (argc != 3) {
            printf("Wrong no of arguments for test_gesture() \n");
            return 1;
        }
        length = parse_short(argv[2], 10);

        if (length == SHRT_MAX)
            return 1;

        printf("Mouse::test_gesture(%d) \n", length);
        test_gesture(length);
        return 0;
    } else {
        printf("Mouse: %s - no valid function!\n", argv[1]);
        return 1;
    }
}


static unsigned short parse_ushort(char *str, int base) {
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

static short parse_short(char *str, int base) {
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
