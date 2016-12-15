#include "tower.h"

/******************************* Tower functions *****************************************/

Tower* InitTower( int x,  int y, int hp, char* name_tower,  int player){

	Tower *t = (Tower *) malloc(sizeof(Tower));
	/*
	char* name_of_image_stopped;
	char* name_of_image_moving;

	name_of_image_stopped=malloc(strlen(PATH)+strlen(name_unit)+strlen(IMG_STPD)+strlen(BMP_EXT)+1);
	strcpy(name_of_image_stopped, PATH);
	strcat(name_of_image_stopped, name_unit);
	strcat(name_of_image_stopped, IMG_STPD);
	strcat(name_of_image_stopped, BMP_EXT);*/
	t->tower_bmp=loadBitmap(getImagePath(name_tower));
	/*
	name_of_image_moving=malloc(strlen(PATH)+strlen(name_unit)+strlen(IMG_MOV)+strlen(BMP_EXT)+1);
	strcpy(name_of_image_moving, PATH);
	strcat(name_of_image_moving, name_unit);
	strcat(name_of_image_moving, IMG_MOV);
	strcat(name_of_image_moving, BMP_EXT);
	u->unit_standing_bmp=loadBitmap(name_of_image_moving);*/



	t->x=x;
	t->y=y;
	t->hp=hp;
	t->player=player;
	t->width=t->tower_bmp->bitmapInfoHeader.width;
	t->height=t->tower_bmp->bitmapInfoHeader.height;

	return t;
}

void drawTower(Tower *t, char* doubleBuffer) {

	if(t->player==1)

		drawBitmap(t->tower_bmp, t->x, t->y, ALIGN_LEFT,doubleBuffer);
	else
		drawBitmap(t->tower_bmp, t->x, t->y, ALIGN_RIGHT, doubleBuffer);
}

void towerSetHP(Tower* t, int newHP)
{
	t->hp=newHP;
}

void deleteTower(Tower *t) {
	deleteBitmap(t->tower_bmp);
	free(t);
}
