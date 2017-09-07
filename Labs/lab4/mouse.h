#ifndef __MOUSE_H
#define __MOUSE_H

#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "i8042.h"
#include "timer.h"
#include <stdbool.h>

int mouse_subscribe_int(void); //subscribes keyboard interrupts
int mouse_unsubscribe_int(); //unsubscribes keyboard interrupts
int mouse_get_packets(); //gets status code or data from kbd
int mouse_send_command(); //sends command
int mouse_send_args(unsigned long cmd);
int mouse_int_handler(unsigned long cmd);
int mouse_print_packet(unsigned char packet[]);
int mouse_print_config(unsigned char packet[]);
int mouse_state_machine(unsigned char packet[], short length,unsigned long *delta_y, unsigned long situation);






#endif /* __KEYBOARD_H */
