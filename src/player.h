#ifndef __PLAYER_H
#define __PLAYER_H


#include <minix/syslib.h>
#include <minix/drivers.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "video_gr.h"
#include <time.h>
#include <math.h>
#include "const.h"
#include "bullet.h"
#include "unit.h"
#include "tower.h"
#include "defense.c"
#include "special.c"
#include "gqueue.h"

/** @defgroup player player
 * @{
 *
 * Functions related to the players
 */

typedef struct {

	gqueue_t *units;

	Tower* t;
	//Special* s;
	//Defense* d;

	unsigned int side; //0-> left, 1->right
	unsigned int money;
	unsigned int experience;


} Player;


/**
 * @brief initiates unit object
 *
 * @param side - side to which player's units will be headed
 * @return pointer to the unit struct
 */
Player* InitPlayer(unsigned int side);

/**
 * @brief update plaer
 *
 * @param pointer to the player object
 * @return
 */
void updatePlayer(Player* p);

/**
 * @brief deletes the player
 *
 * @param pointer to the player object
 * @return
 */
void deletePlayer(Player* p);

/**
 * @brief adds an unit to the queue of units
 *
 * @param pointer to the player object
 * pointer to the unit object
 * @return
 */
void addUnits(Player* p, Unit* u);

/**
 * @brief delete an unit from the queue of units
 *
 * @param pointer to the player object
 * pointer to the unit object
 * @return
 */
void deleteUnits(Player* p, Unit* u);

/**
 * @brief sets the tower
 *
 * @param pointer to the player object
 * pointer to the tower object
 * @return
 */
void setTower(Player* p, Tower* t);


/**
 * @brief sets the defense
 *
 * @param pointer to the player object
 * pointer to the defense object
 * @return
 */
//void setDefense(Player* p, Defense* d);


#endif
