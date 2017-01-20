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
#include "test_animation.h"


/** @defgroup Unit Unit
* @{
*
* Functions that units may execute, and also the struct for units creation
*/


#define Unit_Speed		1  //Unit speed


typedef enum {
	attacking,
	shooting,
	moving,
	standing,
	dying,
}UnitActualState;

typedef struct Unit {

	int hp;
	int strength;
	int type;
	int price;
	int reward_for_killing;
	int exp_for_killing;

	char* name_unit;

	int x;
	int y;
	int vel;

	int id;

	int width;
	int height;

	int in_battle;

	int player;
	int range;

	Bullet* bullets[MAX_BULLETS];

	Animation* UnitAnime_A;
	Animation* UnitAnime_M;
	Animation* UnitAnime_S;
	Animation* UnitAnime_D;

	int killed;

	UnitActualState UnitS;

	Bitmap* unit_bmp;

}Unit;

/**
* @brief initiates unit object
*
* @param x_pos - unit position in x
* @param hp - unit initial hp
* @param strength - unit strength
* @param type - (0,1,2) type of unit
* @param price - how much does it cost to make this unit
* @param reward_for_killing - how much gold does the other player get when kills this unit
* @param exp_for_killing - how much exp does the other player get when kills this unit
* @param player - to which player (1 or 2) this unit belongs, it determines the unit orientation (left or right)
* @param id of the unit
* @return pointer to the unit struct
*/
Unit* InitUnit(int x, int hp, int strength, int type, char* name_unit, int price,
	int exp_for_killing, int player, int id);



/**
* @brief updates unit x and y
*
* @param pointer to unit
* @return
*/
void MoveUnit(Unit *u);

/**
* @brief draw unit to the second buffer
*
* @param pointer to unit
* @param pointer to doubleBuffer
* @param counter of the timer
* @return
*/
void DrawUnit(Unit *u, char* doubleBuffer, int counter);


/**
* @brief adds a bullet to an unit
*
* @param pointer to the unit object
* @param pointer to the bullet object
* @return
*/
void addBulletsUnits(Unit* u, Bullet* b);



/**
* @brief update unit
*
* @param pointer to unit
* @return
*/
//void updateUnit(Unit *u);


/**
* @brief verifies if bullets are empty
*
* @param pointer to the unit object
* @return 1 -> true, 0->false
*/
int emptyBulletsUnits(Unit* u);

/**
* @brief verifies if bullets are full
*
* @param pointer to the unit object
* @return 1 -> true, 0->false
*/
int fullBulletsUnits(Unit* u);

/**
* @brief delete a bullet from the array of bullets
*
* @param pointer to the unit object
* @return
*/
void removeBulletUnit(Unit* u);

/**
* @brief sets HP to the arg
*
* @param pointer to unit
* @param hp - new hp
* @return
*/
void unitSetHP(Unit *u, int new_hp);

/**
* @brief delete unit
*
* @param pointer to unit
* @return
*/
void deleteUnit(Unit *u);

/** @} end of Unit */

#endif
