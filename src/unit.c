#include "unit.h"

/******************************* Unit functions *****************************************/

Unit* InitUnit(unsigned int x, unsigned int y, unsigned int hp, unsigned int strength,unsigned int type, char* name_unit,
		unsigned int price, unsigned int reward_for_killing, unsigned int exp_for_killing){

	Unit *u = (Unit *) malloc(sizeof(Unit));
	/*
	char* name_of_image_stopped;
	char* name_of_image_moving;

	name_of_image_stopped=malloc(strlen(PATH)+strlen(name_unit)+strlen(IMG_STPD)+strlen(BMP_EXT)+1);
	strcpy(name_of_image_stopped, PATH);
	strcat(name_of_image_stopped, name_unit);
	strcat(name_of_image_stopped, IMG_STPD);
	strcat(name_of_image_stopped, BMP_EXT);*/
	u->unit_bmp=loadBitmap(getImagePath(name_unit));
	/*
	name_of_image_moving=malloc(strlen(PATH)+strlen(name_unit)+strlen(IMG_MOV)+strlen(BMP_EXT)+1);
	strcpy(name_of_image_moving, PATH);
	strcat(name_of_image_moving, name_unit);
	strcat(name_of_image_moving, IMG_MOV);
	strcat(name_of_image_moving, BMP_EXT);
	u->unit_standing_bmp=loadBitmap(name_of_image_moving);*/



	u->x=x;
	u->y=y;
	u->vel=Unit_Speed;
	u->hp=hp;
	u->strength=strength;
	u->type=type;
	u->price=price;
	u->reward_for_killing=reward_for_killing;
	u->exp_for_killing=exp_for_killing;
	u->width=u->unit_bmp->bitmapInfoHeader.width + 10;  //+10, serve para dar margem caso a imagem esteja em movimento
	u->height=u->unit_bmp->bitmapInfoHeader.height;

	u->UnitS=standing;

	return u;

	//CONTINUAR
}

void MoveUnit(Unit *u)
{
	u->x+=u->vel;

}

void DrawUnit(Unit *u)
{
	drawBitmap(u->unit_bmp, u->x, u->y, ALIGN_LEFT);

}

void unitSetHP(Unit *u, unsigned int new_hp)
{
	u->hp=new_hp;
}


void deleteUnit(Unit *u)
{
	deleteBitmap(u->unit_bmp);
	free(u);
}
