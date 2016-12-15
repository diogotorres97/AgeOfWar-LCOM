#include "game.h"

Game* InitGame(unsigned int mode) {

	Game* g = (Game*) malloc(sizeof(Game));

	g->p1 = InitPlayer(0);
	g->p2 = InitPlayer(1);

	//Adaptar InitTower para InitTower 0, 1, 2, 3 leves
	g->p1->t=InitTower(0, InY, 200, "tower_left_1", 1);
	g->p2->t=InitTower(1024, InY, 200, "tower_right_1", 2);

	g->GameTerrain = (Terrain*) malloc(sizeof(Terrain));
	g->GameTerrain = InitTerrain(0);

	g->gameBuffer = (char*)malloc(VRAM_SIZE);

	return g;
}


void kbdInterruptHandler(Game* g, unsigned long key)
{

	switch(key)
	{
	case KEY_PRESSED(KEY_1):
																																																									{
		if(!fullUnits(g->p1)) //may create units
		{
			switch(g->p1->level)
			{
			case 1:
				if(g->p1->money >= 15)
				{

					Unit* u = InitUnit(InX_P1, In_Units_Y, 45, 9, 0, "lvl1_1_l", 15, 45, 1);
					addUnits(g->p1, u);
					setMoney(g->p1, -15);


				}
				break;
			case 2:

				break;
			case 3:

				break;

			}
		}
		break;
																																																									}
	case KEY_PRESSED(KEY_2):
																																																									{
		if(!fullUnits(g->p1)) //may create units
		{
			switch(g->p1->level)
			{
			case 1:
				if(g->p1->money >= 25)
				{

					Unit* u = InitUnit(InX_P1, In_Units_Y, 75, 19, 1, "lvl1_2_l", 25, 75, 1);
					addUnits(g->p1, u);
					setMoney(g->p1, -25);

				}
				break;
			case 2:

				break;
			case 3:

				break;

			}
		}
		break;
																																																									}
	case KEY_PRESSED(KEY_J):

																																																							{
		if(!fullUnits(g->p2)) //may create units
		{
			switch(g->p2->level)
			{
			case 1:
				if(g->p2->money >= 15)
				{

					Unit* u = InitUnit(InX_P2, In_Units_Y, 45, 9, 0, "lvl1_1_r", 15, 45, 2);
					addUnits(g->p2, u);
					setMoney(g->p2, -15);

				}
				break;
			case 2:

				break;
			case 3:

				break;

			}
		}
		break;
																																																							}
	case KEY_PRESSED(KEY_K):
																																																								{
		if(!fullUnits(g->p2)) //may create units
		{
			switch(g->p2->level)
			{
			case 1:
				if(g->p2->money >= 25)
				{

					Unit* u = InitUnit(InX_P2, In_Units_Y, 75, 19, 1, "lvl1_2_r", 25, 75, 2);
					addUnits(g->p2, u);
					setMoney(g->p2, -25);

				}
				break;
			case 2:

				break;
			case 3:

				break;

			}
		}
		break;
																																																								}
	default:
		break;
	}
}

