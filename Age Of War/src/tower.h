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


/** @defgroup Tower Tower
* @{
*
* Functions that tower may execute
*/


typedef struct Tower {

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
* @param hp - tower initial hp
* @param name_tower - name of tower's image
* @param player - to which player (1 or 2) this tower belongs, it determines the tower orientation (left or right)

* @return pointer to the tower struct
*/
Tower* InitTower(int x, int hp, char* name_tower, int player);

/**
* @brief draws the tower to the second buffer
*
* @param pointer to tower
* @param pointer to doubleBuffer
* @param life_max	max life of the tower
* @param life_current	current life of the tower
* @return
*/
void DrawTower(Tower *t, char* doubleBuffer,int life_max, int life_current);

/**
* @brief sets player's tower bitmap to another
*
* @param pointer to the tower object
* @param name_tower - name of tower's image
* @return
*/
void setTower(Tower* t, char* name_tower);


/**
* @brief sets HP to the arg
*
* @param t - pointer to tower
* @param hp - new hp
* @return
*/
void towerSetHP(Tower* t, int newHP);

/**
* @brief delete tower
*
* @param pointer to tower
* @return
*/
void deleteTower(Tower *t);

/** @} end of Timer */

#endif
