#include "bullet.h"

/******************************* Bullet functions *****************************************/

Bullet* InitBullet(int x, int y, int strength, int player, int type_of_bullet, char* name_bullet)
{
	Bullet* b = (Bullet *)malloc(sizeof(Bullet));

	b->bullet_bmp = loadBitmap(getImagePath(name_bullet));

	b->vel_x = Bullet_X_Speed;
	b->vel_y = Bullet_Y_Speed;

	b->x = x;
	b->y = y;
	b->strength = strength;
	b->player = player;
	b->type_of_bullet = type_of_bullet;
	b->width = b->bullet_bmp->bitmapInfoHeader.width;  //+10, serve para dar margem caso a imagem esteja em movimento
	b->height = b->bullet_bmp->bitmapInfoHeader.height;

	b->BulletS = move;

	return b;
}

void moveBullet(Bullet* b, int dist_x, int dist_y)
{
	if (b->player == 1)
	{
		if (b->type_of_bullet == 1)
		{

			b->y += b->vel_y;
			if ((dist_y / b->vel_y) >= dist_x)
			{
				b->x += 1;
			}
			else
			{
				b->x += dist_x / (dist_y / b->vel_y);

			}

		}
		else
		{
			b->x += b->vel_x;
		}
	}
	else
	{
		if (b->type_of_bullet == 1)
		{
			//printf("disY: %d, distX: %d\n", dist_y, dist_x);
			b->y += b->vel_y;
			if ((dist_y / b->vel_y) >= dist_x)
			{

				b->x -= 1;

			}
			else
			{
				//printf("vel x= %d\n", dist_x/(dist_y/b->vel_y));

				b->x -= dist_x / (dist_y / b->vel_y);
			}


		}
		else
		{
			b->x -= b->vel_x;
		}
	}

}

int checkBulletFloorCollision(Bullet* b)
{
	if (b->y + b->height >= InY)
	{
		return 1;
	}
	return 0;
}

void drawBullet(Bullet* b, char* doubleBuffer)
{
	if (b->player == 1)
		bitmap_draw_transparency(b->bullet_bmp, b->x, b->y, ALIGN_LEFT, doubleBuffer);
	else
		bitmap_draw_transparency(b->bullet_bmp, b->x, b->y, ALIGN_RIGHT, doubleBuffer);
}

void deleteBullet(Bullet* b)
{
	deleteBitmap(b->bullet_bmp);
	free(b);
}
