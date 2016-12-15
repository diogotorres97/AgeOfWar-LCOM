#include "unit.h"

/******************************* Unit functions *****************************************/

Unit* InitUnit( int x,  int y, int hp,  int strength, int type, char* name_unit,
		 int price,  int exp_for_killing,  int player){

	Unit *u = (Unit *) malloc(sizeof(Unit));

	u->unit_bmp=loadBitmap(getImagePath(name_unit));

	u->bullets[0]=(Bullet *)malloc(sizeof(Bullet));
	u->bullets[0]=NULL;


	u->x=x;
	u->y=y;
	u->vel=Unit_Speed;
	u->hp=hp;
	u->strength=strength;
	u->type=type;
	u->price=price;
	u->reward_for_killing=price*(4.0/3);
	u->exp_for_killing=exp_for_killing;
	u->player=player;
	u->width=u->unit_bmp->bitmapInfoHeader.width;  //+10, serve para dar margem caso a imagem esteja em movimento
	u->height=u->unit_bmp->bitmapInfoHeader.height;


	if(u->type==1)
		u->range=Unit_TYPE1_Range;

	u->killed=0;
	u->UnitS=standing;

	return u;

	//CONTINUAR
}

void MoveUnit(Unit *u)
{
	if(u->player==1)
		u->x+=u->vel;
	else
		u->x-=u->vel;
}

void DrawUnit(Unit *u,char* doubleBuffer)
{
	if(u->player==1)
		drawBitmap(u->unit_bmp, u->x, u->y, ALIGN_LEFT, doubleBuffer);
	else
		drawBitmap(u->unit_bmp, u->x, u->y, ALIGN_RIGHT,doubleBuffer);
}

void addBullets(Unit* u, Bullet* b)
{
	u->bullets[0]=b;
}


int emptyBullets(Unit* u)
{
	if(u->bullets[0]==NULL)
		return 1;
	else
		return 0;
}

int fullBullets(Unit* u)
{
	if(u->bullets[0]!=NULL)
		return 1;
	else
		return 0;
}

void removeBullet(Unit* u)
{
	u->bullets[0]=NULL;
}

void unitSetHP(Unit *u, int new_hp)
{
	u->hp=new_hp;
}


void deleteUnit(Unit *u)
{
	deleteBitmap(u->unit_bmp);
	free(u);
}
