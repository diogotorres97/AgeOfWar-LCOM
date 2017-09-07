#include "rtc.h"
#include "test6.h"


int rtc_test_conf(void) {

		unsigned long regs[4];

		if(sys_outb(RTC_ADDR_REG, RTC_CTRL_REG_A))return 1;
		if(sys_inb(RTC_DATA_REG, &regs[0]))return 1;
		if(sys_outb(RTC_ADDR_REG, RTC_CTRL_REG_B))return 1;
		if(sys_inb(RTC_DATA_REG, &regs[1]))return 1;
		if(sys_outb(RTC_ADDR_REG, RTC_CTRL_REG_C))return 1;
		if(sys_inb(RTC_DATA_REG, &regs[2]))return 1;
		if(sys_outb(RTC_ADDR_REG,  RTC_CTRL_REG_D))return 1;
		if(sys_inb(RTC_DATA_REG, &regs[3]))return 1;

	printf("A: 0x%x \n B: 0x%x \n C: 0x%x \n D: 0x%x \n", regs[0], regs[1], regs[2], regs[3]);

}

int rtc_test_date(void) {
	unsigned long a_aux;
	unsigned long b_aux;
	unsigned long c_aux;
	unsigned long d_aux;
	unsigned long tmp;
	unsigned long minutes, hours, weekday, day, month, year;

	sys_outb(0x70, 0x0A);
	sys_inb(0x71, &a_aux);
	sys_outb(0x70, 0x0B);
	sys_inb(0x71, &b_aux);
	sys_outb(0x70, 0x0C);
	sys_inb(0x71, &c_aux);
	sys_outb(0x70, 0x0D);
	sys_inb(0x71, &d_aux);

	sys_outb(0x70, RTC_ADDRESS_MINUTES);
	sys_inb(0x71, &minutes);
	tmp = bcd_to_bin(minutes);
	minutes = tmp;

	sys_outb(0x70, RTC_ADDRESS_HOURS);
	sys_inb(0x71, &hours);
	tmp = bcd_to_bin(hours);
	hours = tmp;

	sys_outb(0x70, RTC_ADDRESS_DAY_WEEK);
	sys_inb(0x71, &weekday);
	tmp = bcd_to_bin(weekday);
	weekday = tmp;

	sys_outb(0x70,  RTC_ADDRESS_DAY_MONTH);
	sys_inb(0x71, &day);
	tmp = bcd_to_bin(day);
	day = tmp;

	sys_outb(0x70,  RTC_ADDRESS_MONTH);
	sys_inb(0x71, &month);
	tmp = bcd_to_bin(month);
	month = tmp;

	sys_outb(0x70,  RTC_ADDRESS_YEAR);
	sys_inb(0x71, &year);
	tmp = bcd_to_bin(year);
	year = tmp;


	printf("%d \n", minutes);
	printf("%d \n", hours);
	printf("%d \n", day);
	printf("%d \n", month);
	printf("%d \n", year);


}

int rtc_test_int(/* to be defined in class */) { 
	/* To be completed */
}

