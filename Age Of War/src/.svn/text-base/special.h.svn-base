#ifndef __SPECIAL_H
#define __SPECIAL_H


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


/** @defgroup Special Special
 * @{
 *
 * Functions that special may execute
 */


typedef enum{
	attack,
	charging,
	available,

}SpecialState;

typedef struct Special{

	int strength;
	int x;
	int y;
	int player;
	char* special_name;

	SpecialState SpecialS;

	Bitmap* special_bmp;

}Special;

/**
 * @brief initiates special object
 *
 * @param x_pos - tower position in x
 * @param strength - special's strength
 * @param name_special - name of tower's image
 * @param player - to which player (1 or 2) this special belongs, it determines the special orientation (left or right)

 * @return pointer to the unit struct
 */
Special* InitSpecial( int x, int strength, char* name_tower,  int player);

/**
 * @brief draws the special to the second buffer
 *
 * @param pointer to special
 * @param pointer to doubleBuffer
 * @return
 */
void DrawSpecial(Special *s, char* doubleBuffer);


/**
 * @brief sets strength to the arg
 *
 * @param s - pointer to special
 * @param newStrength - new strength
 * @return
 */
void specialSetStrength(Special* s, int newStrength);

/**
 * @brief delete special
 *
 * @param pointer to special
 * @return
 */
void deleteSpecial(Special *s);

/** @} end of Special */

#endif
