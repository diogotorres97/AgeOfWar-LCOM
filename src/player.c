#include "player.h"

Player* InitPlayer(unsigned int side)
{
	Player *p=(Player *) malloc(sizeof(Player));


	int counter=0;


	while(counter<MAX_UNITS)
	{
		p->units[counter]=(Unit *)malloc(sizeof(Unit));
		p->units[counter]=NULL;
		counter++;
	}

	p->side=side;
	p->experience=0;
	p->money=150;
	p->level=1;





	/*p->s=(Special *) malloc(sizeof(Special));
	p->s=InitSpecial();
	p->d=(Defense *) malloc(sizeof(Defense));*/

	return p;

}

void setLevel(Player* p, unsigned int level)
{
	p->level=level;
}
void setMoney(Player* p,  int newMoney)
{
	p->money+=newMoney;
}

void deletePlayer(Player* p)
{

	free(p);
}
void addUnits(Player* p, Unit* u)
{
	p->units[newPosUnit(p)]=u;


}

int emptyUnits(Player* p)
{
	int counter=0;
	while(counter<MAX_UNITS)
	{
		if(p->units[counter]!=NULL)
		{
			return 0;
		}
		counter++;
	}
	return 1;
}

int fullUnits(Player* p)
{
	int counter=0;
	while(counter<MAX_UNITS)
	{
		if(p->units[counter]==NULL)
		{
			return 0;
		}
		counter++;
	}
	return 1;
}

int newPosUnit(Player* p)
{
	int counter=0;
	while(counter<MAX_UNITS)
	{
		if(p->units[counter]==NULL)
			return counter;
		counter++;
	}
}

int checkUnitCollisionSamePlayer(Unit* u1, Unit* u2,  int player)
{
	if(player==1)
	{
		if((u1->x+u1->width) >= u2->x)
		{
			return 1;
		}
	}
	else
	{
		if((u1->x-u1->width) <= u2->x)
		{
			return 1;
		}
	}

	return 0;
}

int checkUnitsTowerCollision(Unit* u, Tower* t)
{
	if(t->player==1)
	{
		if(u->x - u->width <= t->x + t->width)
		{
			return 1;
		}
	}
	else
	{
		if(u->x + u->width >= t->x - t->width)
		{
			return 1;
		}
	}
	return 0;
}



int checkBulletsTowerCollision(Bullet* b, Tower* t)
{

	if(t->player==1)
	{

		if(b->x - b->width <= t->x+t->width)
		{
			return 1;
		}
	}
	else
	{
		if(b->x+b->width >= t->x-t->width)
		{
			return 1;
		}
	}
	return 0;
}

int checkUnitTowerRange(Unit* u, Tower* t)
{

	if(t->player==1)
	{

		if(u->x-u->width-u->range <= t->x+t->width)
		{
			return 1;
		}
	}
	else
	{
		if(u->x+u->width+u->range >= t->x-t->width)
		{
			return 1;
		}
	}
	return 0;
}

void removeUnit(Player* p)
{
	int counter=0;
	while(counter<MAX_UNITS)
	{

		if(counter!=MAX_UNITS-1)
		{
			if(p->units[counter]!=NULL)
			{
				p->units[counter]=p->units[counter+1];

			}
			else
				return;
		}
		else
		{
			p->units[counter]=NULL;
			return;
		}
		counter++;
	}
}
