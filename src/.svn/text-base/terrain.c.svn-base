#include "terrain.h"

/******************************************** Terrain functions *****************************************/

Terrain* InitTerrain(int level) {
	Terrain * terr = (Terrain*)malloc(sizeof(Terrain));
	char buf[10];
	sprintf(buf, "terrain_%d", level);
	terr->back_bmp = loadBitmap(getImagePath(buf));

	return terr;
}

void drawTerrain(Terrain* terr, char* doubleBuffer) {

	drawBitmap(terr->back_bmp, 0, 0, ALIGN_LEFT, doubleBuffer);
}

void deleteTerrain(Terrain* terr) {
	deleteBitmap(terr->back_bmp);
	free(terr);
}
