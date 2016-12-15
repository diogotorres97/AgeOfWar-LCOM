#ifndef __TOWER_H
#define __TOWER_H


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

/** @defgroup Tower Tower
 * @{
 *
 * Functions that tower may execute
 */


typedef struct Tower{

	int hp;
	 int x;
	 int y;
	 int player;

	 int width;
	 int height;

	Bitmap* tower_bmp;

}Tower;

/**
 * @brief initiates tower object
 *
 * @param x_pos - tower position in x
 * y_pos - tower position in y
 * hp - tower initial hp
 * name_tower - name of tower's image
 * player - to which player (1 or 2) this tower belongs, it determines the unit orientation (left or right)

 * @return pointer to the unit struct
 */
Tower* InitTower( int x,  int y, int hp, char* name_tower,  int player);

/**
 * @brief updates tower coordinates
 *
 * @param
 * @return
 */
void DrawTower(Tower *t, char* doubleBuffer);


/**
 * @brief sets HP to the arg
 *
 * @param t - pointer to tower
 * hp - new hp
 * @return
 */
void towerSetHP(Tower* t, int newHP);

/**
 * @brief check if there is collision between an unit and a tower
 *
 * @param pointer to tower
 * @return 1 if yes, 0 otherwise
 */

void deleteTower(Tower *t);

#endif
