#include "rtc.h"

static int rtc_hook_id;

int rtc_subscribe_int() {
    rtc_hook_id = RTC_IRQ;  //RTC IRQ number is 8.
    if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &rtc_hook_id) != OK) {
        return -1;
    } else if (sys_irqenable((&rtc_hook_id)) != OK) {
        return -1;
    } else
        return RTC_IRQ;
}

int rtc_unsubscribe_int() {
    if (sys_irqdisable(&rtc_hook_id) != OK)
        return 1;
    else if (sys_irqrmpolicy(&rtc_hook_id) != OK)
        return 1;
    else
        return 0;
}


unsigned char bcd_to_bin(unsigned char bcd) {
    unsigned char aux;
    aux = (bcd >> 4) * 10;
    aux += (bcd & 0x0F);
    return aux;
}

unsigned char int_to_char(int n) {
    return 48 + n;
}


