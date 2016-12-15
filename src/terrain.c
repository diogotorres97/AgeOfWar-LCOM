#include "terrain.h"

Terrain* InitTerrain(int level){
	Terrain * terr = (Terrain*)malloc(sizeof(Terrain));
	terr->back_bmp=loadBitmap(getImagePath("background"));

	return terr;
}

void drawTerrain(Terrain* terr, char* doubleBuffer){

	drawBitmap(terr->back_bmp, 0, 0, ALIGN_LEFT,doubleBuffer);
}

void deleteTerrain(Terrain* terr){
	deleteBitmap(terr->back_bmp);
	free(terr);
}
