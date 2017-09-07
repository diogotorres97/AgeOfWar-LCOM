#ifndef __SLOT_H
#define __SLOT_H

#include "bitmap.h"

/** @defgroup slot slot
* @{
*
* Functions for managing the slots
*/

typedef struct {

	int x;
	int y;
	int width;
	int height;
	int player;

	Bitmap* slot_bmp;

}Slot;

/**
* @brief initiates slot object
*
* @param x_pos - slot position in x
* @param y - slot position in y
* @param name_slot - name of tower's image
* @param player - to which player (1 or 2) this slot belongs, it determines the slot orientation (left or right)
* @param first - if this is the first slot
*
* @return pointer to the slot struct
*/
Slot* InitSlot(int x, int y, char* name_slot, int player, int first);

/**
* @brief draws the slot to the second buffer
*
* @param pointer to slot
* @param pointer to doubleBuffer
* @return
*/
void drawSlot(Slot* s, char* doubleBuffer);

/**
* @brief  slot bitmap to another
*
* @param pointer to the slot object
* @param name_slot - name of slot's image
* @param x - x to set
* @param y - y to set
* @return
*/
void setSlot(Slot* s, char* name_slot, int x, int y);

/**
* @brief delete slot
*
* @param pointer to slot
* @return
*/
void deleteSlot(Slot *s);

/** @} end of Slot */

#endif
