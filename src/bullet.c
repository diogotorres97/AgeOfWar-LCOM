#include "bullet.h"

/******************************* Bullet functions *****************************************/


Bullet* InitBullet( int x,  int y, int strength,  int player,  int type_of_bullet, char* name_bullet)
{
	Bullet* b = (Bullet *) malloc(sizeof(Bullet));

	b->bullet_bmp=loadBitmap(getImagePath(name_bullet));

	b->vel_x=Bullet_X_Speed;
	b->vel_y=Bullet_Y_Speed;

	b->x=x;
	b->y=y;
	b->strength=strength;
	b->player=player;
	b->type_of_bullet=type_of_bullet;
	b->width=b->bullet_bmp->bitmapInfoHeader.width;  //+10, serve para dar margem caso a imagem esteja em movimento
	b->height=b->bullet_bmp->bitmapInfoHeader.height;

	b->BulletS=move;

	return b;

}

void moveBullet(Bullet* b)
{
	if(b->player==1)
	{
		if(b->type_of_bullet==1)
		{
			//A FAZER PELO DIOGO , BULLETS TÊM DE SE MEXER NA DIAGONAL
		}
		else
		{
			b->x+=b->vel_x;
		}
	}
	else
	{
		if(b->type_of_bullet==1)
		{
			//A FAZER PELO DIOGO , BULLETS TÊM DE SE MEXER NA DIAGONAL
		}
		else
		{
			b->x-=b->vel_x;
		}
	}

}

void drawBullet(Bullet* b, char* doubleBuffer)
{
	if(b->player==1)
		drawBitmap(b->bullet_bmp, b->x, b->y, ALIGN_LEFT, doubleBuffer);
	else
		drawBitmap(b->bullet_bmp, b->x, b->y, ALIGN_RIGHT, doubleBuffer);
}

void deleteBullet(Bullet* b)
{
	deleteBitmap(b->bullet_bmp);
	free(b);
}
