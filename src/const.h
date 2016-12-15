#ifndef _LCOM_CONST_H_
#define _LCOM_CONST_H_

/** @defgroup CONST CONST
 * @{
 *
 * Constants for programming the i8254 Timer and the i8042 keyoard, as well as other util constants and macros.
 */

/* UTILS */

#define BIT(n) (0x01<<(n))

#define TRIES 5


/* CONSTANTS RELATED TO THE GAME */

#define MAX_UNITS     10

#define MAX_BULLETS    1

#define NUM_TYPES_UNITS     15

#define InY			500 //Initial y for objects

#define InX_P1		0 //Unit initial x for player 1
#define InX_P2		1024 //Unit initial x for player 2
#define In_Units_Y 		600 //Unit initial y




/* TIMER MACROS */

#define TIMER_FREQ  1193182    /**< @brief clock frequency for timer in PC and AT */

#define TIMER0_IRQ	       	 0    /**< @brief Timer 0 IRQ line */

#define TIMER_DEFAULT_FREQ	60

#define TIMER_HOOK_ID		 1

/* MASKS */

#define BIT_MASK_EIGHT		0xFF // 0000 0000 XXXX XXXX
#define MASK_ZERO 			0x00
#define MASK_4LSB_1 		(BIT(3)|BIT(2)|BIT(1)|BIT(0))
#define MASK_ACESS_TIME		(BIT(5) | BIT(4))
#define MASK_PROGRAMMED_MODE (BIT(3)|BIT(2)|BIT(1))	 // 0000 1110

/* I/O port addresses */

#define TIMER_0			0x40 /**< @brief Timer 0 count register */
#define TIMER_1			0x41 /**< @brief Timer 1 count register */
#define TIMER_2			0x42 /**< @brief Timer 2 count register */
#define TIMER_CTRL		0x43 /**< @brief Control register */

#define SPEAKER_CTRL		0x61 /**< @brief Register for speaker control  */

/* Timer control */

/* Timer selection: bits 7 and 6 */

#define TIMER_SEL0		0x00     /**< @brief Control Word for Timer 0 */
#define TIMER_SEL1		BIT(6)   /**< @brief Control Word for Timer 1 */
#define TIMER_SEL2		BIT(7)   /**< @brief Control Word for Timer 2 */
#define TIMER_RB_CMD		(BIT(7)|BIT(6))  /**< @brief Read Back Command */

/* Register selection: bits 5 and 4 */

#define TIMER_LSB		BIT(4)  /**< @brief Initialize Counter LSB only */
#define TIMER_MSB		BIT(5)  /**< @brief Initialize Counter MSB only */
#define TIMER_LSB_MSB		(TIMER_LSB | TIMER_MSB) /**< @brief Initialize LSB first and MSB afterwards */

/* Operating mode: bits 3, 2 and 1 */

#define TIMER_INT_COUNT		0x00			/**< @brief MODE 0: INTERRUPT ON TERMINAL COUNT */
#define TIMER_HW_RETR		BIT(1)	 		/**< @brief MODE 1: HARDWARE RETRIGGERABLE ONE-SHOT */
#define TIMER_RATE_GEN		BIT(2)          /**< @brief Mode 2: rate generator */
#define TIMER_SQR_WAVE		(BIT(2)|BIT(1)) /**< @brief Mode 3: square wave generator */
#define TIMER_SW_TRIG 		BIT(3)	 		/**< @brief MODE 4: SOFTWARE TRIGGERED STROBE */
#define TIMER_HW_TRIG 		(BIT(3)|BIT(1))	/**< @brief MODE 5: HARDWARE TRIGGERED STROBE (RETRIGGERABLE) */

/* Counting mode: bit 0 */

#define TIMER_BCD			0x01   /**< @brief Count in BCD */
#define TIMER_BIN			0x00   /**< @brief Count in binary */

/* READ-BACK COMMAND FORMAT */

#define TIMER_RB_COUNT_         BIT(5)
#define TIMER_RB_STATUS_        BIT(4)
#define TIMER_RB_SEL(n)         BIT((n)+1)


/* KEYBOARD MACROS */

#define KEYBOARD_HOOK_ID 4

#define IRQ1 1

#define DELAY_US 20000

#define ESC_BREAKCODE 0x81

#define FIRST_OF_TWO_BYTE_SCANCODES 0xE0

#define KBD_ACK 0xFA

#define KBD_RESEND 0xFE

#define KBD_ERROR 0xFC

#define CAPS_LOCK BIT(2)

#define SCROLL_LOCK BIT(0)

#define NUMERIC_LOCK BIT(1)

/* PORTS */

#define STAT_REG 0x64

#define OUT_BUF 0x60

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

/* GRAPHIC MACROS */

#define VRAM_PHYS_ADDR        0xE0000000

#define H_RES					1024

#define V_RES					768

#define BITS_PER_PIXEL          8

#define VRAM_SIZE 			H_RES*V_RES*BITS_PER_PIXEL/8

/*Mouse constants */


#define IRQ12 12

#define MOUSE_HOOK_ID 5

#define EDR	0xF4 //enable data report

#define DDR	0xF5 //disable data report

#define SSME	0xEA //stream enable

#define SSMD	0xFA //stream disable

#define STATUS_REQUEST 0xE9

#define M_ARGS 0xD4

#define MOUSE_ACK 0xFA

#define MOUSE_NACK 0xFE

#define MOUSE_ERROR 0xFC

#define TOLERANCE 5

#define LB BIT(0)

#define RB BIT(1)

#define MB BIT(2)

#define XS BIT(4)

#define YS BIT(5)

#define XO BIT(6)

#define YO BIT(7)

#define COMP 0xFF
/**@}*/

#endif /* _LCOM_CONST_H_ */