void updateGame(Game* g)
{
	int counter=0;
	if(!(emptyUnits(g->p1)) && emptyUnits(g->p2))
	{
		counter=0;
		while(counter<MAX_UNITS)
		{
			if(g->p1->units[counter]!=NULL)
			{

				if((g->p1->units[counter]->type==1) && (checkUnitTowerRange(g->p1->units[counter], g->p2->t)))
				{


					if(emptyBullets(g->p1->units[counter]))
					{
						if(g->timer_cntr%60==0){

							Bullet* b= InitBullet(g->p1->units[counter]->x+g->p1->units[counter]->width, g->p1->units[counter]->y, g->p1->units[counter]->strength, 1, 2, "bullet");
							addBullets(g->p1->units[counter], b);}
					}
					else
					{
						if(!checkBulletsTowerCollision(g->p1->units[counter]->bullets[0], g->p2->t))
						{
							moveBullet(g->p1->units[counter]->bullets[0]);
						}
						else
						{

							towerSetHP(g->p2->t, g->p2->t->hp - g->p1->units[counter]->bullets[0]->strength);
							removeBullet(g->p1->units[counter]);
						}
					}

				}
				if(!checkUnitsTowerCollision(g->p1->units[0], g->p2->t))
				{


					if(counter!=0)
					{
						if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
						{
							MoveUnit(g->p1->units[counter]);
						}
					}
					else
					{
						MoveUnit(g->p1->units[counter]);

					}


				}
				else
				{
					if(g->timer_cntr%30==0){
						towerSetHP(g->p2->t, g->p2->t->hp - g->p1->units[0]->strength);
					}
					if(counter!=0)
					{
						if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
						{
							MoveUnit(g->p1->units[counter]);
						}
					}
				}


			}

			counter++;


		}


	}
	else
	{
		if(emptyUnits(g->p1) && !(emptyUnits(g->p2)))
		{
			counter=0;
			while(counter<MAX_UNITS)
			{
				if(g->p2->units[counter]!=NULL)
				{
					if((g->p2->units[counter]->type==1) && (checkUnitTowerRange(g->p2->units[counter], g->p1->t)))
					{


						if(emptyBullets(g->p2->units[counter]))
						{
							if(g->timer_cntr%60==0){
								Bullet* b= InitBullet(g->p2->units[counter]->x - g->p2->units[counter]->width, g->p2->units[counter]->y, g->p2->units[counter]->strength, 2, 2, "bullet");
								addBullets(g->p2->units[counter], b);
							}
						}
						else
						{
							if(!checkBulletsTowerCollision(g->p2->units[counter]->bullets[0], g->p1->t))
							{

								moveBullet(g->p2->units[counter]->bullets[0]);

							}
							else
							{

								towerSetHP(g->p1->t, g->p1->t->hp - g->p2->units[counter]->bullets[0]->strength);
								removeBullet(g->p2->units[counter]);
							}
						}

					}
					if(!checkUnitsTowerCollision(g->p2->units[0], g->p1->t))
					{


						if(counter!=0)
						{
							if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
							{
								MoveUnit(g->p2->units[counter]);
							}
						}
						else
						{
							MoveUnit(g->p2->units[counter]);

						}
					}
					else
					{
						if(g->timer_cntr%30==0){
							towerSetHP(g->p1->t, g->p1->t->hp - g->p2->units[0]->strength);
						}
						if(counter!=0)
						{
							if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
							{
								MoveUnit(g->p2->units[counter]);
							}
						}
					}
				}

				counter++;


			}


		}
		else
		{
			if(!(emptyUnits(g->p1)) && !(emptyUnits(g->p2)))
			{
				counter=0;
				while(counter<MAX_UNITS)
				{

					if(!(emptyUnits(g->p1)) && !(emptyUnits(g->p2)))
					{
						if(g->p1->units[counter]!=NULL)
						{
							if((g->p1->units[counter]->type==1) && (checkUnitEnemyUnitRange(g->p1->units[counter], g->p2->units[0])) && !checkUnitCollision(g->p1->units[counter], g->p2->units[0]))
							{

								if(emptyBullets(g->p1->units[counter]))
								{

									if(g->timer_cntr%60==0){

										Bullet* b= InitBullet(g->p1->units[counter]->x+g->p1->units[counter]->width, g->p1->units[counter]->y, g->p1->units[counter]->strength, 1, 2, "bullet");
										addBullets(g->p1->units[counter], b);}
								}
								else
								{
									if(!checkBulletsUnitsCollision(g->p1->units[counter]->bullets[0], g->p2->units[0]))
									{

										moveBullet(g->p1->units[counter]->bullets[0]);
									}
									else
									{
										if(g->p2->units[0]->killed)
										{
											setMoney(g->p1, g->p2->units[0]->reward_for_killing);
											removeUnit(g->p2);
										}
										else
										{
											unitSetHP(g->p2->units[0], g->p2->units[0]->hp - g->p1->units[counter]->bullets[0]->strength);
										}
										removeBullet(g->p1->units[counter]);

									}
								}
							}
						}

						if(g->p2->units[counter]!=NULL)
						{
							if((g->p2->units[counter]->type==1) && (checkUnitEnemyUnitRange(g->p2->units[counter], g->p1->units[0])) && !checkUnitCollision(g->p2->units[counter], g->p1->units[0] ))
							{

								if(emptyBullets(g->p2->units[counter]))
								{
									if(g->timer_cntr%60==0){

										Bullet* b= InitBullet(g->p2->units[counter]->x-g->p2->units[counter]->width, g->p2->units[counter]->y, g->p2->units[counter]->strength, 2, 2, "bullet");
										addBullets(g->p2->units[counter], b);}
								}
								else
								{
									if(!checkBulletsUnitsCollision(g->p2->units[counter]->bullets[0], g->p1->units[0]))
									{
										moveBullet(g->p2->units[counter]->bullets[0]);
									}
									else
									{
										if(g->p1->units[0]->killed)
										{
											setMoney(g->p2, g->p1->units[0]->reward_for_killing);
											removeUnit(g->p1);
										}
										else
										{
											unitSetHP(g->p1->units[0], g->p1->units[0]->hp - g->p2->units[counter]->bullets[0]->strength);
										}

										removeBullet(g->p2->units[counter]);

									}
								}
							}
						}
						if(checkUnitCollision(g->p1->units[0], g->p2->units[0]))
						{
							if(g->timer_cntr%30==0){
								battleBetweenUnits(g->p1->units[0], g->p2->units[0]);
								if(g->p1->units[0]->killed)
								{

									setMoney(g->p2, g->p1->units[0]->reward_for_killing);
									removeUnit(g->p1);


								}
								else
								{
									if(g->p2->units[0]->killed)
									{

										setMoney(g->p1, g->p2->units[0]->reward_for_killing);
										removeUnit(g->p2);

									}
								}

							}
						}
						else
						{
							if(counter==0)
							{
								if(checkUnitsTowerCollision(g->p1->units[0], g->p2->t))
								{
									if(g->timer_cntr%30==0){
										towerSetHP(g->p2->t, g->p2->t->hp - g->p1->units[0]->strength);
									}
								}
								else
								{
									MoveUnit(g->p1->units[counter]);
								}

								if(checkUnitsTowerCollision(g->p2->units[0], g->p1->t))
								{
									if(g->timer_cntr%30==0){
										towerSetHP(g->p1->t, g->p1->t->hp - g->p2->units[0]->strength);
									}
								}
								else
								{
									MoveUnit(g->p2->units[counter]);
								}


							}
						}

						if(g->p1->units[counter]!=NULL)
						{
							if(counter!=0)
							{
								if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
								{
									MoveUnit(g->p1->units[counter]);
								}
							}

						}

						if(g->p2->units[counter]!=NULL)
						{
							if(counter!=0)
							{
								if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
								{
									MoveUnit(g->p2->units[counter]);
								}
							}

						}

					}
					else
					{


						if(g->p1->units[counter]!=NULL)
						{
							if(!checkUnitsTowerCollision(g->p1->units[0], g->p2->t))
							{
								if(counter!=0)
								{
									if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
									{
										MoveUnit(g->p1->units[counter]);
									}
								}
								else
								{
									MoveUnit(g->p1->units[counter]);

								}
							}
							else
							{
								if(g->timer_cntr%30==0){
									towerSetHP(g->p2->t, g->p2->t->hp - g->p1->units[0]->strength);
								}
								if(counter!=0)
								{
									if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
									{
										MoveUnit(g->p1->units[counter]);
									}
								}
							}
						}

						if(g->p2->units[counter]!=NULL)
						{
							if(!checkUnitsTowerCollision(g->p2->units[0], g->p1->t))
							{
								if(counter!=0)
								{
									if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
									{
										MoveUnit(g->p2->units[counter]);
									}
								}
								else
								{
									MoveUnit(g->p2->units[counter]);

								}
							}
							else
							{
								if(g-> timer_cntr%30==0){
									towerSetHP(g->p1->t, g->p1->t->hp - g->p2->units[0]->strength);
								}
								if(counter!=0)
								{
									if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
									{
										MoveUnit(g->p2->units[counter]);
									}
								}
							}

						}



					}

					counter++;

				}

			}


		}
	}
}



