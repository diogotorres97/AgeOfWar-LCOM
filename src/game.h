#ifndef __GAME_H
#define __GAME_H


#include <minix/drivers.h>
#include <minix/syslib.h>
#include "stdbool.h"
#include "stdio.h"
#include <stdlib.h>

#include "const.h"
#include "unit.h"
#include "bullet.h"
#include "tower.h"
#include "defense.c"
#include "special.c"
#include "timer.h"
#include "mouse.h"
#include "keyboard.h"
#include "player.h"
#include "gqueue.h"

#include "math.h"


/** @defgroup game game
 * @{
 *
 * Functions used to create all the objects of the game
 */

typedef struct {
	Player* p1;
	Player* p2;

	unsigned int mode;


	//irqs

	int irq_timer;
	int irq_mouse;
	int irq_kbd;


	int timer_flag;
	int kbd_flag;
	int mouse_flag;
	int timer_cntr;
	int created_unit;

	bool end;
	bool pause;


	//gqueue_t *types_of_units=new_gqueue(NUM_TYPES_UNITS, sizeof(Unit));


	Bitmap* back_bmp;
} Game;


/**
 * @brief init of the game
 *
 * @param mode - if it is multiplayer in the same PC (0) or between 2 PC's (1)
 * @return pointer to the game struct
 */
Game* InitGame(unsigned int mode);

/**
 * @brief updates players objects
 *
 * @param pointer to the game struct
 * @return
 */
void updateGame(Game* g);

/**
 * @brief draw of players objects to the buffer, as well as the background
 *
 * @param pointer to the game struct
 * @return
 */
void drawGame(Game* g);

/**
 * @brief erases the game
 *
 * @param pointer to the game struct
 * @return
 */
void deleteGame(Game* g);

/**
 * @brief deals with all the hardware interrupts
 *
 * @param pointer to the game struct
 * key - if a key is pressed or released its code is stored in key
 * @return
 */
void gameInterruptHandler(Game* g, unsigned long *key);

/**
 * @brief creates the actions for each released key
 *
 * @param pointer to the game struct
 * key - key that was released
 * @return
 */
void kbdInterruptHandler(Game* g, unsigned long key);

/**
 * @brief check if there is collision between 2 units
 *
 * @param u1, u2 - pointers to units
 * @return 1 if true, 0 if false
 */
int checkUnitCollision(Unit* u1, Unit* u2);

/**
 * @brief subscribes the devices
 *
 * @param pointer to the game struct
 * @return 1 if error, 0 if OK
 */
int subscribeDevices(Game* g);

/**
 * @brief unsubscribes the devices
 *
 * @param pointer to the game struct
 * @return
 */
void unsubscribeDevices(Game* g);

/**
 * @brief creates the queue with the types of units
 *
 * @param pointer to the game struct
 * @return
 */

//void createUnitTypes(Game* g);

#endif
