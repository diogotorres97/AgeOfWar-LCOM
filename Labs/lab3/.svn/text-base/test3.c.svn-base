#include "test3.h"

int kbd_test_scan(unsigned short ass) {

        //read and display the scancodes, both the makecodes and break codes

        int irq_set = kbd_subscribe_int();

        if (irq_set == -1)

                return 1;

        unsigned long trash;

        sys_inb(OUT_BUF, &trash);

        irq_set = BIT(irq_set);

        int ipc_status, r;

        message msg;

        unsigned long code = 0x00;

        while (code != ESC_BREAKCODE) {

                /* Get a request message. */

                if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {

                        printf("driver_receive failed with: %d", r);

                        continue;

                }

                if (is_ipc_notify(ipc_status)) { /* received notification*/

                        switch (_ENDPOINT_P(msg.m_source)) {

                        case HARDWARE: /* hardware interrupt notification */

                                if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

                                        if(ass==0)

                                        {

                                                code = kbc_get_status_codes(); //C handler

                                        }

                                        else

                                        {

                                                code=kbd_asm_IH(); //ASM handler

                                        }

                                        kbd_print_codes(code);

                                }

                                break;

                        default:

                                break; /* no other notifications expected: do nothing */

                        }

                }

        }

        if (kbd_unsubscribe_int() == 1)

                return 1;

        return 0;

}

int kbd_test_leds(unsigned short n, unsigned short *leds)

{

        int irq_set1 = kbd_subscribe_int();

        if(irq_set1==-1)

                return 1;

        int irq_set2 = timer_subscribe_int();

        if(irq_set2==-1)

                return 1;

        irq_set1=BIT(irq_set1);

        irq_set2 = BIT(irq_set2);

        int ipc_status, r;

        message msg;

        unsigned short i=0;

        unsigned long counter=0;

        unsigned long trash;

        sys_inb(OUT_BUF, &trash); //make code do enter

        while (counter < TIMER_DEFAULT_FREQ * n) {

                if ((r = driver_receive(ANY, &msg, &ipc_status) != 0)) {

                        printf("driver_receive failed with: %d", r);

                        continue;

                }

                if (is_ipc_notify(ipc_status)) {

                        switch (_ENDPOINT_P(msg.m_source)) {

                        case HARDWARE:

                                if (msg.NOTIFY_ARG & irq_set2) {

                                        counter++;

                                        if (counter % TIMER_DEFAULT_FREQ == 0)

                                        {

                                                kbd_switch_led(leds[i]);

                                                i++;

                                        }

                                }

                                break;

                        default:

                                break;

                        }

                } else {

                }

        }

        if(kbd_unsubscribe_int()==1)

                return 1;

        if(timer_unsubscribe_int()==1)

                return 1;

        kbc_send_command(SET_DFT_ENABLE_KBD);

        kbc_send_command(RESET_KD);

        return 0;

}

int kbd_test_timed_scan(unsigned short n) {

        int irq_set1 = kbd_subscribe_int();

        if (irq_set1 == -1)

                return 1;

        int irq_set2 = timer_subscribe_int();

        if(irq_set2==-1)

                return 1;

        unsigned long trash;

        sys_inb(OUT_BUF, &trash);

        irq_set1 = BIT(irq_set1);

        irq_set2 = BIT(irq_set2);

        int ipc_status, r;

        message msg;

        unsigned long code = 0x00;

        int counter=0;

        int seconds=0;

        while ((code != ESC_BREAKCODE) && seconds < n) {

                /* Get a request message. */

                if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {

                        printf("driver_receive failed with: %d", r);

                        continue;

                }

                if (is_ipc_notify(ipc_status)) { /* received notification*/

                        switch (_ENDPOINT_P(msg.m_source)) {

                        case HARDWARE: /* hardware interrupt notification */

                                if (msg.NOTIFY_ARG & irq_set1) { /* subscribed interrupt */

                                        code = kbc_get_status_codes();

                                        if(code==-1)

                                                return 1;

                                        kbd_print_codes(code);

                                        counter=0;

                                        seconds=0;

                                }

                                if (msg.NOTIFY_ARG & irq_set2) {

                                        counter++;

                                        if (counter % TIMER_DEFAULT_FREQ == 0)

                                        {

                                                seconds++;

                                                printf("Passou %d segundos! \n",seconds);

                                        }

                                }

                                break;

                        default:

                                break; /* no other notifications expected: do nothing */

                        }

                }

        }

        if (kbd_unsubscribe_int() == 1)

                return 1;

        if(timer_unsubscribe_int()==1)

                return 1;

        return 0;

}

