#ifndef __TERRAIN_H
#define __TERRAIN_H

#include "bitmap.h"


/** @defgroup terrain terrain
* @{
*
* Functions for managing the game terrain
*/

typedef struct {
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
void drawTerrain(Terrain* terr, char* doubleBuffer);

/**
* @brief delete all resources allocated by the terrain struct
*
* @param pointer to terrain struct
* @return
*/
void deleteTerrain(Terrain* terr);

/** @} end of Terrain */

#endif
