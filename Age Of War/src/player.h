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
#include "defense.h"
#include "special.h"
#include "number.h"
#include "slot.h"

/** @defgroup player player
* @{
*
* Functions related to the players
*/

typedef struct {

    Unit *units[MAX_UNITS];

    Defense *defenses[MAX_DEFENSES];

    Slot *slots_defenses[MAX_SLOTS];

    int slots_available;

    Number *no_money;
    Number *no_exp;
    Number *no_exp_to_evolve;
    Number *no_time_special;
    Number *no_tower_life;

    unsigned int level;

    Tower *t;
    Special *s;


    unsigned int side; //0-> left, 1->right
    int income_per_level;
    int money;
    int experience;
    int defense_current_range;


} Player;


/**
* @brief initiates unit object
*
* @param side - side to which player's units will be headed
* @return pointer to the unit struct
*/
Player *InitPlayer(unsigned int side);

/**
* @brief sets this player money to newMoney
*
* @param p- pointer to the player object
* @param newMoney - money to set
* @return
*/
void setMoney(Player *p, int newMoney);

/**
* @brief sets this player exp to newExp
*
* @param p- pointer to the player object
* @param newExp - exp to set
* @return
*/
void setExperience(Player *p, int newExp);

/**
* @brief sets this defense range to newRange
*
* @param p- pointer to the player object
* @param newRange - range to set
* @return
*/
void setDefenseRange(Player *p, int newRange);

/**
* @brief deletes the player
*
* @param pointer to the player object
* @return
*/
void deletePlayer(Player *p);

/**
* @brief sets the player current level
*
* @param pointer to the player object
* @param level to set
* @return
*/
void setLevel(Player *p, unsigned int level);

/**
* @brief sets the player current income
*
* @param pointer to the player object
* income to set
* @return
*/
void setIncome(Player *p, int income);

/**
* @brief adds an unit to the array of units
*
* @param pointer to the player object
* @param pointer to the unit object
* @return
*/
void addUnits(Player *p, Unit *u);

/**
* @brief adds a defense to the array of defenses
*
* @param pointer to the player object
* @param pointer to the defense object
* @return
*/
void addDefenses(Player *p, Defense *d);

/**
* @brief adds a slot to the array of slots
*
* @param pointer to the player object
* @param pointer to the slot object
* @return
*/
void addSlots(Player *p, Slot *s);

/**
* @brief verifies if units is empty
*
* @param pointer to the player object
* @return 1 -> true, 0->false
*/
int emptyUnits(Player *p);

/**
* @brief verifies if units is full
*
* @param pointer to the player object
* @return 1 -> true, 0->false
*/
int fullUnits(Player *p);

/**
* @brief counts the number of units
*
* @param pointer to the player object
* @return 1 -> true, 0->false
*/
int countUnits(Player *p);

/**
* @brief counts the number of defenses
*
* @param pointer to the player object
* @return 1 -> true, 0->false
*/
int countDefenses(Player *p);

/**
* @brief counts the number of slots
*
* @param pointer to the player object
* @return 1 -> true, 0->false
*/
int countSlots(Player *p);

/**
* @brief verifies if defenses is empty
*
* @param pointer to the player object
* @return 1 -> true, 0->false
*/
int emptyDefenses(Player *p);

/**
* @brief verifies if defenses is full
*
* @param pointer to the player object
* @return 1 -> true, 0->false
*/
int fullDefenses(Player *p);

/**
* @brief verifies if slots is empty
*
* @param pointer to the player object
* @return 1 -> true, 0->false
*/
int emptySlots(Player *p);

/**
* @brief verifies if slots is full
*
* @param pointer to the player object
* @return 1 -> true, 0->false
*/
int fullSlots(Player *p);

/**
* @brief gives the new unit position
*
* @param pointer to the player object
* @return position of the new unit
*/
int newPosUnit(Player *p);

/**
* @brief gives the new defense position
*
* @param pointer to the player object
* @return position of the new defense
*/
int newPosDefense(Player *p);

/**
* @brief gives the new slot position
*
* @param pointer to the player object
* @return position of the new defense
*/
int newPosSlot(Player *p);

/**
* @brief check if the unit is inside of the defense range
*
* @param u - pointer to unit
* @param d - pointer to defense
* @return 1 if true, 0 if false
*/
int checkUnitsDefenseRange(Unit *u, Defense *d);

/**
* @brief check if there is collision between 2 units
*
* @param u1, u2 - pointers to units
* @param player - indicates the side of the player (1-> left, 2-> right)
* @return 1 if true, 0 if false
*/
int checkUnitCollisionSamePlayer(Unit *u1, Unit *u2, int player);

/**
* @brief check if there is collision between an unit and a tower
*
* @param u - pointer to unit
* @param t - pointer to tower
* @return 1 if true, 0 if false
*/
int checkUnitsTowerCollision(Unit *u, Tower *t);

/**
* @brief check if there is collision between a bullet and an unit
*
* @param b - pointer to bullet
* @param t - pointer to tower
* @return 1 if true, 0 if false
*/
int checkBulletsTowerCollision(Bullet *b, Tower *t);

/**
* @brief check if the tower is inside of the unit range
*
* @param u - pointer to unit
* @param t - pointer to tower
* @return 1 if true, 0 if false
*/
int checkUnitTowerRange(Unit *u, Tower *t);

/**
* @brief delete an unit from the array of units
*
* @param pointer to the player object
* @return
*/
void removeUnit(Player *p);

/**
* @brief delete a defense from the array of defenses
*
* @param pointer to the player object
* @return
*/
void removeDefense(Player *p);

/**
* @brief delete a slot from the array of slots
*
* @param pointer to the player object
* @return
*/
void removeSlot(Player *p);

/** @} end of Player */


#endif
