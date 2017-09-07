#ifndef __TESTANIMATION_H
#define __TESTANIMATION_H

#include <string.h>
#include "bitmap.h"

/** @defgroup Animation Animation
* @{
*
* Functions for test animation
*/

#define LVL1_1_A 40
#define LVL1_1_D 24
#define LVL1_1_M 43
#define LVL1_1_S 0

#define LVL1_2_A 40
#define LVL1_2_D 24
#define LVL1_2_M 43
#define LVL1_2_S 32

#define LVL1_3_A 45
#define LVL1_3_D 50
#define LVL1_3_M 40
#define LVL1_3_S 0

#define LVL2_1_A 47
#define LVL2_1_D 44
#define LVL2_1_M 40
#define LVL2_1_S 0

#define LVL2_2_A 47
#define LVL2_2_D 44
#define LVL2_2_M 40
#define LVL2_2_S 40

#define LVL2_3_A 52
#define LVL2_3_D 22
#define LVL2_3_M 40
#define LVL2_3_S 0

#define LVL3_1_A 36
#define LVL3_1_D 30
#define LVL3_1_M 47
#define LVL3_1_S 0

#define LVL3_2_A 46
#define LVL3_2_D 54
#define LVL3_2_M 47
#define LVL3_2_S 46

#define LVL3_3_A 54
#define LVL3_3_D 38
#define LVL3_3_M 48
#define LVL3_3_S 54

#define LVL4_1_A 30
#define LVL4_1_D 29
#define LVL4_1_M 49
#define LVL4_1_S 0

#define LVL4_2_A 21
#define LVL4_2_D 20
#define LVL4_2_M 47
#define LVL4_2_S 21

#define LVL4_3_A 63
#define LVL4_3_D 14
#define LVL4_3_M 10
#define LVL4_3_S 63

#define LVL5_1_A 37
#define LVL5_1_D 65
#define LVL5_1_M 47
#define LVL5_1_S 0

#define LVL5_2_A 54
#define LVL5_2_D 38
#define LVL5_2_M 34
#define LVL5_2_S 14

#define LVL5_3_A 40
#define LVL5_3_D 31
#define LVL5_3_M 28
#define LVL5_3_S 40


typedef struct {

	Bitmap** sprites;

	int counter;

}Animation;

/**
 * @brief initialize the Animation
 *
 * @param u1_id
 * @param state
 * @return
 */
Animation* InitAnimation(int u1_id, int state);


/**
 * @brief draw all bitmaps that belong to Animation struct
 *
 * @param anime anime pointer to animation struct
 * @param x
 * @param y
 * @param position
 * @param doubleBuffer
 * @param counter
 * @return
 */
void drawAnimation(Animation* anime, int x, int y, int position, char* doubleBuffer, int counter);

/**
 * @brief delete all resources allocated by the Animation struct
 *
 * @param anime pointer to animation struct
 * @return
 */
void deleteAnimation(Animation* anime);

/**
 * @brief Gets the path of the animation
 * @param path
 * @param state
 * @param count
 * @return
 */
const char* getImagePathAnimation(char* path, unsigned  int state, unsigned  int count);

/** @} end of Animation */

#endif
