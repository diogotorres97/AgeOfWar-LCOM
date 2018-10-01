#include "rtc.h"
#include <minix/driver.h>

/******************************************** RTC functions *****************************************/

static int rtc_hook_id;

Date *InitDate() {
    Date *d = (Date *) malloc(sizeof(Date));
    d->minutes = 0;
    d->hours = 0;
    d->day = 0;
    d->month = 0;
    d->year = 0;
    return d;
}

int updateDate(Date *d) {
    unsigned long a_aux;
    unsigned long tmp;
    unsigned long minutes, hours, day, month, year;

    rtc_disable_interrupts();

    do {

        sys_outb(0x70, 0x0A);
        sys_inb(0x71, &a_aux);

        sys_outb(0x70, RTC_ADDRESS_MINUTES);
        sys_inb(0x71, &minutes);
        tmp = bcd_to_bin(minutes);
        d->minutes = tmp;

        sys_outb(0x70, RTC_ADDRESS_HOURS);
        sys_inb(0x71, &hours);
        tmp = bcd_to_bin(hours);
        d->hours = tmp;

        sys_outb(0x70, RTC_ADDRESS_DAY_MONTH);
        sys_inb(0x71, &day);
        tmp = bcd_to_bin(day);
        d->day = tmp;

        sys_outb(0x70, RTC_ADDRESS_MONTH);
        sys_inb(0x71, &month);
        tmp = bcd_to_bin(month);
        d->month = tmp;

        sys_outb(0x70, RTC_ADDRESS_YEAR);
        sys_inb(0x71, &year);
        tmp = bcd_to_bin(year);
        d->year = tmp;

    } while (a_aux & 0x80);

    rtc_enable_interrupts();

}

void drawDate(Date *d, int x, int y, char *doubleBuffer) {
    DateFont *font = InitDateFont();
    int min1, min0;
    int hou1, hou0;
    int day1, day0;
    int mon1, mon0;
    int yea1, yea0;

    min1 = d->minutes / 10;
    min0 = d->minutes - min1 * 10;
    hou1 = d->hours / 10;
    hou0 = d->hours - hou1 * 10;
    day1 = d->day / 10;
    day0 = d->day - day1 * 10;
    mon1 = d->month / 10;
    mon0 = d->month - mon1 * 10;
    yea1 = d->year / 10;
    yea0 = d->year - yea1 * 10;

    drawDateChar(font, hou1, x + 50, y, doubleBuffer);
    drawDateChar(font, hou0, x + 60, y, doubleBuffer);
    drawDateChar(font, min1, x + 80, y, doubleBuffer);
    drawDateChar(font, min0, x + 90, y, doubleBuffer);
    drawDateChar(font, day1, x + 130, y, doubleBuffer);
    drawDateChar(font, day0, x + 140, y, doubleBuffer);
    drawDateChar(font, 11, x + 150, y, doubleBuffer);
    drawDateChar(font, mon1, x + 160, y, doubleBuffer);
    drawDateChar(font, mon0, x + 170, y, doubleBuffer);
    drawDateChar(font, 11, x + 180, y, doubleBuffer);
    drawDateChar(font, yea1, x + 190, y, doubleBuffer);
    drawDateChar(font, yea0, x + 200, y, doubleBuffer);
    deleteDateFont(font);
}

void deleteDate(Date *d) {
    free(d);
}

int rtc_subscribe_int() {
    rtc_hook_id = RTC_HOOK_ID;  //RTC IRQ number is 8.
    if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &rtc_hook_id) != OK)
        return -1;

    return RTC_IRQ;
}

int rtc_unsubscribe_int() {

    if (sys_irqrmpolicy(&rtc_hook_id) != OK)
        return 1;
    else
        return 0;
}

void rtc_disable_interrupts() {
    asm("cli");
}

void rtc_enable_interrupts() {
    asm("sti");
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

