#ifndef __UNIT_H
#define __UNIT_H


#include <minix/syslib.h>
#include <minix/drivers.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "video_gr.h"
#include <time.h>
#include <math.h>
#include "const.h"
#include "bullet.h"
#include "tower.h"

/** @defgroup Unit Unit
 * @{
 *
 * Functions that units may execute, and also the struct for units creation
 */


#define Unit_Speed		7 //Unit speed


typedef enum{
	attacking,
	moving,
	standing,
	killed,
}UnitActualState;

typedef struct Unit{

	unsigned int hp;
	unsigned int strength;
	unsigned int type;
	unsigned int price;
	unsigned int reward_for_killing;
	unsigned int exp_for_killing;
	//unsigned int player;

	unsigned int x;
	unsigned int y;
	unsigned int vel;

	unsigned int width;
	unsigned int height;

	unsigned int in_battle;

	UnitActualState UnitS;

	Bitmap* unit_bmp;
	//Bitmap* unit_moving_bmp;
}Unit;

/**
 * @brief initiates unit object
 *
 * @param x_pos - unit position in x
 * y_pos - unit position in y
 * hp - unit initial hp
 * strength - unit strength
 * type - (0,1,2) type of unit
 * price - how much does it cost to make this unit
 * reward_for_killing - how much gold does the other player get when kills this unit
 * exp_for_killing - how much exp does the other player get when kills this unit
 * player - to which player this unit belongs, it determines the unit orientation (left or right)
 * @return pointer to the unit struct
 */
Unit* InitUnit(unsigned int x, unsigned int y, unsigned int hp, unsigned int strength,	unsigned int type, char* name_unit, unsigned int price,
		unsigned int reward_for_killing, unsigned int exp_for_killing);



/**
 * @brief updates unit coordinates
 *
 * @param pointer to unit
 * @return
 */
void MoveUnit(Unit *u);

/**
 * @brief draw unit to the second buffer
 *
 * @param pointer to unit
 * @return
 */
void DrawUnit(Unit *u);

/**
 * @brief update unit
 *
 * @param pointer to unit
 * @return
 */
//void updateUnit(Unit *u);

/**
 * @brief sets HP to the arg
 *
 * @param pointer to unit
 * hp - new hp
 * @return
 */
void unitSetHP(Unit *u, unsigned int new_hp);

/**
 * @brief check if there is collision between an unit and a tower
 *
 * @param pointer to tower
 * @return 1 if yes, 0 otherwise
 */
int CheckUnitsTowerCollision(Tower *t);

/**
 * @brief delete unit
 *
 * @param pointer to unit
 * @return
 */
void deleteUnit(Unit *u);

#endif
