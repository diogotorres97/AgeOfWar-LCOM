#ifndef __DEFENSE_H
#define __DEFENSE_H


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

typedef struct Defense {


    int x;
    int y;
    int player;
    int range;
    int strength;
    int price;


    int width;
    int height;

    Bullet *bullets[MAX_BULLETS];

    Bitmap *defense_bmp;

} Defense;

/**
* @brief initiates defense object
*
* @param x - defense position in x
* @param y - defense position in y
* @param strength - defense strength
* @param name_defense - name of defense's image
* @param price - cost of the defense
* @param player - to which player (1 or 2) this defense belongs, it determines the defense orientation (left or right)

* @return pointer to the unit struct
*/
Defense *InitDefense(int x, int y, int strength, char *name_defense, int price, int player, int range);

/**
* @brief draws the defense to the second buffer
*
* @param pointer to defense
* pointer to doubleBuffer
* @return
*/
void DrawDefense(Defense *d, char *doubleBuffer);

/**
* @brief verifies if bullets are empty
*
* @param pointer to the unit object
* @return 1 -> true, 0->false
*/
int emptyBulletsDefenses(Defense *d);

/**
* @brief verifies if bullets are full
*
* @param pointer to the unit object
* @return 1 -> true, 0->false
*/
int fullBulletsDefenses(Defense *d);

/**
* @brief delete a bullet from the array of bullets
*
* @param pointer to the defense object
* @return
*/
void removeBulletDefense(Defense *d);

/**
* @brief adds a bullet to a defense
*
* @param pointer to the defense object
* @param pointer to the bullet object
* @return
*/
void addBulletsDefense(Defense *d, Bullet *b);

/**
* @brief delete defense
*
* @param pointer to defense
* @return
*/
void deleteDefense(Defense *d);

/** @} end of Defense */

#endif
