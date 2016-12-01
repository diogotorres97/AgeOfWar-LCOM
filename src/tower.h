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

	unsigned int hp;
	unsigned int x;
	unsigned int y;

	unsigned int width;
	unsigned int height;

	Bitmap* tower_bmp;

}Tower;

/**
 * @brief initiates unit object
 *
 * @param x_pos - tower position in x
 * y_pos - tower position in y
 * hp - tower initial hp

 * @return pointer to the unit struct
 */
Tower* InitTower(unsigned int x, unsigned int y, unsigned int hp, char* name_tower);

/**
 * @brief updates unit coordinates
 *
 * @param
 * @return
 */
void DrawTower(Tower *t);

/**
 * @brief update unit
 *
 * @param pointer to unit
 * @return
 */
void updateTower(Tower *t);

/**
 * @brief sets HP to the arg
 *
 * @param hp - new hp
 * @return
 */
void towerSetHP(unsigned int hp);

/**
 * @brief check if there is collision between an unit and a tower
 *
 * @param pointer to tower
 * @return 1 if yes, 0 otherwise
 */

void deleteTower(Tower *t);

#endif
