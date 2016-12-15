#ifndef __BULLET_H
#define __BULLET_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "video_gr.h"
#include "const.h"

/** @defgroup Bullet Bullet
 * @{
 *
 * Functions that are executed by bullets
 */

#define Bullet_X_Speed		5  //Bullet x speed
#define Bullet_Y_Speed		5  //Bullet y speed


typedef enum{
	move,
	destroyed,
}BulletActualState;


typedef struct Bullet{

	 int x;
	 int y;
	 int vel_x;
	 int vel_y;

	 int width;
	 int height;
	 int player;
	 int strength;



	 int type_of_bullet; //defense or unit bullet


	BulletActualState BulletS;

	Bitmap* bullet_bmp;
}Bullet;


/**
 * @brief initiates bullet object
 *
 * @param x_pos - bullet position in x
 * y_pos - bullet position in y
 * strength - bullet strength
 * player - to which player (1 or 2) this unit belongs, it determines the unit orientation (left or right)
 * type - type of bullet (1-> defense, 2-> unit)
 * name_unit - name of bullet image
 * @return pointer to the bullet struct
 */
Bullet* InitBullet( int x,  int y, int strength,  int player,  int type_of_bullet, char* name_bullet);


/**
 * @brief update bullet x and y
 *
 * @param pointer to bullet
 * @return
 */
void moveBullet(Bullet* b);

/**
 * @brief draw bullet to second buffer
 *
 * @param pointer to bullet
 * @return
 */
void drawBullet(Bullet* b, char* doubleBuffer);

/**
 * @brief delete bullet
 *
 * @param pointer to bullet
 * @return
 */
void deleteBullet(Bullet* b);

#endif
