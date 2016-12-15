#ifndef __TERRAIN_H
#define __TERRAIN_H

#include "bitmap.h"


/** @defgroup terrain terrain
 * @{
 *
 * Functions for managing the game terrain
 */

/**
 * The game will use 864*720 pixels, so each cell will have 36 pixels
 *
 * 0 is floor bmp
 * 1 is grass bmp
 * 2 is wall bmp
 * 3 is mini tank bmp
 * 4 is score bmp
 * 5 is live bmp
 */

#define CellSize          36
#define HorizontalCells   24
#define VerticalCells     20
#define CellInitialPos    24
#define Width             864
#define Height            720
#define BarInitialX       895
#define arraySize         480
#define LateralBarSize    60
#define ScreenWidth       1024

typedef struct{
	Bitmap* back_bmp;

}Terrain;

/**
 * @brief initialize the terrain
 *
 * @param
 * @return pointer to terrain struct
 */
Terrain* InitTerrain(int level);

/**
 * @brief draw all bitmaps that belong to terrain struct
 *
 * @param pointer to terrain struct
 * @return
 */
void drawTerrain(Terrain* terr,char* doubleBuffer);

/**
 * @brief delete all resources allocated by the terrain struct
 *
 * @param pointer to terrain struct
 * @return
 */
void deleteTerrain(Terrain* terr);

#endif
