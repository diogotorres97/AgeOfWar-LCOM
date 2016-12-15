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

	//gqueue_t *units;

	Unit* units[MAX_UNITS];

	unsigned int level;

	Tower* t;
	//Special* s;
	//Defense* d;

	unsigned int side; //0-> left, 1->right
	int money;
	int experience;


} Player;


/**
 * @brief initiates unit object
 *
 * @param side - side to which player's units will be headed
 * @return pointer to the unit struct
 */
Player* InitPlayer(unsigned int side);

/**
 * @brief sets this player money to newMoney
 *
 * @param p- pointer to the player object
 * newMoney - money to set
 * @return
 */
void setMoney(Player* p, int newMoney);

/**
 * @brief deletes the player
 *
 * @param pointer to the player object
 * @return
 */
void deletePlayer(Player* p);

/**
 * @brief sets the player current level
 *
 * @param pointer to the player object
 * level to set
 * @return
 */
void setLevel(Player* p, unsigned int level);
/**
 * @brief adds an unit to the queue of units
 *
 * @param pointer to the player object
 * pointer to the unit object
 * @return
 */
void addUnits(Player* p, Unit* u);

/**
 * @brief verifies if units are empty
 *
 * @param pointer to the player object
 * @return 1 -> true, 0->false
 */
int emptyUnits(Player* p);

/**
 * @brief verifies if units are full
 *
 * @param pointer to the player object
 * @return 1 -> true, 0->false
 */
int fullUnits(Player* p);

/**
 * @brief gives the new unit position
 *
 * @param pointer to the player object
 * @return position of the new unit
 */
int newPosUnit(Player* p);

/**
 * @brief check if there is collision between 2 units
 *
 * @param u1, u2 - pointers to units
 * player - indicates the side of the player (1-> left, 2-> right)
 * @return 1 if true, 0 if false
 */
int checkUnitCollisionSamePlayer(Unit* u1, Unit* u2, int player);

/**
 * @brief check if there is collision between an unit and a tower
 *
 * @param u - pointer to unit
 * t - pointer to tower
 * @return 1 if true, 0 if false
 */
int checkUnitsTowerCollision(Unit* u, Tower* t);

/**
 * @brief check if there is collision between a bullet and an unit
 *
 * @param b - pointer to bullet
 * t - pointer to tower
 * @return 1 if true, 0 if false
 */
int checkBulletsTowerCollision(Bullet* b, Tower* t);

/**
 * @brief check if the tower is inside of the unit range
 *
 * @param u - pointer to unit
 * t - pointer to tower
 * @return 1 if true, 0 if false
 */
int checkUnitTowerRange(Unit* u, Tower* t);

/**
 * @brief delete an unit from the array of units
 *
 * @param pointer to the player object
 * @return
 */
void removeUnit(Player* p);

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
