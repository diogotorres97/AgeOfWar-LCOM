#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "i8042.h"
#include "timer.h"
#include <stdbool.h>

int kbd_subscribe_int(void); //subscribes keyboard interrupts
int kbd_unsubscribe_int(); //unsubscribes keyboard interrupts
int kbc_get_status_codes(); //gets status code or data from kbd
int kbc_send_command(unsigned long cmd); //sends command to kbd
int check_command(); // check if command returns error, resend or ack
int send_args(unsigned long args); //sends args to kbd
int kbd_print_codes(unsigned long code); //prints make or break codes
int kbd_switch_led(unsigned int led); //activates and deactivates leds


#endif /* __KEYBOARD_H */
