#ifndef __MOUSE_H
#define __MOUSE_H

#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "bitmap.h"
#include "const.h"
#include "timer.h"
#include <stdbool.h>

/** @defgroup mouse mouse
* @{
*
* Functions used to create all the objects of the mouse
*/

typedef struct {
    int x, y;
    int Xsign, Ysign;
    int Xdelta, Ydelta;

    unsigned long packet[3];
    int packetCounter;

    int leftButton_P, middleButton_P, rightButton_P;

    int mouseWidth, mouseHeight;
    Bitmap *MouseBMP;
} Mouse;

/**
* @brief init the mouse struct
*
* @param
* @return mouse struct
*/
Mouse *InitMouse();

/**
* @brief draw mouse bmp, in the mouse buffer, accordingly to the actual coordinates
*
* @param mouse struct
* @return
*/
void drawMouse(Mouse *mouse, char *doublebuffer);

/**
* @brief free all resources allocated by mouse struct
*
* @param mouse struct
* @return
*/
void deleteMouse(Mouse *mouse);

/**
 * @brief subscribes keyboard interrupts
 * @return
 */
int mouse_subscribe_int(void);

/**
 * @brief unsubscribes keyboard interrupts
 * @return
 */
int mouse_unsubscribe_int();

/**
 * @brief gets status code or data from kbd
 * @return
 */
int mouse_get_packets();

/**
 * @brief sends command
 * @return
 */
int mouse_send_command();

/**
 * @brief sends args
 * @param cmd
 * @return
 */
int mouse_send_args(unsigned long cmd);

/**
 * @brief mouse interrupt handler
 * @param cmd
 * @return
 */
int mouse_int_handler(unsigned long cmd);

/**
 * @brief mouse print packets
 * @param packet
 * @return
 */
int mouse_print_packet(unsigned char packet[]);

/**
 * @brief mouse print config
 * @param packet
 * @return
 */
int mouse_print_config(unsigned char packet[]);

/**
 * @brief mouse state machine
 * @param packet
 * @param length
 * @param delta_y
 * @param situation
 * @return
 */
int mouse_state_machine(unsigned char packet[], short length, unsigned long *delta_y, unsigned long situation);

/**
* @brief read a byte from mouse buffer and set the respective packet
*
* @param mouse struct pointer
* @return
*/
void SetPacket(Mouse *mouse);

/**
* @brief when the 3 bytes packet is read, update the mouse accordingly to the information in those packets
*        the menu flag means if the actual game state is  menu or playing
*
* @param mouse struct pointer
* @return
*/
void updateMouse(Mouse *mouse, int menu_flag);

/** @} end of Mouse */

#endif /* __KEYBOARD_H */
