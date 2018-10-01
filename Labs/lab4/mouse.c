#include "mouse.h"

static int mouse_hook_id;

int mouse_subscribe_int(void) {

    mouse_hook_id = MOUSE_HOOK_ID; // atualiza hook_id, passando a ser 5

    if (sys_irqsetpolicy(IRQ12, (IRQ_REENABLE | IRQ_EXCLUSIVE), &mouse_hook_id)
        != OK) {
        printf("ERROR: subscribe notification failed!\n");
        return -1;
    }

    if (sys_irqenable(&mouse_hook_id) != OK) {
        printf("ERROR: enables interrupts has failed!\n");
        return -1;
    }
    return MOUSE_HOOK_ID;
}

int mouse_unsubscribe_int() {

    if (sys_irqdisable(&mouse_hook_id) != OK) {
        printf("ERROR: disables interrupts failed!\n");
        return 1;
    }

    if (sys_irqrmpolicy(&mouse_hook_id) != OK) {
        printf("ERROR: unsubscribes a previous subscription failed!\n");
        return 1;
    }
    return 0;
}

int mouse_get_packets() {

    unsigned long data;
    int i = 0;

    while (i < TRIES) {
        if (sys_inb(OUT_BUF, &data) != OK) {
            tickdelay(micros_to_ticks(DELAY_US));
            i++;
        }
        return data;

    }
    return -1;
}

int mouse_send_command() {
    unsigned long stat;

    while (1) {
        sys_inb(STAT_REG, &stat);
        if ((stat & IBF) == 0) {
            sys_outb(STAT_REG, M_ARGS);
            tickdelay(micros_to_ticks(DELAY_US));
            return 0;
        }
        tickdelay(micros_to_ticks(DELAY_US));
    }
}

int mouse_send_args(unsigned long cmd) {
    unsigned long stat;

    while (1) {
        sys_inb(STAT_REG, &stat);
        if ((stat & IBF) == 0) {
            sys_outb(OUT_BUF, cmd);
            tickdelay(micros_to_ticks(DELAY_US));
            return 0;
        }
        tickdelay(micros_to_ticks(DELAY_US));
    }
}

int mouse_int_handler(unsigned long cmd) {
    unsigned char code;

    do {
        mouse_send_command();
        mouse_send_args(cmd);
        code = mouse_get_packets();
    } while (code != KBD_ACK);

}

int mouse_print_packet(unsigned char packet[]) {
    printf("B1= 0x%x  ", packet[0]);
    printf("B2= 0x%x  ", packet[1]);
    printf("B3= 0x%x  ", packet[2]);

    unsigned long MLB, MMB, MRB, MXOV, MYOV;
    unsigned char code;
    long temp1, temp2;

    code = packet[0];

    if ((code & YO) != 0)
        MYOV = 1;
    else
        MYOV = 0;

    if ((code & XO) != 0)
        MXOV = 1;
    else
        MXOV = 0;

    if ((code & YS) != 0)
        temp2 = -((~packet[2] + 1) & COMP);
    else
        temp2 = packet[2];

    if ((code & XS) != 0)
        temp1 = -((~packet[1] + 1) & COMP);
    else
        temp1 = packet[1];

    if ((code & MB) != 0)
        MMB = 1;
    else
        MMB = 0;

    if ((code & RB) != 0)
        MRB = 1;
    else
        MRB = 0;

    if ((code & LB) != 0)
        MLB = 1;
    else
        MLB = 0;

    printf("LB=%d ", MLB);
    printf("MB=%d ", MMB);
    printf("RB=%d ", MRB);
    printf("XOV=%d ", MXOV);
    printf("YOV=%d ", MYOV);
    printf("X=%d ", temp1);
    printf("Y=%d ", temp2);
    printf("\n");

    return 0;
}


int mouse_print_config(unsigned char packet[]) {
    printf("\n Mouse Configuration:\n");

    unsigned char byte1 = packet[0];
    unsigned char byte2 = packet[1];
    unsigned char byte3 = packet[2];

    if ((byte1 & BIT(6)) != 0) {
        printf("Remote (polled) Mode\n");
    } else printf("Stream Mode\n");

    if ((byte1 & BIT(5)) != 0) {
        printf("Data Reporting Enabled\n");

    } else printf("Data Reporting Disabled\n");

    if ((byte1 & BIT(4)) != 0) {
        printf("Scaling is 2:1\n");
    } else printf("Scaling is 1:1\n");

    if ((byte1 & BIT(2)) != 0) {
        printf("Left Button is currently pressed\n");
    } else printf("Left Button is Released\n");

    if ((byte1 & BIT(1)) != 0) {
        printf("Middle Button is currently pressed\n");
    } else printf("Middle Button is Released\n");

    if ((byte1 & BIT(0)) != 0) {
        printf("Right Button is currently pressed\n");

    } else printf("Right Button is Released\n");

    printf("\n");

    if (byte2 == (BIT(1) & BIT(0))) {
        printf("Resolution: 8 units per mm\n");
    } else if (byte2 == BIT(1)) {
        printf("Resolution: 4 units per mm\n");
    } else if (byte2 == BIT(0)) {
        printf("Resolution: 2 units per mm\n");
    } else if (byte2 == 0) {
        printf("Resolution: 1 units per mm\n");
    }

    printf("Sample Rate: %d Hz\n", byte3);

}


int mouse_state_machine(unsigned char packet[], short length, unsigned long *delta_y, unsigned long situation) {
    // code from test_gesture
    unsigned long right_button;

    if ((packet[0] & XO == 0) || (packet[0] & YO) == 0 || (packet[1] == 0) || (packet[2] == 0)) {


        right_button = (packet[0] & RB);

        switch (situation) {
            case 0:// before pressing right button or after releasing it
                if (right_button != 0)//pressed right button
                {

                    *delta_y = 0; //reinitializes the count
                    situation = 1; //now may move with right button pressed

                }
                break;
            case 1: //while moving
                //verifies if delta y is negative (CP2)
                if (right_button == 0) {
                    situation = 0;
                    break;
                }

                if ((packet[0] & YS) != 0) {
                    *delta_y += ((~packet[2] + 1) & COMP);

                } else *delta_y += packet[2];


                if (length > 0) {
                    if (((packet[0] & XS) == 0) && ((packet[0] & YS) == 0)) // both positive
                    {
                        if (*delta_y >= length) {
                            situation = 2;
                        }

                    } else {
                        situation = 0;
                    }
                } else {
                    if (((packet[0] & XS) != 0) && ((packet[0] & YS) != 0)) //both negative
                    {
                        if (*delta_y >= -length) {
                            situation = 2;
                        }


                    } else {
                        situation = 0;
                    }
                }
                break;
            case 2: //finished (overcame length in the required direction)
                break;

            default:
                break; /* no other notifications expected: do nothing */
        }

    }
    return situation;
}
