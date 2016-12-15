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


/** @defgroup Unit Unit
 * @{
 *
 * Functions that units may execute, and also the struct for units creation
 */


#define Unit_Speed		2  //Unit speed
#define Unit_TYPE1_Range   250 		//units range

typedef enum{
	attacking,
	moving,
	standing,
	killed,
}UnitActualState;

typedef struct Unit{

	int hp;
	 int strength;
	 int type;
	 int price;
	 int reward_for_killing;
	 int exp_for_killing;
	// int player;

	int x;
	int y;
	int vel;

	 int width;
	 int height;

	 int in_battle;

	 int player;
	 int range;

	Bullet* bullets[MAX_BULLETS];

	//A REMOVER E SUBSTITUIR POR MAQUINA DE ESTADOS

	 int killed;

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
 * player - to which player (1 or 2) this unit belongs, it determines the unit orientation (left or right)
 * @return pointer to the unit struct
 */
Unit* InitUnit( int x,  int y, int hp,  int strength,	 int type, char* name_unit,  int price,
		  int exp_for_killing,  int player);



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
 * @return
 */
void DrawUnit(Unit *u, char* doubleBuffer);


/**
 * @brief adds a bullet to an unit
 *
 * @param pointer to the unit object
 * pointer to the bullet object
 * @return
 */
void addBullets(Unit* u, Bullet* b);

/**
 * @brief verifies if bullets are empty
 *
 * @param pointer to the unit object
 * @return 1 -> true, 0->false
 */
int emptyBullets(Unit* u);

/**
 * @brief verifies if bullets are full
 *
 * @param pointer to the unit object
 * @return 1 -> true, 0->false
 */
int fullBullets(Unit* u);

/**
 * @brief update unit
 *
 * @param pointer to unit
 * @return
 */
//void updateUnit(Unit *u);

/**
 * @brief delete a bullet from the array of bullets
 *
 * @param pointer to the unit object
 * @return
 */
void removeBullet(Unit* u);

/**
 * @brief sets HP to the arg
 *
 * @param pointer to unit
 * hp - new hp
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

#endif
