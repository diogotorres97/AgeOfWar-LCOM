#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

/** @defgroup i8042 i8042


 * @{
 *
 * Constants for programming the i8042 Keyboard. Needs to be completed.
 */
#define KEYBOARD_HOOK_ID 4

#define IRQ1 1

#define TRIES 5

#define BIT(n) (0x01<<(n))

#define STAT_REG    0x64

#define DELAY_US 20000

#define KBC_CMD_REG 0x64

#define OUT_BUF 0x60

#define ESC_BREAKCODE 0x81

#define FIRST_OF_TWO_BYTE_SCANCODES 0xE0

#define KBD_ACK 0xFA

#define KBD_RESEND 0xFE

#define KBD_ERROR 0xFC

#define CAPS_LOCK BIT(2)

#define SCROLL_LOCK BIT(0)

#define NUMERIC_LOCK BIT(1)

/* PORTS */

#define PORT_60 0x60

#define PORT_64 0x64

/* Keyboard Commands */

#define RESET_KD 0xFF

#define SET_DFT_ENABLE_KBD 0xF6

#define DISABLE_KBD 0xF5

#define CLEAR_BFR_ENABLE_KBD 0xF4

#define CANGE_KBD_REP 0xF3  //bits 0-4 rate  5-6 delay

#define SWITCH_KBD_LEDS 0xED //bits 0-2  (0->Scroll lock indicator, 1->numeric lock, 2->caps lock)

/* Status Register */

#define PARITY BIT(7) //Parity error - invalid data

#define TIMEOUT BIT(6) //Timeout error - invalid data

#define AUX BIT(5) //Mouse Data

#define INH BIT(4) //nhibit flag: 0 if keyboard is inhibited

#define A2 BIT(3) //A2 input line: 0 data byte ; 1 command byte

#define SYS BIT(2)//System flag: 0 if system in power-on reset ; 1 if system already initialized

#define IBF BIT(1) //Input buffer full don’t write commands or arguments

#define OBF BIT(0) //Output buffer full - data available for reading


/* Keyboard-Related KBC Commands for PC-AT/PS2 */

#define READ_COMM_BYTE 0x20 //Returns Command Byte

#define WRITE_COMM_BYTE 0x60  //ATENCAO  Takes A: Command Byte

#define CHECK_KBC 0xAA //Returns 0x55, if OK ; Returns 0xFC, if error

#define CHECK_KBD_INTERFACE 0xAB //Returns 0, if OK

#define DISABLE_KBD_INT 0xAD

#define ENABLE_KBD_INT 0xAE


/**@}*/

#endif /* _LCOM_I8042_H_ */
