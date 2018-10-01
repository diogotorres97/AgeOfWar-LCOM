#ifndef __GAME_H
#define __GAME_H


#include <minix/drivers.h>
#include <minix/syslib.h>
#include "stdbool.h"
#include "stdio.h"
#include <stdlib.h>

#include "const.h"
#include "unit.h"
#include "bullet.h"
#include "tower.h"
#include "slot.h"
#include "defense.h"
#include "special.h"
#include "timer.h"
#include "mouse.h"
#include "keyboard.h"
#include "player.h"
#include "terrain.h"
#include "video_gr.h"
#include "test_animation.h"
#include "math.h"


/** @defgroup game game
* @{
*
* Functions used to create all the objects of the game
*/

typedef struct {
    Player *p1;
    Player *p2;
    Terrain *GameTerrain;
    Animation *GameAnime;
    unsigned int mode;

    int created_unit;
    int timer_cntr;
    int special_cntr1;
    int special_cntr2;

    int used_special1;
    int used_special2;

    int time_left_special1;
    int time_left_special2;

    int show_special1;
    int show_special2;

    char *gameBuffer;
    int timer_anime;

    int current_back;

    Bitmap *menu_l_bmp; //menu for p1
    Bitmap *menu_r_bmp; //menu for p2
    Bitmap *special_charge_bmp; //special charging image

} Game;


/**
* @brief init of the game
*
* @param mode - if it is multiplayer in the same PC (0)
* @return pointer to the game struct
*/
Game *InitGame(unsigned int mode);

/**
* @brief updates players objects
*
* @param pointer to the game struct
* @return
*/
void updateGame(Game *g);

/**
* @brief draw of players objects to the buffer, as well as the background
*
* @param pointer to the game struct
* @return
*/
void drawGame(Game *g);

/**
* @brief erases the game
*
* @param pointer to the game struct
* @return
*/
void deleteGame(Game *g);

/**
* @brief check if there is collision between 2 units
*
* @param u1 - pointer to unit from player 1
* @param u2 - pointer to unit from player 2
* @return 1 if true, 0 if false
*/
int checkUnitCollision(Unit *u1, Unit *u2);

/**
* @brief check if the enemy unit is inside of the first players unit range
*
* @param u1 - pointer to unit of type 1
* @param u2 - u1 - pointer to the other unit
* @return 1 if true, 0 if false
*/
int checkUnitEnemyUnitRange(Unit *u1, Unit *u2);

/**
* @brief simulates the battle between 2 units
*
* @param u1 - pointer to unit from player 1
* @param u2 - pointer to unit from player 2
* @return
*/
void battleBetweenUnits(Unit *u1, Unit *u2);

/**
* @brief check if there is collision between a bullet and an unit
*
* @param b - pointer to bullet
* @param u - pointer to unit
* @return 1 if true, 0 if false
*/
int checkBulletsUnitsCollision(Bullet *b, Unit *u);

/**
* @brief deals with all the hardware interrupts
*
* @param pointer to the game struct
* @param key - if a key is pressed or released its code is stored in key
* @return
*/

void kbdInterruptHandler(Game *g, unsigned long key);

/** @} end of Game */

#endif