void drawGame(Game* g)
{

	drawTerrain(g->GameTerrain, g->gameBuffer);




	if(!(emptyUnits(g->p1)))
	{
		int counter=0;
		while(counter<MAX_UNITS)
		{
			if(g->p1->units[counter]!=NULL)
			{
				if(!emptyBullets(g->p1->units[counter]))
					drawBullet(g->p1->units[counter]->bullets[0],g->gameBuffer);
				DrawUnit((g->p1)->units[counter],g->gameBuffer);

			}
			counter++;
		}
	}

	if(!(emptyUnits(g->p2)))
	{
		int counter=0;
		while(counter<MAX_UNITS)
		{
			if(g->p2->units[counter]!=NULL)
			{
				if(!emptyBullets(g->p2->units[counter]))
					drawBullet(g->p2->units[counter]->bullets[0],g->gameBuffer);
				DrawUnit((g->p2)->units[counter],g->gameBuffer);

			}
			counter++;
		}
	}

	drawTower(g->p1->t,g->gameBuffer);

	drawTower(g->p2->t,g->gameBuffer);

}

void deleteGame(Game* g)
{
	deletePlayer(g->p1);
	deletePlayer(g->p2);
	deleteTerrain(g->GameTerrain);
	free(g);
}

int checkUnitCollision(Unit* u1, Unit* u2)
{
	if(u1->player==1)
	{
		if((u1->x + u1->width) >= (u2->x - u2->width))
		{

			return 1;
		}
	}
	else
	{
		if((u1->x - u1->width) <= (u2->x + u2->width))
		{

			return 1;
		}
	}
	return 0;
}

