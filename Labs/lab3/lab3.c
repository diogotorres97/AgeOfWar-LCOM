#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "test3.h"
#include "timer.h"
#include "i8042.h"

static int proc_args(int argc, char **argv);

static unsigned short parse_ushort(char *str, int base);

static void print_usage(char **argv);

int main(int argc, char **argv) {
    sef_startup();

    /* Enable IO-sensitive operations for ourselves */
    sys_enable_iop(SELF);

    /* DO NOT FORGET TO initialize service */

    if (argc == 1) {                    /* Prints usage of the program if no arguments are passed */
        print_usage(argv);
        return 0;
    } else return proc_args(argc, argv);
}

static void print_usage(char **argv) {
    printf("Usage: one of the following:\n"
           "\t service run %s -args \"scan <decimal no.- ass (Which IH to use (0->C, other->assembly))>\"\n"
           "\t service run %s -args \"leds <decimal no. - *leds (LEDs to toggle (Ranges from 0 t0 2))>\"\n"
           "\t service run %s -args \"timed_scan <decimal no. - n (Number of seconds without scancodes before exiting)>\"\n",
           argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv) {
    unsigned short ass, n;
    unsigned short *leds;
    if (strncmp(argv[1], "scan", strlen("scan")) == 0) {
        if (argc != 3) {
            printf("keyboard: wrong no. of arguments for kbd_test_scan()\n");
            return 1;
        }
        ass = parse_ushort(argv[2], 10);                        /* Parses string to unsigned long */
        if (ass == USHRT_MAX)
            return 1;
        printf("keyboard::kbd_test_scan(%d)\n", ass);
        return kbd_test_scan(ass);
    } else if (strncmp(argv[1], "leds", strlen("leds")) == 0) {
        if (argc < 3) {
            printf("keyboard: wrong no. of arguments for kbd_test_leds()\n");
            return 1;
        }
        n = argc - 2;                    /* Parses string to unsigned long */

        unsigned short leds[n];

        int i = 0;
        while (i < n) {
            if ((parse_ushort(argv[2 + i], 10) > 2) || (parse_ushort(argv[2 + i], 10) < 0)) {
                printf("\nERROR: Leds values have to be between 0 and 2\n");
                return 1;
            }
            leds[i] = parse_ushort(argv[2 + i], 10);
            i++;
        }
        printf("keyboard::kbd_test_leds( ", leds);
        i = 0;
        while (i < n) {
            printf("%d  ", leds[i]);
            i++;
        }
        printf(")\n");
        return kbd_test_leds(n, leds);
    } else if (strncmp(argv[1], "timed_scan", strlen("timed_scan")) == 0) {
        if (argc != 3) {
            printf("keyboard: wrong no. of arguments for kbd_test_timed_scan()\n");
            return 1;
        }
        n = parse_ushort(argv[2], 10);                        /* Parses string to unsigned long */
        if (n == USHRT_MAX)
            return 1;
        printf("keyboard::kbd_test_timed_scan(%lu)\n", n);
        return kbd_test_timed_scan(n);
    } else {
        printf("keyboard: %s - no valid function!\n", argv[1]);
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

