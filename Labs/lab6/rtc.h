#ifndef __RTC_H
#define __RTC_H

#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <minix/syslib.h>


/** @defgroup rtc rtc
 * @{
 *
 *
 * Functions for using the real time clock
 */
#define RTC_IRQ 8 //irq_line

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

#define RTC_ADDRESS_SECONDS 		0
#define RTC_ADDRESS_SECONDS_ALARM 	1
#define RTC_ADDRESS_MINUTES			2
#define RTC_ADDRESS_MINUTES_ALARM	3
#define RTC_ADDRESS_HOURS 			4
#define RTC_ADDRESS_HOURS_ALARM 	5
#define RTC_ADDRESS_DAY_WEEK 		6
#define RTC_ADDRESS_DAY_MONTH		7
#define RTC_ADDRESS_MONTH			8
#define RTC_ADDRESS_YEAR			9

#define RTC_CTRL_REG_A 			10
#define RTC_CTRL_REG_B  		11
#define RTC_CTRL_REG_C  		12
#define RTC_CTRL_REG_D 			13

/**
 * @brief subscribe rtc
 *
 * @param
 * @return RTC_IRQ if sucess, -1 otherwise
 */
int rtc_subscribe_int();

/**
 * @brief unsubscribe rtc
 *
 * @param
 * @return 0 if sucess, 1 otherwise
 */
int rtc_unsubscribe_int();

/**
 * @brief transform char in bcd to bin
 *
 * @param bcd char
 * @return char passed as argument in binary
 */
unsigned char bcd_to_bin(unsigned char bcd);

/**
 * @brief get the ascii code
 *
 * @param int
 * @return ascii code of respective int
 */
unsigned char int_to_char(int n);

/**
 * @brief init the date struct
 *
 * @param
 * @return date struct
 */

#endif