int checkUnitEnemyUnitRange(Unit* u1, Unit* u2)
{
	if(u1->player==1)
	{
		if((u1->x+u1->width+u1->range) >= (u2->x - u2->width))
		{
			return 1;
		}
	}
	else
	{
		if((u1->x-u1->width-u1->range) <= (u2->x + u2->width))
		{
			return 1;
		}
	}

	return 0;
}

void battleBetweenUnits(Unit* u1, Unit* u2)
{

	unitSetHP(u1, u1->hp - (rand() % 3 + u2->strength));
	unitSetHP(u2, u2->hp - (rand() % 3 + u1->strength));

	if((u1->hp<=0) && (u2->hp<=0))
	{

		int unit_victory=rand() % 2;

		if(unit_victory==0)
		{
			unitSetHP(u1, 1);
			u2->killed=1;
		}
		else
		{
			unitSetHP(u2, 1);
			u1->killed=1;
		}
	}
	else
	{
		if(u1->hp<=0)
		{

			u1->killed=1;
		}
		else
		{
			if(u2->hp<=0)
			{

				u2->killed=1;
			}
		}
	}


}

int checkBulletsUnitsCollision(Bullet* b, Unit* u)
{
	if(u->player==1)
	{
		if(b->x-b->width <= u->x+u->width)
		{
			return 1;
		}
	}
	else
	{
		if(b->x+b->width >= u->x-u->width)
		{
			return 1;
		}
	}
	return 0;
}

