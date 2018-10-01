#include "test4.h"

int test_packet(unsigned short cnt) {

    int irq_set = mouse_subscribe_int();
    if (irq_set == -1)
        return 1;

    irq_set = BIT(irq_set);
    int ipc_status, r;
    message msg;

    unsigned short i = 0; //count packets
    unsigned short counter = 0; //count 3-bytes to create a packet
    unsigned char packet[3];
    unsigned char code;

    mouse_int_handler(SSME); //enable stream mode
    mouse_int_handler(EDR); //enable data reporting

    while (i < cnt) {    /* Get a request message. */
        if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification*/
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.NOTIFY_ARG & irq_set) {/* subscribed interrupt */
                        code = mouse_get_packets();

                        if (counter == 0) {
                            if ((BIT(3) & code)) {
                                packet[counter] = code;
                                counter++;
                            }
                        } else {
                            if (counter != 3) {
                                packet[counter] = code;
                                if (counter == 2) {
                                    mouse_print_packet(packet);
                                    i++;
                                }
                                counter++;
                            }
                        }
                        if (counter == 3)
                            counter = 0;
                    }
                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }
        }
    }


    unsigned long trash;
    sys_inb(OUT_BUF, &trash);

    mouse_int_handler(DDR); //disable data reporting


    if (mouse_unsubscribe_int() == 1)
        return 1;

    mouse_int_handler(SET_DFT_ENABLE_KBD);

    return 0;
}


int test_async(unsigned short idle_time) {
    int irq_set2 = timer_subscribe_int();
    if (irq_set2 == -1)
        return 1;

    int irq_set1 = mouse_subscribe_int();
    if (irq_set1 == -1)
        return 1;

    irq_set1 = BIT(irq_set1);
    irq_set2 = BIT(irq_set2);

    int ipc_status, r;
    message msg;

    unsigned short i = 0; //count packets
    unsigned short counter = 0; //count 3-bytes to create a packet
    unsigned char packet[3];
    unsigned char code;

    mouse_int_handler(SSME); //enable stream mode
    mouse_int_handler(EDR); //enable data reporting

    int timer_counter = 0;
    int seconds = 0;

    while (seconds < idle_time) {/* Get a request message. */
        if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification*/
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.NOTIFY_ARG & irq_set1) { /* subscribed interrupt */
                        seconds = 0;
                        timer_counter = 0;
                        code = mouse_get_packets();


                        if (counter == 0) {
                            if ((BIT(3) & code)) {
                                packet[counter] = code;
                                counter++;
                            }
                        } else {
                            if (counter != 3) {
                                packet[counter] = code;
                                if (counter == 2) {
                                    mouse_print_packet(packet);
                                    i++;
                                }
                                counter++;
                            }
                        }
                        if (counter == 3)
                            counter = 0;
                    }

                    if (msg.NOTIFY_ARG & irq_set2) {
                        timer_counter++;
                        if (timer_counter % TIMER_DEFAULT_FREQ == 0) {
                            seconds++;
                            printf("Passou %d segundos! \n", seconds);
                        }
                    }
                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }

        }
    }

    unsigned long trash;
    sys_inb(OUT_BUF, &trash);

    mouse_int_handler(DDR); //disable data reporting

    if (mouse_unsubscribe_int() == 1)
        return 1;

    if (timer_unsubscribe_int() == 1)
        return 1;

    mouse_int_handler(SET_DFT_ENABLE_KBD);


    return 0;
}

int test_config(void) {

    if (mouse_subscribe_int() == -1)
        return 1;

    mouse_int_handler(EDR); //enable data reporting
    mouse_int_handler(STATUS_REQUEST); //send status request

    int counter = 0;
    unsigned char packet[3];

    while (counter < 3) {
        packet[counter] = mouse_get_packets();
        counter++;
    }

    unsigned long trash;
    sys_inb(OUT_BUF, &trash);

    mouse_print_config(packet);

    mouse_int_handler(DDR);

    if (mouse_unsubscribe_int() == 1)
        return 1;

    mouse_int_handler(SET_DFT_ENABLE_KBD);

    return 0;
}

int test_gesture(short length) {

    int irq_set = mouse_subscribe_int();
    if (irq_set == -1)
        return 1;

    irq_set = BIT(irq_set);
    int ipc_status, r;
    message msg;

    unsigned short i = 0; //count packets
    unsigned short counter = 0; //count 3-bytes to create a packet
    unsigned char packet[3];
    unsigned char code;

    unsigned long right_button = 0;
    unsigned long positive_slope = 0;
    unsigned long delta_x = 0; //contador horizontal
    unsigned long delta_y = 0; //contador vertical

    unsigned long situation = 0; //0-> before pressing right button or after releasing it; 1-> while moving; 2-> finished (overcame length)


    mouse_int_handler(SSME); //enable stream mode
    mouse_int_handler(EDR); //enable data reporting

    while (situation != 2) {    /* Get a request message. */
        if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification*/
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
                        code = mouse_get_packets();


                        if (counter == 0) {
                            if ((BIT(3) & code)) {
                                packet[counter] = code;
                                counter++;
                            }
                        } else {
                            if (counter != 3) {
                                packet[counter] = code;
                                if (counter == 2) {
                                    mouse_print_packet(packet);
                                    i++;
                                }
                                counter++;
                            }
                        }
                        if (counter == 3) {
                            counter = 0;
                            situation = mouse_state_machine(packet, length, &delta_y, situation);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    unsigned long trash;
    sys_inb(OUT_BUF, &trash);

    mouse_int_handler(DDR); //disable data reporting

    if (mouse_unsubscribe_int() == 1)
        return 1;

    mouse_int_handler(SET_DFT_ENABLE_KBD);

    return 0;
}
