#include "game.h"

/******************************************** Game functions *****************************************/

Game* InitGame(unsigned int mode) {

	Game* g = (Game*) malloc(sizeof(Game));

	g->p1 = InitPlayer(0);
	g->p2 = InitPlayer(1);

	g->p1->t=InitTower(0, 500, "tower_lvl1_l", 1);
	g->p2->t=InitTower(1024, 500, "tower_lvl1_r", 2);

	g->p1->no_money=InitNumber(moneyP1_x, money_y, 1,g->p1->money);
	g->p1->no_exp=InitNumber(expP1_x, exp_y, 1, g->p1->experience);
	g->p1->no_exp_to_evolve=InitNumber(expP1_to_evolve_x, exp_to_evolve_y, 1,EXP_MIN_LEVEL2);
	g->p1->no_time_special=InitNumber(no_P1_time_special_x, no_time_special_y, 1,0);
	g->p1->no_tower_life=InitNumber(no_P1_life_tower_x, no_life_tower_y,1, MAX_LIFE_TOWER_1);

	g->p2->no_money=InitNumber(moneyP2_x, money_y, 2,g->p2->money);
	g->p2->no_exp=InitNumber(expP2_x, exp_y, 2,g->p2->experience);
	g->p2->no_exp_to_evolve=InitNumber(expP2_to_evolve_x, exp_to_evolve_y, 2,EXP_MIN_LEVEL2);
	g->p2->no_time_special=InitNumber(no_P2_time_special_x, no_time_special_y, 2,0);
	g->p2->no_tower_life=InitNumber(no_P2_life_tower_x, no_life_tower_y,2, MAX_LIFE_TOWER_1);




	g->p1->s=InitSpecial(325, 100, "special_l", 1);
	g->p2->s=InitSpecial(699, 100, "special_r", 2);

	Slot* sl1 = InitSlot(InX_Defenses_P1, g->p1->t->y, "exp1_1", 1, 1);
	addSlots(g->p1, sl1);

	Slot* sl2 = InitSlot(InX_Defenses_P2, g->p2->t->y, "exp1_1", 2, 1);
	addSlots(g->p2, sl2);


	g->GameTerrain = InitTerrain(1);

	g->menu_l_bmp = loadBitmap(getImagePath("menu1_l"));
	g->menu_r_bmp = loadBitmap(getImagePath("menu1_r"));
	g->special_charge_bmp = loadBitmap(getImagePath("special_charge"));

	g->current_back=1;

	g->timer_anime = 0;
	g->used_special1=0;
	g->used_special2=0;

	g->time_left_special1=30;
	g->time_left_special2=30;

	g->show_special1=0;
	g->show_special2=0;

	g->special_cntr1=0;
	g->special_cntr2=0;

	g->gameBuffer = (char*)malloc(VRAM_SIZE);

	return g;
}


void kbdInterruptHandler(Game* g, unsigned long key)
{

	switch(key)
	{
	//keys for unit creation player1
	case KEY_PRESSED(KEY_1):
																																																																																																																																																																																																																																																															{
		if(!fullUnits(g->p1)) //may create units
		{
			switch(g->p1->level)
			{
			case 1:
				if(g->p1->money >= 15)
				{

					Unit* u = InitUnit(InX_P1, 45, 9, 0, "lvl1_1_l", 15, 45, 1,1);
					addUnits(g->p1, u);

					setMoney(g->p1, -15);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 2:
				if(g->p1->money >= 50)
				{

					Unit* u = InitUnit(InX_P1, 90, 18, 0, "lvl2_1_l", 50, 90, 1,7);
					addUnits(g->p1, u);
					setMoney(g->p1, -50);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 3:
				if(g->p1->money >= 200)
				{

					Unit* u = InitUnit(InX_P1, 180, 36, 0, "lvl3_1_l", 200, 180, 1,13);
					addUnits(g->p1, u);
					setMoney(g->p1, -200);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 4:
				if(g->p1->money >= 1500)
				{

					Unit* u = InitUnit(InX_P1, 540, 108, 0, "lvl4_1_l", 1500, 540, 1,19);
					addUnits(g->p1, u);
					setMoney(g->p1, -1500);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 5:
				if(g->p1->money >= 5000)
				{

					Unit* u = InitUnit(InX_P1, 1620, 324, 0, "lvl5_1_l", 5000, 1620, 1,25);
					addUnits(g->p1, u);
					setMoney(g->p1, -5000);
					setNumber(g->p1->no_money, g->p1->money);

				}
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

					Unit* u = InitUnit(InX_P1, 75, 19, 1, "lvl1_2_l", 25, 75, 1,3);
					addUnits(g->p1, u);
					setMoney(g->p1, -25);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 2:
				if(g->p1->money >= 75)
				{

					Unit* u = InitUnit(InX_P1, 150, 38, 1, "lvl2_2_l", 75, 150, 1,9);
					addUnits(g->p1, u);
					setMoney(g->p1, -75);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 3:
				if(g->p1->money >= 400)
				{

					Unit* u = InitUnit(InX_P1, 300, 76, 1, "lvl3_2_l", 400, 300, 1,15);
					addUnits(g->p1, u);
					setMoney(g->p1, -400);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 4:
				if(g->p1->money >= 2000)
				{

					Unit* u = InitUnit(InX_P1, 900, 228, 1, "lvl4_2_l", 2000, 900, 1,21);
					addUnits(g->p1, u);
					setMoney(g->p1, -2000);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 5:
				if(g->p1->money >= 6000)
				{

					Unit* u = InitUnit(InX_P1, 2700, 684, 1, "lvl5_2_l", 6000, 2700, 1,27);
					addUnits(g->p1, u);
					setMoney(g->p1, -6000);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;

			}
		}
		break;
																																																																																																																																																																																																																																																															}
	case KEY_PRESSED(KEY_3):
																																																																																																																																																																																																																																																																		{
		if(!fullUnits(g->p1)) //may create units
		{
			switch(g->p1->level)
			{
			case 1:
				if(g->p1->money >= 100)
				{

					Unit* u = InitUnit(InX_P1, 150, 44, 0, "lvl1_3_l", 100, 150, 1,5);
					addUnits(g->p1, u);
					setMoney(g->p1, -100);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 2:
				if(g->p1->money >= 500)
				{

					Unit* u = InitUnit(InX_P1, 300, 88, 0, "lvl2_3_l", 500, 300, 1,11);
					addUnits(g->p1, u);
					setMoney(g->p1, -500);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 3:
				if(g->p1->money >= 1000)
				{

					Unit* u = InitUnit(InX_P1, 600, 176, 0, "lvl3_3_l", 1000, 600, 1,17);
					addUnits(g->p1, u);
					setMoney(g->p1, -1000);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 4:
				if(g->p1->money >= 7000)
				{

					Unit* u = InitUnit(InX_P1, 1800, 528, 0, "lvl4_3_l", 7000, 1800, 1,23);
					addUnits(g->p1, u);
					setMoney(g->p1, -7000);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			case 5:
				if(g->p1->money >= 20000)
				{

					Unit* u = InitUnit(InX_P1, 5400, 1584, 0, "lvl5_3_l", 20000, 5400, 1,29);
					addUnits(g->p1, u);
					setMoney(g->p1, -20000);
					setNumber(g->p1->no_money, g->p1->money);

				}
				break;
			}
		}
		break;
																																																																																																																																																																																																																																																																		}
	//keys for defense creation player 1
	case KEY_PRESSED(KEY_Q):
																																																																																																																																																																																																																																																																			{
		if(g->p1->slots_available>0) //may create defenses
		{
			int new_pos;

			switch(g->p1->level)
			{
			case 1:
				if(g->p1->money >= 100)
				{
					new_pos=newPosDefense(g->p1);

					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 10,  "d1_1_l", 100, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -100);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 2:
				if(g->p1->money >= 500)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 20,  "d2_1_l", 500, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -500);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 3:
				if(g->p1->money >= 1500)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 40,  "d3_1_l", 1500, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -1500);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 4:
				if(g->p1->money >= 7000)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 120,  "d4_1_l", 7000, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -7000);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 5:
				if(g->p1->money >= 24000)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 360,  "d5_1_l", 24000, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -24000);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;

			}
		}
		break;
																																																																																																																																																																																																																																																																			}

	case KEY_PRESSED(KEY_W):
																																																																																																																																																																																																																																																																				{
		if(g->p1->slots_available>0) //may create defenses
		{
			int new_pos;
			switch(g->p1->level)
			{
			case 1:
				if(g->p1->money >= 200)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 15,  "d1_2_l", 200, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -200);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 2:
				if(g->p1->money >= 750)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 30,  "d2_2_l", 750, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -750);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 3:
				if(g->p1->money >= 3000)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 60,  "d3_2_l", 3000, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -3000);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 4:
				if(g->p1->money >= 9000)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 180,  "d4_2_l", 9000, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -9000);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 5:
				if(g->p1->money >= 40000)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 540,  "d5_2_l", 40000, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -40000);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;

			}
		}
		break;
																																																																																																																																																																																																																																																																				}




	case KEY_PRESSED(KEY_E):
																																																																																																																																																																																																																																																																					{
		if(g->p1->slots_available>0) //may create defenses
		{
			int new_pos;
			switch(g->p1->level)
			{
			case 1:
				if(g->p1->money >= 500)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 20,  "d1_3_l", 500, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -500);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 2:
				if(g->p1->money >= 1000)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 40,  "d2_3_l", 1000, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -1000);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 3:
				if(g->p1->money >= 6000)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 80,  "d3_3_l", 6000, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -6000);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 4:
				if(g->p1->money >= 14000)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 240,  "d4_3_l", 14000, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -14000);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;
			case 5:
				if(g->p1->money >= 100000)
				{
					new_pos=newPosDefense(g->p1);
					Defense* d = InitDefense(g->p1->slots_defenses[new_pos]->x+10, g->p1->slots_defenses[new_pos]->y+15, 720,  "d5_3_l", 100000, 1, g->p1->defense_current_range);
					addDefenses(g->p1, d);
					setMoney(g->p1, -100000);
					setNumber(g->p1->no_money, g->p1->money);
					g->p1->slots_available--;

				}
				break;

			}
		}
		break;
																																																																																																																																																																																																																																																																					}






	//key for level evolution for player1

	case KEY_PRESSED(KEY_X):
																																																																																																																																																																																																																																																																				{
		int count_slots=0;

		char buf[10];
		switch(g->p1->level)
		{
		case 1:
			if(g->p1->experience>=EXP_MIN_LEVEL2)
			{

				setLevel(g->p1, 2);
				setIncome(g->p1, INCOME_LEVEL2);

				setDefenseRange(g->p1, DEFENSE_RANGE2);
				specialSetStrength(g->p1->s, 200);
				setTower(g->p1->t, "tower_lvl2_l");
				towerSetHP(g->p1->t, g->p1->t->hp+500);

				deleteBitmap(g->menu_l_bmp);
				g->menu_l_bmp = loadBitmap(getImagePath("menu2_l"));

				setNumber(g->p1->no_tower_life, g->p1->t->hp);
				setNumber(g->p1->no_exp_to_evolve, EXP_MIN_LEVEL3);

				if(g->current_back==1)
				{
					deleteTerrain(g->GameTerrain);
					g->GameTerrain = InitTerrain(2);
					g->current_back=2;
				}

				count_slots=newPosSlot(g->p1);

				count_slots--; //the first slot is never changed

				if(count_slots>0)
				{
					while(count_slots>0)
					{
						sprintf(buf, "exp2_%d", count_slots);
						switch(count_slots)
						{
						case 3:
							setSlot(g->p1->slots_defenses[count_slots],buf,53,g->p1->slots_defenses[count_slots-1]->y-65 );
							break;
						case 2:
							setSlot(g->p1->slots_defenses[count_slots],buf,53,g->p1->slots_defenses[count_slots-1]->y-30 );
							break;
						case 1:
							setSlot(g->p1->slots_defenses[count_slots],buf,53,g->p1->slots_defenses[count_slots-1]->y-20 );
							break;
						}


						count_slots--;
					}
				}



			}
			break;
		case 2:
			if(g->p1->experience>=EXP_MIN_LEVEL3)
			{

				setLevel(g->p1, 3);
				setIncome(g->p1, INCOME_LEVEL3);

				setDefenseRange(g->p1, DEFENSE_RANGE3);
				specialSetStrength(g->p1->s, 400);
				setTower(g->p1->t, "tower_lvl3_l");
				towerSetHP(g->p1->t, g->p1->t->hp+1000);

				deleteBitmap(g->menu_l_bmp);
				g->menu_l_bmp = loadBitmap(getImagePath("menu3_l"));

				setNumber(g->p1->no_tower_life, g->p1->t->hp);
				setNumber(g->p1->no_exp_to_evolve,EXP_MIN_LEVEL4);

				if(g->current_back==2)
				{
					deleteTerrain(g->GameTerrain);
					g->GameTerrain = InitTerrain(3);
					g->current_back=3;
				}

				count_slots=newPosSlot(g->p1);

				count_slots--; //the first slot is never changed

				if(count_slots>0)
				{
					while(count_slots>0)
					{
						sprintf(buf, "exp3_%d", count_slots);
						switch(count_slots)
						{
						case 3:
							setSlot(g->p1->slots_defenses[count_slots],buf,53,g->p1->slots_defenses[count_slots-1]->y-90 );
							break;
						case 2:
							setSlot(g->p1->slots_defenses[count_slots],buf,53,g->p1->slots_defenses[count_slots-1]->y-85 );
							break;
						case 1:
							setSlot(g->p1->slots_defenses[count_slots],buf,53,g->p1->slots_defenses[count_slots-1]->y-55 );
							break;
						}


						count_slots--;
					}
				}



			}

			break;
		case 3:
			if(g->p1->experience>=EXP_MIN_LEVEL4)
			{

				setLevel(g->p1, 4);
				setIncome(g->p1, INCOME_LEVEL4);

				setDefenseRange(g->p1, DEFENSE_RANGE4);
				specialSetStrength(g->p1->s, 1200);
				setTower(g->p1->t, "tower_lvl4_l");
				towerSetHP(g->p1->t, g->p1->t->hp+1200);

				deleteBitmap(g->menu_l_bmp);
				g->menu_l_bmp = loadBitmap(getImagePath("menu4_l"));

				setNumber(g->p1->no_tower_life, g->p1->t->hp);
				setNumber(g->p1->no_exp_to_evolve, EXP_MIN_LEVEL5);

				if(g->current_back==3)
				{
					deleteTerrain(g->GameTerrain);
					g->GameTerrain = InitTerrain(4);
					g->current_back=4;
				}


				count_slots=newPosSlot(g->p1);

				count_slots--; //the first slot is never changed

				if(count_slots>0)
				{
					while(count_slots>0)
					{
						sprintf(buf, "exp4_%d_l", count_slots);
						switch(count_slots)
						{
						case 3:
							setSlot(g->p1->slots_defenses[count_slots],buf,57,g->p1->slots_defenses[count_slots-1]->y-40 );
							break;
						case 2:
							setSlot(g->p1->slots_defenses[count_slots],buf,57,g->p1->slots_defenses[count_slots-1]->y-25 );
							break;
						case 1:
							setSlot(g->p1->slots_defenses[count_slots],buf,33,g->p1->slots_defenses[count_slots-1]->y-33 );
							break;
						}


						count_slots--;
					}
				}

			}

			break;
		case 4:
			if(g->p1->experience>=EXP_MIN_LEVEL5)
			{

				setLevel(g->p1, 5);
				setIncome(g->p1, INCOME_LEVEL5);

				setDefenseRange(g->p1, DEFENSE_RANGE5);
				specialSetStrength(g->p1->s, 3600);
				setTower(g->p1->t, "tower_lvl5_l");
				towerSetHP(g->p1->t, g->p1->t->hp+1500);

				setNumber(g->p1->no_tower_life, g->p1->t->hp);

				deleteBitmap(g->menu_l_bmp);
				g->menu_l_bmp = loadBitmap(getImagePath("menu5_l"));

				if(g->current_back==4)
				{
					deleteTerrain(g->GameTerrain);
					g->GameTerrain = InitTerrain(5);
					g->current_back==5;
				}

				count_slots=newPosSlot(g->p1);

				count_slots--; //the first slot is never changed

				if(count_slots>0)
				{
					while(count_slots>0)
					{
						sprintf(buf, "exp5_%d_l", count_slots);
						switch(count_slots)
						{
						case 3:
							setSlot(g->p1->slots_defenses[count_slots],buf,77,g->p1->slots_defenses[count_slots-1]->y-75 );
							break;
						case 2:
							setSlot(g->p1->slots_defenses[count_slots],buf,77,g->p1->slots_defenses[count_slots-1]->y-38 );
							break;
						case 1:
							setSlot(g->p1->slots_defenses[count_slots],buf,75,g->p1->slots_defenses[count_slots-1]->y-18 );
							break;
						}


						count_slots--;
					}
				}

			}
			break;
		default:
			break;

		}

		break;


																																																																																																																																																																																																																																																																				}
	//key1 for special for player 1
	case KEY_PRESSED(KEY_Z):
																																																																																																																																																																																																																																																																					{

		if(g->p1->s->SpecialS==available && !emptyUnits(g->p2))
		{
			g->p1->s->SpecialS=attack;
		}

		break;



																																																																																																																																																																																																																																																																					}
	//key for defense selling for player 1
	case KEY_PRESSED(KEY_R):
																																																																																																																																																																																																																																																																									{
		if(!emptyDefenses(g->p1))
		{

			setMoney(g->p1, (g->p1->defenses[0]->price/2));
			setNumber(g->p1->no_money, g->p1->money);
			g->p1->slots_available++;

			removeDefense(g->p1);



		}


		break;



																																																																																																																																																																																																																																																																									}

	//key for tower expansion for player 1
	case KEY_PRESSED(KEY_T):
																																																																																																																																																																																																																																																																						{

		if(!fullSlots(g->p1)&&(g->p1->money>=1000))
		{

			int new_pos;
			char buf[10];
			Slot* slo;
			switch(g->p1->level)
			{
			case 1:
				new_pos=newPosSlot(g->p1);
				sprintf(buf, "exp1_%d", new_pos);
				if(new_pos==1)
				{
					slo = InitSlot(60, g->p1->slots_defenses[new_pos-1]->y+20,  buf,1, 0);
				}
				else
				{
					slo = InitSlot(60, g->p1->slots_defenses[new_pos-1]->y+5,  buf,1, 0);
				}

				addSlots(g->p1, slo);
				setMoney(g->p1, -1000);
				setNumber(g->p1->no_money, g->p1->money);
				g->p1->slots_available++;



				break;
			case 2:

				new_pos=newPosSlot(g->p1);
				sprintf(buf, "exp2_%d", new_pos);
				if(new_pos==1)
				{
					slo = InitSlot(53, g->p1->slots_defenses[new_pos-1]->y+25,  buf,1, 0);
				}
				else
				{
					slo = InitSlot(53, g->p1->slots_defenses[new_pos-1]->y+15,  buf,1, 0);
				}

				addSlots(g->p1, slo);

				setMoney(g->p1, -1000);
				setNumber(g->p1->no_money, g->p1->money);
				g->p1->slots_available++;

				break;
			case 3:

				new_pos=newPosSlot(g->p1);
				sprintf(buf, "exp3_%d", new_pos);
				if(new_pos==1)
				{
					slo = InitSlot(53, g->p1->slots_defenses[new_pos-1]->y+15,  buf,1, 0);
				}
				else
				{
					slo = InitSlot(53, g->p1->slots_defenses[new_pos-1]->y+20,  buf,1, 0);
				}
				addSlots(g->p1, slo);
				setMoney(g->p1, -1000);
				setNumber(g->p1->no_money, g->p1->money);
				g->p1->slots_available++;
				break;
			case 4:

				new_pos=newPosSlot(g->p1);
				sprintf(buf, "exp4_%d_l", new_pos);
				if(new_pos==1)
				{
					slo = InitSlot(33, g->p1->slots_defenses[new_pos-1]->y+25,  buf,1, 0);
				}
				else
				{
					slo = InitSlot(57, g->p1->slots_defenses[new_pos-1]->y+5,  buf,1, 0);
				}
				addSlots(g->p1, slo);
				setMoney(g->p1, -1000);
				setNumber(g->p1->no_money, g->p1->money);
				g->p1->slots_available++;
				break;
			case 5:

				new_pos=newPosSlot(g->p1);
				sprintf(buf, "exp5_%d_l", new_pos);
				if(new_pos==1)
				{
					slo = InitSlot(75, g->p1->slots_defenses[new_pos-1]->y+33,  buf,1, 0);
				}
				else
				{
					slo = InitSlot(77, g->p1->slots_defenses[new_pos-1]->y+5,  buf,1, 0);
				}
				addSlots(g->p1, slo);
				setMoney(g->p1, -1000);
				setNumber(g->p1->no_money, g->p1->money);
				g->p1->slots_available++;
				break;
			}


		}




		break;



																																																																																																																																																																																																																																																																						}




	//keys for unit creation for player 2

	case KEY_PRESSED(KEY_J):

																																																																																																																																																																																																																																																														{
		if(!fullUnits(g->p2)) //may create units
		{
			switch(g->p2->level)
			{
			case 1:
				if(g->p2->money >= 15)
				{

					Unit* u = InitUnit(InX_P2, 45, 9, 0, "lvl1_1_r", 15, 45, 2,2);
					addUnits(g->p2, u);
					setMoney(g->p2, -15);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 2:
				if(g->p2->money >= 50)
				{

					Unit* u = InitUnit(InX_P2, 90, 18, 0, "lvl2_1_r", 50, 90, 2,8);
					addUnits(g->p2, u);
					setMoney(g->p2, -50);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 3:
				if(g->p2->money >= 200)
				{

					Unit* u = InitUnit(InX_P2, 180, 36, 0, "lvl3_1_r", 200, 180, 2,14);
					addUnits(g->p2, u);
					setMoney(g->p2, -200);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 4:
				if(g->p2->money >= 1500)
				{

					Unit* u = InitUnit(InX_P2, 540, 108, 0, "lvl4_1_r", 1500, 540, 2,20);
					addUnits(g->p2, u);
					setMoney(g->p2, -1500);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 5:
				if(g->p2->money >= 5000)
				{

					Unit* u = InitUnit(InX_P2, 1620, 324, 0, "lvl5_1_r", 5000, 1620, 2,26);
					addUnits(g->p2, u);
					setMoney(g->p2, -5000);
					setNumber(g->p2->no_money, g->p2->money);

				}
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

					Unit* u = InitUnit(InX_P2, 75, 19, 1, "lvl1_2_r", 25, 75, 2,4);
					addUnits(g->p2, u);
					setMoney(g->p2, -25);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 2:
				if(g->p2->money >= 75)
				{

					Unit* u = InitUnit(InX_P2, 150, 38, 1, "lvl2_2_r", 75, 150, 2,10);
					addUnits(g->p2, u);
					setMoney(g->p2, -75);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 3:
				if(g->p2->money >= 400)
				{

					Unit* u = InitUnit(InX_P2, 300, 76, 1, "lvl3_2_r", 400, 300, 2,16);
					addUnits(g->p2, u);
					setMoney(g->p2, -400);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 4:
				if(g->p2->money >= 2000)
				{

					Unit* u = InitUnit(InX_P2, 900, 228, 1, "lvl4_2_r", 2000, 900, 2,22);
					addUnits(g->p2, u);
					setMoney(g->p2, -2000);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 5:
				if(g->p2->money >= 6000)
				{

					Unit* u = InitUnit(InX_P2, 2700, 684, 1, "lvl5_2_r", 6000, 2700, 2,28);
					addUnits(g->p2, u);
					setMoney(g->p2, -6000);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;

			}
		}
		break;
																																																																																																																																																																																																																																																																				}

	case KEY_PRESSED(KEY_L):
																																																																																																																																																																																																																																																																			{
		if(!fullUnits(g->p2)) //may create units
		{
			switch(g->p2->level)
			{
			case 1:
				if(g->p2->money >= 100)
				{

					Unit* u = InitUnit(InX_P2, 150, 44, 0, "lvl1_3_r", 100, 150, 2,6);
					addUnits(g->p2, u);
					setMoney(g->p2, -100);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 2:
				if(g->p2->money >= 500)
				{

					Unit* u = InitUnit(InX_P2, 300, 88, 0, "lvl2_3_r", 500, 300, 2,12);
					addUnits(g->p2, u);
					setMoney(g->p2, -500);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 3:
				if(g->p2->money >= 1000)
				{

					Unit* u = InitUnit(InX_P2, 600, 176, 0, "lvl3_3_r", 1000, 600, 2,18);
					addUnits(g->p2, u);
					setMoney(g->p2, -1000);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 4:
				if(g->p2->money >= 7000)
				{

					Unit* u = InitUnit(InX_P2, 1800, 528, 0, "lvl4_3_r", 7000, 1800, 2,24);
					addUnits(g->p2, u);
					setMoney(g->p2, -7000);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;
			case 5:
				if(g->p2->money >= 20000)
				{

					Unit* u = InitUnit(InX_P2, 5400, 1584, 0, "lvl5_3_r", 20000, 5400, 2,30);
					addUnits(g->p2, u);
					setMoney(g->p2, -20000);
					setNumber(g->p2->no_money, g->p2->money);

				}
				break;

			}
		}
		break;

																																																																																																																																																																																																																																																																			}
	//keys for defense creation player 2
	case KEY_PRESSED(KEY_U):
																																																																																																																																																																																																																																																																				{
		if(g->p2->slots_available>0) //may create defenses
		{
			int new_pos;
			switch(g->p2->level)
			{
			case 1:
				if(g->p2->money >= 100)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 10,  "d1_1_r", 100, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -100);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 2:
				if(g->p2->money >= 500)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 20,  "d2_1_r", 500, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -500);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 3:
				if(g->p2->money >= 1500)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 40,  "d3_1_r", 1500, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -1500);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 4:
				if(g->p2->money >= 7000)
				{

					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 120,  "d4_1_r", 7000, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -7000);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 5:
				if(g->p2->money >= 24000)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 360,  "d5_1_r", 24000, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -24000);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;

			}
		}
		break;
																																																																																																																																																																																																																																																																				}

	case KEY_PRESSED(KEY_I):
																																																																																																																																																																																																																																																																					{
		if(g->p2->slots_available>0) //may create defenses
		{
			int new_pos;
			switch(g->p2->level)
			{
			case 1:
				if(g->p2->money >= 200)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 15,  "d1_2_r", 200, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -200);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 2:
				if(g->p2->money >= 750)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 30,  "d2_2_r", 750, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -750);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 3:
				if(g->p2->money >= 3000)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 60,  "d3_2_r", 3000, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -3000);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 4:
				if(g->p2->money >= 9000)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 180,  "d4_2_r", 9000, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -9000);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 5:
				if(g->p2->money >= 40000)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 540,  "d5_2_r", 40000, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -40000);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;

			}
		}
		break;
																																																																																																																																																																																																																																																																					}




	case KEY_PRESSED(KEY_O):
																																																																																																																																																																																																																																																																						{
		if(g->p2->slots_available>0) //may create defenses
		{
			int new_pos;
			switch(g->p2->level)
			{
			case 1:
				if(g->p2->money >= 500)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 20,  "d1_3_r", 500, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -500);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 2:
				if(g->p2->money >= 1000)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 40,  "d2_3_r", 1000, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -1000);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 3:
				if(g->p2->money >= 6000)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 80,  "d3_3_r", 6000, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -6000);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 4:
				if(g->p2->money >= 14000)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 240,  "d4_3_r", 14000, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -14000);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;
			case 5:
				if(g->p2->money >= 100000)
				{
					new_pos=newPosDefense(g->p2);
					Defense* d = InitDefense(g->p2->slots_defenses[new_pos]->x-10, g->p2->slots_defenses[new_pos]->y+15, 720,  "d5_3_r", 100000, 2, g->p2->defense_current_range);
					addDefenses(g->p2, d);
					setMoney(g->p2, -100000);
					setNumber(g->p2->no_money, g->p2->money);
					g->p2->slots_available--;

				}
				break;

			}
		}
		break;
																																																																																																																																																																																																																																																																						}






	//key for level evolution for player2

	case KEY_PRESSED(KEY_M):
																																																																																																																																																																																																																																																																					{
		int count_slots=0;
		char buf[10];
		switch(g->p2->level)
		{
		case 1:
			if(g->p2->experience>=EXP_MIN_LEVEL2)
			{

				setLevel(g->p2, 2);
				setIncome(g->p2, INCOME_LEVEL2);

				setDefenseRange(g->p2, DEFENSE_RANGE2);
				specialSetStrength(g->p2->s, 200);
				setTower(g->p2->t, "tower_lvl2_r");
				towerSetHP(g->p2->t, g->p2->t->hp+500);

				deleteBitmap(g->menu_r_bmp);
				g->menu_r_bmp = loadBitmap(getImagePath("menu2_r"));

				setNumber(g->p2->no_tower_life, g->p2->t->hp);
				setNumber(g->p2->no_exp_to_evolve, EXP_MIN_LEVEL3);

				if(g->current_back==1)
				{
					deleteTerrain(g->GameTerrain);
					g->GameTerrain = InitTerrain(2);
					g->current_back=2;
				}


				count_slots=newPosSlot(g->p2);

				count_slots--; //the first slot is never changed

				if(count_slots>0)
				{
					while(count_slots>0)
					{
						sprintf(buf, "exp2_%d", count_slots);
						switch(count_slots)
						{
						case 3:
							setSlot(g->p2->slots_defenses[count_slots],buf,971,g->p2->slots_defenses[count_slots-1]->y-65 );
							break;
						case 2:
							setSlot(g->p2->slots_defenses[count_slots],buf,971,g->p2->slots_defenses[count_slots-1]->y-30 );
							break;
						case 1:
							setSlot(g->p2->slots_defenses[count_slots],buf,971,g->p2->slots_defenses[count_slots-1]->y-20 );
							break;
						}


						count_slots--;
					}
				}

			}
			break;
		case 2:
			if(g->p2->experience>=EXP_MIN_LEVEL3)
			{

				setLevel(g->p2, 3);
				setIncome(g->p2, INCOME_LEVEL3);

				setDefenseRange(g->p2, DEFENSE_RANGE3);
				specialSetStrength(g->p2->s, 400);
				setTower(g->p2->t, "tower_lvl3_r");
				towerSetHP(g->p2->t, g->p2->t->hp+1000);

				deleteBitmap(g->menu_r_bmp);
				g->menu_r_bmp = loadBitmap(getImagePath("menu3_r"));

				setNumber(g->p2->no_tower_life, g->p2->t->hp);
				setNumber(g->p2->no_exp_to_evolve, EXP_MIN_LEVEL4);

				if(g->current_back==2)
				{
					deleteTerrain(g->GameTerrain);
					g->GameTerrain = InitTerrain(3);
					g->current_back=3;
				}

				count_slots=newPosSlot(g->p2);

				count_slots--; //the first slot is never changed

				if(count_slots>0)
				{
					while(count_slots>0)
					{
						sprintf(buf, "exp3_%d", count_slots);
						switch(count_slots)
						{
						case 3:
							setSlot(g->p2->slots_defenses[count_slots],buf,971,g->p2->slots_defenses[count_slots-1]->y-90 );
							break;
						case 2:
							setSlot(g->p2->slots_defenses[count_slots],buf,971,g->p2->slots_defenses[count_slots-1]->y-85 );
							break;
						case 1:
							setSlot(g->p2->slots_defenses[count_slots],buf,971,g->p2->slots_defenses[count_slots-1]->y-55 );
							break;
						}


						count_slots--;
					}
				}

			}

			break;
		case 3:
			if(g->p2->experience>=EXP_MIN_LEVEL4)
			{

				setLevel(g->p2, 4);
				setIncome(g->p2, INCOME_LEVEL4);

				setDefenseRange(g->p2, DEFENSE_RANGE4);
				specialSetStrength(g->p2->s, 1200);
				setTower(g->p2->t, "tower_lvl4_r");
				towerSetHP(g->p2->t, g->p2->t->hp+1200);

				deleteBitmap(g->menu_r_bmp);
				g->menu_r_bmp = loadBitmap(getImagePath("menu4_r"));

				setNumber(g->p2->no_tower_life, g->p2->t->hp);
				setNumber(g->p2->no_exp_to_evolve, EXP_MIN_LEVEL5);

				if(g->current_back==3)
				{
					deleteTerrain(g->GameTerrain);
					g->GameTerrain = InitTerrain(4);
					g->current_back=4;
				}

				count_slots=newPosSlot(g->p2);

				count_slots--; //the first slot is never changed

				if(count_slots>0)
				{
					while(count_slots>0)
					{
						sprintf(buf, "exp4_%d_r", count_slots);
						switch(count_slots)
						{
						case 3:
							setSlot(g->p2->slots_defenses[count_slots],buf,947,g->p2->slots_defenses[count_slots-1]->y-40 );
							break;
						case 2:
							setSlot(g->p2->slots_defenses[count_slots],buf,947,g->p2->slots_defenses[count_slots-1]->y-25 );
							break;
						case 1:
							setSlot(g->p2->slots_defenses[count_slots],buf,971,g->p2->slots_defenses[count_slots-1]->y-33 );
							break;
						}


						count_slots--;
					}
				}

			}

			break;
		case 4:
			if(g->p2->experience>=EXP_MIN_LEVEL5)
			{

				setLevel(g->p2, 5);
				setIncome(g->p2, INCOME_LEVEL5);

				setDefenseRange(g->p2, DEFENSE_RANGE5);
				specialSetStrength(g->p2->s, 3600);
				setTower(g->p2->t, "tower_lvl5_r");
				towerSetHP(g->p2->t, g->p2->t->hp+1500);

				setNumber(g->p2->no_tower_life, g->p2->t->hp);

				deleteBitmap(g->menu_r_bmp);
				g->menu_r_bmp = loadBitmap(getImagePath("menu5_r"));

				if(g->current_back==4)
				{
					deleteTerrain(g->GameTerrain);
					g->GameTerrain = InitTerrain(5);
					g->current_back=5;
				}

				count_slots=newPosSlot(g->p2);

				count_slots--; //the first slot is never changed

				if(count_slots>0)
				{
					while(count_slots>0)
					{
						sprintf(buf, "exp5_%d_r", count_slots);
						switch(count_slots)
						{
						case 3:
							setSlot(g->p2->slots_defenses[count_slots],buf,947,g->p2->slots_defenses[count_slots-1]->y-75 );
							break;
						case 2:
							setSlot(g->p2->slots_defenses[count_slots],buf,947,g->p2->slots_defenses[count_slots-1]->y-38 );
							break;
						case 1:
							setSlot(g->p2->slots_defenses[count_slots],buf,949,g->p2->slots_defenses[count_slots-1]->y-18 );
							break;
						}


						count_slots--;
					}
				}

			}
			break;
		default:
			break;

		}

		break;
																																																																																																																																																																																																																																																																					}
	//keys for special for player 2
	case KEY_PRESSED(KEY_N):
																																																																																																																																																																																											{

		if(g->p2->s->SpecialS==available && !emptyUnits(g->p1))
		{
			g->p2->s->SpecialS=attack;
		}

		break;

																																																																																																																																																																																											}
	//key for defense selling for player 2
	case KEY_PRESSED(KEY_P):
																																																																																																																																																																																																																																																																										{


		if(!emptyDefenses(g->p2))
		{

			setMoney(g->p2, (g->p2->defenses[0]->price/2));
			setNumber(g->p2->no_money, g->p2->money);
			g->p2->slots_available++;

			removeDefense(g->p2);



		}

		break;



																																																																																																																																																																																																																																																																										}

	//key for tower expansion for player 2
	case KEY_PRESSED(KEY_PLUS):
																																																																																																																																																																																																																																																																							{
		if(!fullSlots(g->p2)&&(g->p2->money>=1000))
		{

			int new_pos;
			char buf[10];
			Slot* slo;
			switch(g->p2->level)
			{
			case 1:
				new_pos=newPosSlot(g->p2);

				sprintf(buf, "exp1_%d", new_pos);
				if(new_pos==1)
				{
					slo = InitSlot(964, g->p2->slots_defenses[new_pos-1]->y+20,  buf,2, 0);
				}
				else
				{
					slo = InitSlot(964, g->p2->slots_defenses[new_pos-1]->y+5,  buf,2, 0);
				}
				addSlots(g->p2, slo);
				setMoney(g->p2, -1000);
				setNumber(g->p2->no_money, g->p2->money);
				g->p2->slots_available++;



				break;
			case 2:

				new_pos=newPosSlot(g->p2);
				sprintf(buf, "exp2_%d", new_pos);
				if(new_pos==1)
				{
					slo = InitSlot(971, g->p2->slots_defenses[new_pos-1]->y+25,  buf,2, 0);
				}
				else
				{
					slo = InitSlot(971, g->p2->slots_defenses[new_pos-1]->y+15,  buf,2, 0);
				}

				addSlots(g->p2, slo);
				setMoney(g->p2, -1000);
				setNumber(g->p2->no_money, g->p2->money);
				g->p2->slots_available++;

				break;
			case 3:

				new_pos=newPosSlot(g->p2);
				sprintf(buf, "exp3_%d", new_pos);
				if(new_pos==1)
				{
					slo = InitSlot(971, g->p2->slots_defenses[new_pos-1]->y+15,  buf,2, 0);
				}
				else
				{
					slo = InitSlot(971, g->p2->slots_defenses[new_pos-1]->y+20,  buf,2, 0);
				}

				addSlots(g->p2, slo);
				setMoney(g->p2, -1000);
				setNumber(g->p2->no_money, g->p2->money);
				g->p2->slots_available++;
				break;
			case 4:

				new_pos=newPosSlot(g->p2);
				sprintf(buf, "exp4_%d_r", new_pos);
				if(new_pos==1)
				{
					slo = InitSlot(991, g->p2->slots_defenses[new_pos-1]->y+25,  buf,2, 0);
				}
				else
				{
					slo = InitSlot(967, g->p2->slots_defenses[new_pos-1]->y+5,  buf,2, 0);
				}

				addSlots(g->p2, slo);
				setMoney(g->p2, -1000);
				setNumber(g->p2->no_money, g->p2->money);
				g->p2->slots_available++;
				break;
			case 5:

				new_pos=newPosSlot(g->p2);
				sprintf(buf, "exp5_%d_r", new_pos);
				if(new_pos==1)
				{
					slo = InitSlot(949, g->p2->slots_defenses[new_pos-1]->y+33,  buf,2, 0);
				}
				else
				{
					slo = InitSlot(947, g->p2->slots_defenses[new_pos-1]->y+5,  buf,2, 0);
				}

				addSlots(g->p2, slo);
				setMoney(g->p2, -1000);
				setNumber(g->p2->no_money, g->p2->money);
				g->p2->slots_available++;
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
	int aux_cnt=0;
	int defense_counter=0;
	int number_defenses_p1=countDefenses(g->p1);
	int number_defenses_p2=countDefenses(g->p2);

	if(g->p1->s->SpecialS==charging)
	{
		g->special_cntr1++;

		if(g->special_cntr1%TIMER_DEFAULT_FREQ==0)
		{
			setNumber(g->p1->no_time_special, g->time_left_special1);
			g->time_left_special1--;
		}
		if( g->special_cntr1%(TIMER_DEFAULT_FREQ*TIME_SPECIAL_RECHARGE)==0)
		{

			g->p1->s->SpecialS=available;
			g->time_left_special1=30;
			g->special_cntr1=0;

		}

	}
	if(g->p2->s->SpecialS==charging)
	{
		g->special_cntr2++;
		if(g->special_cntr2%TIMER_DEFAULT_FREQ==0 )
		{

			setNumber(g->p2->no_time_special, g->time_left_special2);
			g->time_left_special2--;
		}
		if(g->special_cntr2%(TIMER_DEFAULT_FREQ*TIME_SPECIAL_RECHARGE)==0)
		{

			g->p2->s->SpecialS=available;
			g->time_left_special2=30;
			g->special_cntr2=0;

		}
	}







	if(g->timer_cntr%60==0){

		//increses money of each player every second, by its income per level atribute
		setMoney(g->p1, g->p1->income_per_level);
		setNumber(g->p1->no_money, g->p1->money);
		setMoney(g->p2, g->p2->income_per_level);
		setNumber(g->p2->no_money, g->p2->money);
	}

	if(!(emptyUnits(g->p1)) && emptyUnits(g->p2))
	{

		if((g->p1->defenses[0]!=NULL) &&(fullBulletsDefenses(g->p1->defenses[0])))
		{
			removeBulletDefense(g->p1->defenses[0]);
		}

		if(g->used_special2)
		{

			aux_cnt=countUnits(g->p1);


			int c=0;
			while(aux_cnt>0)
			{
				Unit* u=g->p1->units[0];
				if(g->p1->units[c]->UnitS==dying)
				{

					setMoney(g->p2, g->p1->units[c]->reward_for_killing);
					setNumber(g->p2->no_money, g->p2->money);
					setExperience(g->p2, g->p1->units[c]->exp_for_killing);
					setNumber(g->p2->no_exp, g->p2->experience);
					removeUnit(g->p1);


				}
				else
				{
					removeUnit(g->p1);
					addUnits(g->p1, u);

				}
				aux_cnt--;
			}

		}





		while(counter<MAX_UNITS)
		{

			if(g->p1->units[counter]!=NULL)
			{
				if(g->p1->units[counter]->UnitS==dying)
				{
					setMoney(g->p2, g->p1->units[0]->reward_for_killing);
					setNumber(g->p2->no_money, g->p2->money);
					setExperience(g->p2, g->p1->units[0]->exp_for_killing);
					setNumber(g->p2->no_exp, g->p2->experience);
					removeUnit(g->p1);
					counter++;
					continue;
				}
				if((g->p1->units[counter]->type==1))
				{
					if(checkUnitTowerRange(g->p1->units[counter], g->p2->t))
					{
						g->p1->units[counter]->UnitS=shooting;


						if(emptyBulletsUnits(g->p1->units[counter]))
						{
							if(g->timer_cntr%60==0){

								Bullet* b= InitBullet(g->p1->units[counter]->x+g->p1->units[counter]->width, g->p1->units[counter]->y+18, g->p1->units[counter]->strength, 1, 2, "bullet");
								addBulletsUnits(g->p1->units[counter], b);}
						}
						else
						{
							if(!checkBulletsTowerCollision(g->p1->units[counter]->bullets[0], g->p2->t))
							{
								moveBullet(g->p1->units[counter]->bullets[0],0,0);
							}
							else
							{

								towerSetHP(g->p2->t, g->p2->t->hp - g->p1->units[counter]->bullets[0]->strength);
								if(g->p2->t->hp>=0)
								{
									setNumber(g->p2->no_tower_life, g->p2->t->hp);
								}

								removeBulletUnit(g->p1->units[counter]);
							}
						}
					}
					else
					{
						g->p1->units[counter]->UnitS=standing;
						if(fullBulletsUnits(g->p1->units[counter]))
						{
							removeBulletUnit(g->p1->units[counter]);
						}
					}


				}

				if(number_defenses_p2>0 && (g->p1->units[0]!=NULL))
				{

					while(defense_counter<number_defenses_p2)
					{
						if(checkUnitsDefenseRange(g->p1->units[0], g->p2->defenses[defense_counter]))
						{

							if(emptyBulletsDefenses(g->p2->defenses[defense_counter]))
							{

								if(g->timer_cntr%60==0){

									Bullet* b= InitBullet(g->p2->defenses[defense_counter]->x-g->p2->defenses[defense_counter]->width, g->p2->defenses[defense_counter]->y+(g->p2->defenses[defense_counter]->height/2), g->p2->defenses[defense_counter]->strength, 2, 1, "bullet");
									addBulletsDefense(g->p2->defenses[defense_counter], b);}
							}
							else
							{
								if(!checkBulletsUnitsCollision(g->p2->defenses[defense_counter]->bullets[0], g->p1->units[0]))
								{


									moveBullet(g->p2->defenses[defense_counter]->bullets[0],g->p2->defenses[defense_counter]->bullets[0]->x-g->p1->units[0]->x+g->p1->units[0]->width,InY-g->p2->defenses[defense_counter]->bullets[0]->y);
								}
								else
								{

									if(g->p1->units[0]->UnitS==dying)
									{

										setMoney(g->p2, g->p1->units[0]->reward_for_killing);
										setNumber(g->p2->no_money, g->p2->money);
										setExperience(g->p2, g->p1->units[0]->exp_for_killing);
										setNumber(g->p2->no_exp, g->p2->experience);
										removeUnit(g->p1);

										break;

									}
									else
									{


										unitSetHP(g->p1->units[0], g->p1->units[0]->hp - g->p2->defenses[defense_counter]->bullets[0]->strength);

										if(g->p1->units[0]->hp<=0)
										{

											g->p1->units[0]->UnitS=dying;
										}



									}

									removeBulletDefense(g->p2->defenses[defense_counter]);
								}
							}
						}
						else
						{
							if(fullBulletsDefenses(g->p2->defenses[defense_counter]))
							{
								removeBulletDefense(g->p2->defenses[defense_counter]);
							}
						}


						defense_counter++;
					}
					defense_counter=0;
					if(emptyUnits(g->p1))
					{
						while(defense_counter<number_defenses_p2)
						{
							if(fullBulletsDefenses(g->p2->defenses[defense_counter]))
							{
								removeBulletDefense(g->p2->defenses[defense_counter]);
							}
							defense_counter++;
						}
					}


				}
				if(g->p2->s->SpecialS==attack)
				{

					if(g->p1->units[counter]!=NULL)
					{


						unitSetHP(g->p1->units[counter], g->p1->units[counter]->hp - g->p2->s->strength);
						if(g->p1->units[counter]->hp<=0)
						{

							g->p1->units[counter]->UnitS=dying;
						}

					}


				}





				if((g->p1->units[0]!=NULL) && (g->p1->units[counter]!=NULL) && (g->p1->units[counter]->UnitS!=dying))
				{

					if(!checkUnitsTowerCollision(g->p1->units[0], g->p2->t))
					{


						if(counter!=0)
						{
							if(g->p1->units[counter]->type==1)
							{
								if(g->p1->units[counter]->UnitS!=shooting)
								{
									if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
									{
										g->p1->units[counter]->UnitS=moving;
										MoveUnit(g->p1->units[counter]);
									}
									else
									{
										g->p1->units[counter]->UnitS=standing;
									}
								}
							}
							else
							{
								if(g->p1->units[counter-1]->type==1 && (g->p1->units[counter-1]->UnitS==shooting || g->p1->units[counter-1]->UnitS==standing))
								{
									if(checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
									{
										g->p1->units[counter]->UnitS=moving;
										MoveUnit(g->p1->units[counter]);
										Unit* u_aux=g->p1->units[counter];
										g->p1->units[counter]=g->p1->units[counter-1];
										g->p1->units[counter-1]=u_aux;
									}
									else
									{
										g->p1->units[counter]->UnitS=moving;
										MoveUnit(g->p1->units[counter]);
									}
								}
								else
								{
									if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
									{
										g->p1->units[counter]->UnitS=moving;
										MoveUnit(g->p1->units[counter]);
									}
									else
									{
										g->p1->units[counter]->UnitS=standing;
									}
								}
							}

						}
						else
						{
							if(g->p1->units[counter]->UnitS!=shooting)
							{
								g->p1->units[counter]->UnitS=moving;
								MoveUnit(g->p1->units[counter]);
							}


						}


					}
					else
					{

						if(counter!=0)
						{
							if(g->p1->units[counter]->type==1)
							{
								if(g->p1->units[counter]->UnitS!=shooting)
								{
									if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
									{
										g->p1->units[counter]->UnitS=moving;
										MoveUnit(g->p1->units[counter]);
									}
									else
									{
										g->p1->units[counter]->UnitS=standing;
									}
								}
							}
							else
							{
								if(g->p1->units[counter-1]->type==1 && (g->p1->units[counter-1]->UnitS==shooting|| g->p1->units[counter-1]->UnitS==standing))
								{
									if(checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
									{
										g->p1->units[counter]->UnitS=moving;
										MoveUnit(g->p1->units[counter]);
										Unit* u_aux=g->p1->units[counter];
										g->p1->units[counter]=g->p1->units[counter-1];
										g->p1->units[counter-1]=u_aux;
									}
									else
									{
										g->p1->units[counter]->UnitS=moving;
										MoveUnit(g->p1->units[counter]);
									}
								}
								else
								{
									if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
									{
										g->p1->units[counter]->UnitS=moving;
										MoveUnit(g->p1->units[counter]);
									}
									else
									{
										g->p1->units[counter]->UnitS=standing;
									}
								}
							}
						}
						else
						{

							g->p1->units[0]->UnitS=attacking;

							if(g->timer_cntr%60==0){

								towerSetHP(g->p2->t, g->p2->t->hp - g->p1->units[0]->strength);
								if(g->p2->t->hp>=0)
								{
									setNumber(g->p2->no_tower_life, g->p2->t->hp);
								}


							}


						}

					}

				}




			}

			counter++;


		}
		if(g->p2->s->SpecialS==attack)
		{
			g->p2->s->SpecialS=charging;
			g->used_special2=1;
		}
		else
		{
			g->used_special2=0;
		}


	}
	else
	{

		if(emptyUnits(g->p1) && !(emptyUnits(g->p2)))
		{
			if(g->used_special1)
			{

				aux_cnt=countUnits(g->p2);
				int c=0;
				while(aux_cnt>0)
				{
					Unit* u=g->p2->units[0];
					if(g->p2->units[c]->UnitS==dying)
					{

						setMoney(g->p1, g->p2->units[c]->reward_for_killing);
						setNumber(g->p1->no_money, g->p1->money);
						setExperience(g->p1, g->p2->units[c]->exp_for_killing);
						setNumber(g->p1->no_exp, g->p1->experience);
						removeUnit(g->p2);

					}
					else
					{

						removeUnit(g->p2);
						addUnits(g->p2, u);
					}
					aux_cnt--;
				}
			}
			counter=0;
			if((g->p2->defenses[0]!=NULL) &&(fullBulletsDefenses(g->p2->defenses[0])))
			{
				removeBulletDefense(g->p2->defenses[0]);
			}
			while(counter<MAX_UNITS)
			{
				if(g->p2->units[counter]!=NULL)
				{
					if(g->p2->units[counter]->UnitS==dying)
					{
						setMoney(g->p1, g->p2->units[0]->reward_for_killing);
						setNumber(g->p1->no_money, g->p1->money);
						setExperience(g->p1, g->p2->units[0]->exp_for_killing);
						setNumber(g->p1->no_exp, g->p1->experience);
						removeUnit(g->p2);
						counter++;
						continue;
					}
					if((g->p2->units[counter]->type==1))
					{
						if(checkUnitTowerRange(g->p2->units[counter], g->p1->t))
						{
							g->p2->units[counter]->UnitS=shooting;
							if(emptyBulletsUnits(g->p2->units[counter]))
							{
								if(g->timer_cntr%60==0){
									Bullet* b= InitBullet(g->p2->units[counter]->x - g->p2->units[counter]->width, g->p2->units[counter]->y+18, g->p2->units[counter]->strength, 2, 2, "bullet");
									addBulletsUnits(g->p2->units[counter], b);
								}
							}
							else
							{
								if(!checkBulletsTowerCollision(g->p2->units[counter]->bullets[0], g->p1->t))
								{

									moveBullet(g->p2->units[counter]->bullets[0],0,0);

								}
								else
								{
									towerSetHP(g->p1->t, g->p1->t->hp - g->p2->units[counter]->bullets[0]->strength);
									if(g->p1->t->hp>=0)
									{
										setNumber(g->p1->no_tower_life, g->p1->t->hp);
									}

									removeBulletUnit(g->p2->units[counter]);
								}
							}

						}
						else
						{
							g->p2->units[counter]->UnitS=standing;
							if(!emptyBulletsUnits(g->p2->units[counter]))
							{
								removeBulletUnit(g->p2->units[counter]);
							}
						}
					}

					if(number_defenses_p1>0 && (g->p2->units[0]!=NULL))
					{
						while(defense_counter<number_defenses_p1)
						{
							if(checkUnitsDefenseRange(g->p2->units[0], g->p1->defenses[defense_counter]))
							{

								if(emptyBulletsDefenses(g->p1->defenses[defense_counter]))
								{

									if(g->timer_cntr%60==0){

										Bullet* b= InitBullet(g->p1->defenses[defense_counter]->x+g->p1->defenses[defense_counter]->width, g->p1->defenses[defense_counter]->y+(g->p1->defenses[defense_counter]->height/2), g->p1->defenses[defense_counter]->strength, 1, 1, "bullet");
										addBulletsDefense(g->p1->defenses[defense_counter], b);}
								}
								else
								{
									if(!checkBulletsUnitsCollision(g->p1->defenses[defense_counter]->bullets[0], g->p2->units[0]))
									{


										moveBullet(g->p1->defenses[defense_counter]->bullets[0],g->p2->units[0]->x-g->p1->defenses[defense_counter]->bullets[0]->x,InY-g->p1->defenses[defense_counter]->bullets[0]->y);
									}
									else
									{

										if(g->p2->units[0]->UnitS==dying)
										{

											setMoney(g->p1, g->p2->units[0]->reward_for_killing);
											setNumber(g->p1->no_money, g->p1->money);
											setExperience(g->p1, g->p2->units[0]->exp_for_killing);
											setNumber(g->p1->no_exp, g->p1->experience);
											removeUnit(g->p2);

											break;

										}
										else
										{


											unitSetHP(g->p2->units[0], g->p2->units[0]->hp - g->p1->defenses[defense_counter]->bullets[0]->strength);

											if(g->p2->units[0]->hp<=0)
											{

												g->p2->units[0]->UnitS=dying;
											}


										}

										removeBulletDefense(g->p1->defenses[defense_counter]);
									}
								}
							}
							else
							{
								if(fullBulletsDefenses(g->p1->defenses[defense_counter]))
								{
									removeBulletDefense(g->p1->defenses[defense_counter]);
								}
							}


							defense_counter++;
						}
						defense_counter=0;
						if(emptyUnits(g->p2))
						{
							while(defense_counter<number_defenses_p1)
							{
								if(fullBulletsDefenses(g->p1->defenses[defense_counter]))
								{
									removeBulletDefense(g->p1->defenses[defense_counter]);
								}
								defense_counter++;
							}
						}


					}




					if(g->p1->s->SpecialS==attack)
					{
						if(g->p2->units[counter]!=NULL)
						{



							unitSetHP(g->p2->units[counter], g->p2->units[counter]->hp - g->p1->s->strength);
							if(g->p2->units[counter]->hp<=0)
							{

								g->p2->units[counter]->UnitS=dying;
							}

						}


					}

					if((g->p2->units[0]!=NULL) && (g->p2->units[counter]!=NULL) && (g->p2->units[counter]->UnitS!=dying))
					{
						if(!checkUnitsTowerCollision(g->p2->units[0], g->p1->t))
						{


							if(counter!=0)
							{
								if(g->p2->units[counter]->type==1)
								{
									if(g->p2->units[counter]->UnitS!=shooting)
									{
										if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
										}
										else
										{
											g->p2->units[counter]->UnitS=standing;
										}
									}
								}
								else
								{
									if(g->p2->units[counter-1]->type==1 && (g->p2->units[counter-1]->UnitS==shooting || g->p2->units[counter-1]->UnitS==standing))
									{
										if(checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1],2))
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
											Unit* u_aux=g->p2->units[counter];
											g->p2->units[counter]=g->p2->units[counter-1];
											g->p2->units[counter-1]=u_aux;
										}
										else
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
										}
									}
									else
									{
										if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
										}
										else
										{
											g->p2->units[counter]->UnitS=standing;
										}
									}
								}

							}
							else
							{
								if(g->p2->units[counter]->UnitS!=shooting)
								{
									g->p2->units[counter]->UnitS=moving;
									MoveUnit(g->p2->units[counter]);
								}


							}


						}
						else
						{

							if(counter!=0)
							{
								if(g->p2->units[counter]->type==1)
								{
									if(g->p2->units[counter]->UnitS!=shooting)
									{
										if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
										}
										else
										{
											g->p2->units[counter]->UnitS=standing;
										}
									}
								}
								else
								{
									if(g->p2->units[counter-1]->type==1 && (g->p2->units[counter-1]->UnitS==shooting || g->p2->units[counter-1]->UnitS==standing))
									{
										if(checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1],2))
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
											Unit* u_aux=g->p2->units[counter];
											g->p2->units[counter]=g->p2->units[counter-1];
											g->p2->units[counter-1]=u_aux;
										}
										else
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
										}
									}
									else
									{
										if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
										}
										else
										{
											g->p2->units[counter]->UnitS=standing;
										}
									}
								}

							}
							else
							{
								g->p2->units[0]->UnitS=attacking;
								if(g->timer_cntr%60==0){

									towerSetHP(g->p1->t, g->p1->t->hp - g->p2->units[0]->strength);
									if(g->p1->t->hp>=0)
									{
										setNumber(g->p1->no_tower_life, g->p1->t->hp);
									}

								}
							}
						}
					}

				}

				counter++;


			}
			if(g->p1->s->SpecialS==attack)
			{
				g->p1->s->SpecialS=charging;
				g->used_special1=1;
			}
			else
			{
				g->used_special1=0;
			}


		}
		else
		{
			if(!(emptyUnits(g->p1)) && !(emptyUnits(g->p2)))
			{
				if(g->used_special2)
				{
					aux_cnt=countUnits(g->p1);

					int c=0;
					while(aux_cnt>0)
					{
						Unit* u=g->p1->units[0];
						if(g->p1->units[c]->UnitS==dying)
						{

							setMoney(g->p2, g->p1->units[c]->reward_for_killing);
							setNumber(g->p2->no_money, g->p2->money);
							setExperience(g->p2, g->p1->units[c]->exp_for_killing);
							setNumber(g->p2->no_exp, g->p2->experience);
							removeUnit(g->p1);

						}
						else
						{
							removeUnit(g->p1);
							addUnits(g->p1, u);
						}
						aux_cnt--;

					}
				}

				if(g->used_special1)
				{
					aux_cnt=countUnits(g->p2);
					int c=0;
					while(aux_cnt>0)
					{
						Unit* u=g->p2->units[0];
						if(g->p2->units[c]->UnitS==dying)
						{

							setMoney(g->p1, g->p2->units[c]->reward_for_killing);
							setNumber(g->p1->no_money, g->p1->money);
							setExperience(g->p1, g->p2->units[c]->exp_for_killing);
							setNumber(g->p1->no_exp, g->p1->experience);
							removeUnit(g->p2);

						}
						else
						{
							removeUnit(g->p2);
							addUnits(g->p2, u);
						}
						aux_cnt--;
					}
				}

				counter=0;
				defense_counter=0;
				while(counter<MAX_UNITS)
				{

					if(!(emptyUnits(g->p1)) && !(emptyUnits(g->p2)))
					{

						if(number_defenses_p2>0 && (g->p1->units[0]!=NULL))
						{
							while(defense_counter<number_defenses_p2)
							{
								if(checkUnitsDefenseRange(g->p1->units[0], g->p2->defenses[defense_counter]))
								{

									if(emptyBulletsDefenses(g->p2->defenses[defense_counter]))
									{

										if(g->timer_cntr%60==0){

											Bullet* b= InitBullet(g->p2->defenses[defense_counter]->x-g->p2->defenses[defense_counter]->width, g->p2->defenses[defense_counter]->y+(g->p2->defenses[defense_counter]->height/2), g->p2->defenses[defense_counter]->strength, 2, 1, "bullet");
											addBulletsDefense(g->p2->defenses[defense_counter], b);}
									}
									else
									{
										if(!checkBulletsUnitsCollision(g->p2->defenses[defense_counter]->bullets[0], g->p1->units[0]))
										{


											moveBullet(g->p2->defenses[defense_counter]->bullets[0],g->p2->defenses[defense_counter]->bullets[0]->x-g->p1->units[0]->x+g->p1->units[0]->width,InY-g->p2->defenses[defense_counter]->bullets[0]->y);
										}
										else
										{

											if(g->p1->units[0]->UnitS==dying)
											{

												setMoney(g->p2, g->p1->units[0]->reward_for_killing);
												setNumber(g->p2->no_money, g->p2->money);
												setExperience(g->p2, g->p1->units[0]->exp_for_killing);
												setNumber(g->p2->no_exp, g->p2->experience);
												removeUnit(g->p1);

												break;

											}
											else
											{


												unitSetHP(g->p1->units[0], g->p1->units[0]->hp - g->p2->defenses[defense_counter]->bullets[0]->strength);

												if(g->p1->units[0]->hp<=0)
												{

													g->p1->units[0]->UnitS=dying;
												}


											}

											removeBulletDefense(g->p2->defenses[defense_counter]);
										}
									}
								}
								else
								{
									if(fullBulletsDefenses(g->p2->defenses[defense_counter]))
									{
										removeBulletDefense(g->p2->defenses[defense_counter]);
									}
								}


								defense_counter++;
							}
							defense_counter=0;
							if(emptyUnits(g->p1))
							{
								while(defense_counter<number_defenses_p2)
								{
									if(fullBulletsDefenses(g->p2->defenses[defense_counter]))
									{
										removeBulletDefense(g->p2->defenses[defense_counter]);
									}
									defense_counter++;
								}
							}


						}

						defense_counter=0;
						if(number_defenses_p1>0 && (g->p2->units[0]!=NULL))
						{
							while(defense_counter<number_defenses_p1)
							{

								if(checkUnitsDefenseRange(g->p2->units[0], g->p1->defenses[defense_counter]))
								{

									if(emptyBulletsDefenses(g->p1->defenses[defense_counter]))
									{


										if(g->timer_cntr%60==0){

											Bullet* b= InitBullet(g->p1->defenses[defense_counter]->x+g->p1->defenses[defense_counter]->width, g->p1->defenses[defense_counter]->y+(g->p1->defenses[defense_counter]->height/2), g->p1->defenses[defense_counter]->strength, 1, 1, "bullet");
											addBulletsDefense(g->p1->defenses[defense_counter], b);}
									}
									else
									{
										if(!checkBulletsUnitsCollision(g->p1->defenses[defense_counter]->bullets[0], g->p2->units[0]))
										{


											moveBullet(g->p1->defenses[defense_counter]->bullets[0],g->p2->units[0]->x-g->p1->defenses[defense_counter]->bullets[0]->x,InY-g->p1->defenses[defense_counter]->bullets[0]->y);
										}
										else
										{

											if(g->p2->units[0]->UnitS==dying)
											{

												setMoney(g->p1, g->p2->units[0]->reward_for_killing);
												setNumber(g->p1->no_money, g->p1->money);
												setExperience(g->p1, g->p2->units[0]->exp_for_killing);
												setNumber(g->p1->no_exp, g->p1->experience);
												removeUnit(g->p2);

												break;

											}
											else
											{


												unitSetHP(g->p2->units[0], g->p2->units[0]->hp - g->p1->defenses[defense_counter]->bullets[0]->strength);

												if(g->p2->units[0]->hp<=0)
												{

													g->p2->units[0]->UnitS=dying;
												}


											}

											removeBulletDefense(g->p1->defenses[defense_counter]);
										}
									}
								}
								else
								{
									if(fullBulletsDefenses(g->p1->defenses[defense_counter]))
									{
										removeBulletDefense(g->p1->defenses[defense_counter]);
									}
								}


								defense_counter++;
							}
							defense_counter=0;
							if(emptyUnits(g->p2))
							{
								while(defense_counter<number_defenses_p1)
								{
									if(fullBulletsDefenses(g->p1->defenses[defense_counter]))
									{
										removeBulletDefense(g->p1->defenses[defense_counter]);
									}
									defense_counter++;
								}
							}


						}


						if(g->p1->units[counter]!=NULL && (g->p1->units[counter]->UnitS!=dying))
						{

							if(emptyUnits(g->p2))
							{
								if((g->p1->units[counter]->type==1))
								{
									if(!emptyBulletsUnits(g->p1->units[counter]))
									{
										removeBulletUnit(g->p1->units[counter]);
									}
									if(g->p1->units[counter]->UnitS==shooting)
									{
										g->p1->units[counter]->UnitS=standing;
									}
								}
								counter++;
								continue;
							}
							if((g->p1->units[counter]->type==1) && (checkUnitEnemyUnitRange(g->p1->units[counter], g->p2->units[0])) && !checkUnitCollision(g->p1->units[counter], g->p2->units[0]))
							{

								g->p1->units[counter]->UnitS=shooting;
								if(emptyBulletsUnits(g->p1->units[counter]))
								{

									if(g->timer_cntr%60==0){

										Bullet* b= InitBullet(g->p1->units[counter]->x+g->p1->units[counter]->width, g->p1->units[counter]->y+18, g->p1->units[counter]->strength, 1, 2, "bullet");
										addBulletsUnits(g->p1->units[counter], b);}
								}
								else
								{
									if(!checkBulletsUnitsCollision(g->p1->units[counter]->bullets[0], g->p2->units[0]))
									{

										moveBullet(g->p1->units[counter]->bullets[0],0,0);
									}
									else
									{
										if(g->p2->units[0]->UnitS==dying)
										{
											setMoney(g->p1, g->p2->units[0]->reward_for_killing);
											setNumber(g->p1->no_money, g->p1->money);
											setExperience(g->p1, g->p2->units[0]->exp_for_killing);
											setNumber(g->p1->no_exp, g->p1->experience);
											removeUnit(g->p2);

										}
										else
										{
											unitSetHP(g->p2->units[0], g->p2->units[0]->hp - g->p1->units[counter]->bullets[0]->strength);
											if(g->p2->units[0]->hp<=0)
											{
												g->p2->units[0]->UnitS=dying;
											}
										}
										removeBulletUnit(g->p1->units[counter]);

									}
								}
							}
							else
							{
								g->p1->units[counter]->UnitS=standing;
								if(!emptyBulletsUnits(g->p1->units[counter]))
								{
									removeBulletUnit(g->p1->units[counter]);
								}
							}
						}

						else
						{
							if(g->p1->units[counter]!=NULL && g->p1->units[counter]->UnitS==dying)
							{
								setMoney(g->p2, g->p1->units[0]->reward_for_killing);
								setNumber(g->p2->no_money, g->p2->money);
								setExperience(g->p2, g->p1->units[0]->exp_for_killing);
								setNumber(g->p2->no_exp, g->p2->experience);
								removeUnit(g->p1);
							}
						}

						if(g->p2->units[counter]!=NULL && (g->p2->units[counter]->UnitS!=dying))
						{
							if(emptyUnits(g->p1))
							{
								if((g->p2->units[counter]->type==1))
								{
									if(!emptyBulletsUnits(g->p2->units[counter]))
									{
										removeBulletUnit(g->p2->units[counter]);
									}
									if(g->p2->units[counter]->UnitS==shooting)
									{
										g->p2->units[counter]->UnitS=standing;
									}
								}
								counter++;
								continue;
							}
							if((g->p2->units[counter]->type==1) && (checkUnitEnemyUnitRange(g->p2->units[counter], g->p1->units[0])) && !checkUnitCollision(g->p2->units[counter], g->p1->units[0] ))
							{
								g->p2->units[counter]->UnitS=shooting;
								if(emptyBulletsUnits(g->p2->units[counter]))
								{
									if(g->timer_cntr%60==0){

										Bullet* b= InitBullet(g->p2->units[counter]->x-g->p2->units[counter]->width, g->p2->units[counter]->y+18, g->p2->units[counter]->strength, 2, 2, "bullet");
										addBulletsUnits(g->p2->units[counter], b);}
								}
								else
								{
									if(!checkBulletsUnitsCollision(g->p2->units[counter]->bullets[0], g->p1->units[0]))
									{
										moveBullet(g->p2->units[counter]->bullets[0],0,0);
									}
									else
									{
										if(g->p1->units[0]->UnitS==dying)
										{
											setMoney(g->p2, g->p1->units[0]->reward_for_killing);
											setNumber(g->p2->no_money, g->p2->money);
											setExperience(g->p2, g->p1->units[0]->exp_for_killing);
											setNumber(g->p2->no_exp, g->p2->experience);
											removeUnit(g->p1);

										}
										else
										{
											unitSetHP(g->p1->units[0], g->p1->units[0]->hp - g->p2->units[counter]->bullets[0]->strength);
											if(g->p1->units[0]->hp<=0)
											{
												g->p1->units[0]->UnitS=dying;
											}
										}

										removeBulletUnit(g->p2->units[counter]);

									}
								}
							}
							else
							{
								g->p2->units[counter]->UnitS=standing;
								if(!emptyBulletsUnits(g->p2->units[counter]))
								{
									removeBulletUnit(g->p2->units[counter]);
								}
							}
						}

						else
						{
							if(g->p2->units[counter]!=NULL && g->p2->units[counter]->UnitS==dying)
							{
								setMoney(g->p1, g->p2->units[0]->reward_for_killing);
								setNumber(g->p1->no_money, g->p1->money);
								setExperience(g->p1, g->p2->units[0]->exp_for_killing);
								setNumber(g->p1->no_exp, g->p1->experience);
								removeUnit(g->p2);
							}
						}



						if(g->p1->units[0]!=NULL && g->p2->units[0]!=NULL)
						{
							if(checkUnitCollision(g->p1->units[0], g->p2->units[0]))
							{
								if((g->p1->units[0]->UnitS!=dying) && (g->p2->units[0]->UnitS!=dying))
								{
									g->p1->units[0]->UnitS=attacking;
									g->p2->units[0]->UnitS=attacking;
								}

								if(g->timer_cntr%60==0){



									if(g->p1->units[0]->UnitS==dying)
									{

										setMoney(g->p2, g->p1->units[0]->reward_for_killing);
										setNumber(g->p2->no_money, g->p2->money);
										setExperience(g->p2, g->p1->units[0]->exp_for_killing);
										setNumber(g->p2->no_exp, g->p2->experience);
										removeUnit(g->p1);


									}
									else
									{
										if(g->p2->units[0]->UnitS==dying)
										{

											setMoney(g->p1, g->p2->units[0]->reward_for_killing);
											setNumber(g->p1->no_money, g->p1->money);
											setExperience(g->p1, g->p2->units[0]->exp_for_killing);
											setNumber(g->p1->no_exp, g->p1->experience);
											removeUnit(g->p2);


										}
									}
									if(g->p1->units[0]!=NULL && g->p2->units[0]!=NULL)
									{

										battleBetweenUnits(g->p1->units[0], g->p2->units[0]);

									}


								}
							}
							else
							{
								if(counter==0)
								{

									if(checkUnitsTowerCollision(g->p1->units[0], g->p2->t))
									{
										g->p1->units[0]->UnitS=attacking;
										if(g->timer_cntr%60==0){
											towerSetHP(g->p2->t, g->p2->t->hp - g->p1->units[0]->strength);
											if(g->p2->t->hp>=0)
											{
												setNumber(g->p2->no_tower_life, g->p2->t->hp);
											}

										}
									}
									else
									{
										if(g->p1->units[0]->UnitS!=shooting && g->p1->units[0]->UnitS!=dying)
										{

											g->p1->units[0]->UnitS=moving;
											MoveUnit(g->p1->units[0]);
										}
									}

									if(checkUnitsTowerCollision(g->p2->units[0], g->p1->t))
									{
										g->p2->units[0]->UnitS=attacking;
										if(g->timer_cntr%60==0){
											towerSetHP(g->p1->t, g->p1->t->hp - g->p2->units[0]->strength);
											if(g->p1->t->hp>=0)
											{
												setNumber(g->p1->no_tower_life, g->p1->t->hp);
											}

										}
									}
									else
									{
										if(g->p2->units[0]->UnitS!=shooting && g->p2->units[0]->UnitS!=dying)
										{
											g->p2->units[0]->UnitS=moving;
											MoveUnit(g->p2->units[0]);
										}
									}
								}


							}

						}


						if(g->p2->s->SpecialS==attack)
						{

							if(g->p1->units[counter]!=NULL)
							{



								unitSetHP(g->p1->units[counter], g->p1->units[counter]->hp - g->p2->s->strength);
								if(g->p1->units[counter]->hp<=0)
								{

									g->p1->units[counter]->UnitS=dying;
								}

							}


						}

						if(g->p1->s->SpecialS==attack)
						{

							if(g->p2->units[counter]!=NULL)
							{



								unitSetHP(g->p2->units[counter], g->p2->units[counter]->hp - g->p1->s->strength);
								if(g->p2->units[counter]->hp<=0)
								{

									g->p2->units[counter]->UnitS=dying;
								}

							}


						}

						if(g->p1->units[0]!=NULL && g->p1->units[counter]!=NULL && (g->p1->units[counter]->UnitS!=dying))
						{

							if(counter!=0)
							{
								if(g->p1->units[counter]->type==1)
								{
									if(g->p1->units[counter]->UnitS!=shooting)
									{
										if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
										{
											g->p1->units[counter]->UnitS=moving;
											MoveUnit(g->p1->units[counter]);
										}
										else
										{
											g->p1->units[counter]->UnitS=standing;
										}
									}
								}
								else
								{
									if(g->p1->units[counter-1]->type==1 && (g->p1->units[counter-1]->UnitS==shooting || g->p1->units[counter-1]->UnitS==standing))
									{
										if(checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
										{
											g->p1->units[counter]->UnitS=moving;
											MoveUnit(g->p1->units[counter]);
											Unit* u_aux=g->p1->units[counter];
											g->p1->units[counter]=g->p1->units[counter-1];
											g->p1->units[counter-1]=u_aux;
										}
										else
										{
											g->p1->units[counter]->UnitS=moving;
											MoveUnit(g->p1->units[counter]);
										}
									}
									else
									{
										if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
										{
											g->p1->units[counter]->UnitS=moving;
											MoveUnit(g->p1->units[counter]);
										}
										else
										{
											g->p1->units[counter]->UnitS=standing;
										}
									}
								}
							}

						}


						if(g->p2->units[0]!=NULL && g->p2->units[counter]!=NULL && (g->p2->units[counter]->UnitS!=dying))
						{

							if(counter!=0)
							{
								if(g->p2->units[counter]->type==1)
								{
									if(g->p2->units[counter]->UnitS!=shooting)
									{
										if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
										}
										else
										{
											g->p2->units[counter]->UnitS=standing;
										}
									}
								}
								else
								{
									if(g->p2->units[counter-1]->type==1 && (g->p2->units[counter-1]->UnitS==shooting || g->p2->units[counter-1]->UnitS==standing))
									{
										if(checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1],2))
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
											Unit* u_aux=g->p2->units[counter];
											g->p2->units[counter]=g->p2->units[counter-1];
											g->p2->units[counter-1]=u_aux;
										}
										else
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
										}
									}
									else
									{
										if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
										{
											g->p2->units[counter]->UnitS=moving;
											MoveUnit(g->p2->units[counter]);
										}
										else
										{
											g->p2->units[counter]->UnitS=standing;
										}
									}
								}

							}

						}




					}
					else
					{

						if(g->p1->units[counter]!=NULL && g->p1->units[counter]->UnitS!=dying )
						{
							if(!checkUnitsTowerCollision(g->p1->units[0], g->p2->t))
							{
								if(counter!=0)
								{
									if(g->p1->units[counter]->type==1)
									{
										if(g->p1->units[counter]->UnitS!=shooting)
										{
											if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
											{
												g->p1->units[counter]->UnitS=moving;
												MoveUnit(g->p1->units[counter]);
											}
											else
											{
												g->p1->units[counter]->UnitS=standing;
											}
										}
									}
									else
									{
										if(g->p1->units[counter-1]->type==1 && (g->p1->units[counter-1]->UnitS==shooting || g->p1->units[counter-1]->UnitS==standing))
										{
											if(checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
											{
												g->p1->units[counter]->UnitS=moving;
												MoveUnit(g->p1->units[counter]);
												Unit* u_aux=g->p1->units[counter];
												g->p1->units[counter]=g->p1->units[counter-1];
												g->p1->units[counter-1]=u_aux;
											}
											else
											{
												g->p1->units[counter]->UnitS=moving;
												MoveUnit(g->p1->units[counter]);
											}
										}
										else
										{
											if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
											{
												g->p1->units[counter]->UnitS=moving;
												MoveUnit(g->p1->units[counter]);
											}
											else
											{
												g->p1->units[counter]->UnitS=standing;
											}
										}
									}
								}
								else
								{
									if(g->p1->units[counter]->UnitS!=shooting)
									{
										g->p1->units[counter]->UnitS=standing;
										MoveUnit(g->p1->units[counter]);
									}
								}
							}
							else
							{

								if(counter!=0)
								{
									if(g->p1->units[counter]->type==1)
									{
										if(g->p1->units[counter]->UnitS!=shooting)
										{
											if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
											{
												g->p1->units[counter]->UnitS=moving;
												MoveUnit(g->p1->units[counter]);
											}
											else
											{
												g->p1->units[counter]->UnitS=standing;
											}
										}
									}
									else
									{
										if(g->p1->units[counter-1]->type==1 && (g->p1->units[counter-1]->UnitS==shooting || g->p1->units[counter-1]->UnitS==standing))
										{
											if(checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
											{
												g->p1->units[counter]->UnitS=moving;
												MoveUnit(g->p1->units[counter]);
												Unit* u_aux=g->p1->units[counter];
												g->p1->units[counter]=g->p1->units[counter-1];
												g->p1->units[counter-1]=u_aux;
											}
											else
											{
												g->p1->units[counter]->UnitS=moving;
												MoveUnit(g->p1->units[counter]);
											}
										}
										else
										{
											if(!checkUnitCollisionSamePlayer(g->p1->units[counter], g->p1->units[counter-1], 1))
											{
												g->p1->units[counter]->UnitS=moving;
												MoveUnit(g->p1->units[counter]);
											}
											else
											{
												g->p1->units[counter]->UnitS=standing;
											}
										}
									}
								}
								else
								{
									g->p1->units[0]->UnitS=attacking;
									if(g->timer_cntr%60==0){
										towerSetHP(g->p2->t, g->p2->t->hp - g->p1->units[0]->strength);
										if(g->p2->t->hp>=0)
										{
											setNumber(g->p2->no_tower_life, g->p2->t->hp);
										}

									}
								}
							}
						}

						if(g->p2->units[counter]!=NULL && g->p2->units[counter]->UnitS!=dying)
						{
							if(!checkUnitsTowerCollision(g->p2->units[0], g->p1->t))
							{
								if(counter!=0)
								{
									if(g->p2->units[counter]->type==1)
									{
										if(g->p2->units[counter]->UnitS!=shooting)
										{
											if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
											{
												g->p2->units[counter]->UnitS=moving;
												MoveUnit(g->p2->units[counter]);
											}
											else
											{
												g->p2->units[counter]->UnitS=standing;
											}
										}
									}
									else
									{
										if(g->p2->units[counter-1]->type==1 && (g->p2->units[counter-1]->UnitS==shooting || g->p2->units[counter-1]->UnitS==standing))
										{
											if(checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1],2))
											{
												g->p2->units[counter]->UnitS=moving;
												MoveUnit(g->p2->units[counter]);
												Unit* u_aux=g->p2->units[counter];
												g->p2->units[counter]=g->p2->units[counter-1];
												g->p2->units[counter-1]=u_aux;
											}
											else
											{
												g->p2->units[counter]->UnitS=moving;
												MoveUnit(g->p2->units[counter]);
											}
										}
										else
										{
											if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
											{
												g->p2->units[counter]->UnitS=moving;
												MoveUnit(g->p2->units[counter]);
											}
											else
											{
												g->p2->units[counter]->UnitS=standing;
											}
										}
									}

								}
								else
								{
									if(g->p2->units[counter]->UnitS!=shooting)
									{
										g->p2->units[counter]->UnitS=moving;
										MoveUnit(g->p2->units[counter]);
									}

								}
							}
							else
							{

								if(counter!=0)
								{
									if(g->p2->units[counter]->type==1)
									{
										if(g->p2->units[counter]->UnitS!=shooting)
										{
											if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
											{
												g->p2->units[counter]->UnitS=moving;
												MoveUnit(g->p2->units[counter]);
											}
											else
											{
												g->p2->units[counter]->UnitS=standing;
											}
										}
									}
									else
									{
										if(g->p2->units[counter-1]->type==1 && (g->p2->units[counter-1]->UnitS==shooting || g->p2->units[counter-1]->UnitS==standing))
										{
											if(checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1],2))
											{
												g->p2->units[counter]->UnitS=moving;
												MoveUnit(g->p2->units[counter]);
												Unit* u_aux=g->p2->units[counter];
												g->p2->units[counter]=g->p2->units[counter-1];
												g->p2->units[counter-1]=u_aux;
											}
											else
											{
												g->p2->units[counter]->UnitS=moving;
												MoveUnit(g->p2->units[counter]);
											}
										}
										else
										{
											if(!checkUnitCollisionSamePlayer(g->p2->units[counter], g->p2->units[counter-1], 2))
											{
												g->p2->units[counter]->UnitS=moving;
												MoveUnit(g->p2->units[counter]);
											}
											else
											{
												g->p2->units[counter]->UnitS=standing;
											}
										}
									}
								}
								else
								{
									g->p2->units[0]->UnitS=attacking;
									if(g-> timer_cntr%60==0){
										towerSetHP(g->p1->t, g->p1->t->hp - g->p2->units[0]->strength);
										if(g->p1->t->hp>=0)
										{
											setNumber(g->p1->no_tower_life, g->p1->t->hp);
										}

									}
								}
							}

						}






					}

					counter++;

				}
				if(g->p1->s->SpecialS==attack)
				{
					g->p1->s->SpecialS=charging;
					g->used_special1=1;
				}
				else
				{
					g->used_special1=0;
				}

				if(g->p2->s->SpecialS==attack)
				{
					g->p2->s->SpecialS=charging;
					g->used_special2=1;
				}
				else
				{
					g->used_special2=0;
				}

			}
			else
			{
				if(g->p2->s->SpecialS!=attack)
				{
					g->used_special2=0;
				}
				if(g->p1->s->SpecialS!=attack)
				{
					g->used_special1=0;
				}
				defense_counter=0;
				while(defense_counter<number_defenses_p1)
				{
					if(fullBulletsDefenses(g->p1->defenses[defense_counter]))
					{
						removeBulletDefense(g->p1->defenses[defense_counter]);
					}
					defense_counter++;
				}
				defense_counter=0;
				while(defense_counter<number_defenses_p2)
				{
					if(fullBulletsDefenses(g->p2->defenses[defense_counter]))
					{
						removeBulletDefense(g->p2->defenses[defense_counter]);
					}
					defense_counter++;
				}





			}

		}
	}
}


void drawGame(Game* g)
{
	int counter=0;

	drawTerrain(g->GameTerrain, g->gameBuffer);


	//Show the menus
	drawBitmap(g->menu_l_bmp, 10,10,ALIGN_LEFT, g->gameBuffer);
	drawBitmap(g->menu_r_bmp, 1014,10,ALIGN_RIGHT, g->gameBuffer);




	if(g->used_special1)
	{
		g->show_special1=1;


	}

	if(g->show_special1)
	{

		if(g->timer_cntr%TIMER_DEFAULT_FREQ!=0)
		{

			DrawSpecial(g->p1->s, g->gameBuffer);
		}
		else
		{
			g->show_special1=0;
		}
	}
	if(g->p1->s->SpecialS==charging)
	{
		drawBitmap(g->special_charge_bmp, 230,116,ALIGN_LEFT, g->gameBuffer);
	}


	if(g->used_special2)
	{
		g->show_special2=1;
	}
	if(g->show_special2)
	{
		if(g->timer_cntr%TIMER_DEFAULT_FREQ!=0)
		{
			DrawSpecial(g->p2->s, g->gameBuffer);
		}
		else
		{
			g->show_special2=0;
		}
	}
	if(g->p2->s->SpecialS==charging)
	{
		drawBitmap(g->special_charge_bmp, 993,116,ALIGN_RIGHT, g->gameBuffer);
	}



	if(!(emptyUnits(g->p1)))
	{
		counter=0;
		while(counter<MAX_UNITS)
		{
			if(g->p1->units[counter]!=NULL)
			{
				if(!emptyBulletsUnits(g->p1->units[counter]))
					drawBullet(g->p1->units[counter]->bullets[0],g->gameBuffer);
				DrawUnit((g->p1)->units[counter],g->gameBuffer, g->timer_anime);

			}
			counter++;
		}
	}

	if(!(emptyUnits(g->p2)))
	{
		counter=0;
		while(counter<MAX_UNITS)
		{
			if(g->p2->units[counter]!=NULL)
			{
				if(!emptyBulletsUnits(g->p2->units[counter]))
					drawBullet(g->p2->units[counter]->bullets[0],g->gameBuffer);
				DrawUnit((g->p2)->units[counter],g->gameBuffer, g->timer_anime);

			}
			counter++;
		}
	}

	DrawNumber(g->p1->no_money, g->gameBuffer, 2);
	DrawNumber(g->p2->no_money, g->gameBuffer,2);

	DrawNumber(g->p1->no_exp, g->gameBuffer,0);
	DrawNumber(g->p2->no_exp, g->gameBuffer,0);

	if(g->p1->level!=5)
	{
		DrawNumber(g->p1->no_exp_to_evolve, g->gameBuffer,0);
	}

	if(g->p2->level!=5)
	{
		DrawNumber(g->p2->no_exp_to_evolve, g->gameBuffer,0);
	}



	DrawNumber(g->p1->no_time_special, g->gameBuffer,0);
	DrawNumber(g->p2->no_time_special, g->gameBuffer,0);


	DrawNumber(g->p1->no_tower_life, g->gameBuffer,1);
	DrawNumber(g->p2->no_tower_life, g->gameBuffer,1);

	switch(g->p1->level)
	{
	case 1:
		drawTower(g->p1->t,g->gameBuffer, MAX_LIFE_TOWER_1, g->p1->t->hp);
		break;
	case 2:
		drawTower(g->p1->t,g->gameBuffer, MAX_LIFE_TOWER_2, g->p1->t->hp);
		break;
	case 3:
		drawTower(g->p1->t,g->gameBuffer, MAX_LIFE_TOWER_3, g->p1->t->hp);
		break;
	case 4:
		drawTower(g->p1->t,g->gameBuffer, MAX_LIFE_TOWER_4, g->p1->t->hp);
		break;
	case 5:
		drawTower(g->p1->t,g->gameBuffer, MAX_LIFE_TOWER_5, g->p1->t->hp);
		break;
	}


	switch(g->p2->level)
	{
	case 1:
		drawTower(g->p2->t,g->gameBuffer, MAX_LIFE_TOWER_1, g->p2->t->hp);
		break;
	case 2:
		drawTower(g->p2->t,g->gameBuffer, MAX_LIFE_TOWER_2, g->p2->t->hp);
		break;
	case 3:
		drawTower(g->p2->t,g->gameBuffer, MAX_LIFE_TOWER_3, g->p2->t->hp);
		break;
	case 4:
		drawTower(g->p2->t,g->gameBuffer, MAX_LIFE_TOWER_4, g->p2->t->hp);
		break;
	case 5:
		drawTower(g->p2->t,g->gameBuffer, MAX_LIFE_TOWER_5, g->p2->t->hp);
		break;
	}





	counter=1;
	while(counter<MAX_SLOTS)
	{
		if(g->p1->slots_defenses[counter]!=NULL)
		{

			drawSlot(g->p1->slots_defenses[counter],g->gameBuffer);

		}
		counter++;
	}

	counter=1;
	while(counter<MAX_SLOTS)
	{
		if(g->p2->slots_defenses[counter]!=NULL)
		{

			drawSlot(g->p2->slots_defenses[counter],g->gameBuffer);

		}
		counter++;
	}

	if(!(emptyDefenses(g->p1)))
	{
		counter=0;
		while(counter<MAX_DEFENSES)
		{
			if(g->p1->defenses[counter]!=NULL)
			{
				if(!emptyBulletsDefenses(g->p1->defenses[counter]))
					drawBullet(g->p1->defenses[counter]->bullets[0],g->gameBuffer);
				DrawDefense((g->p1)->defenses[counter],g->gameBuffer);

			}
			counter++;
		}
	}

	if(!(emptyDefenses(g->p2)))
	{

		counter=0;
		while(counter<MAX_DEFENSES)
		{
			if(g->p2->defenses[counter]!=NULL)
			{
				if(!emptyBulletsDefenses(g->p2->defenses[counter]))
					drawBullet(g->p2->defenses[counter]->bullets[0],g->gameBuffer);
				DrawDefense((g->p2)->defenses[counter],g->gameBuffer);

			}
			counter++;
		}
	}

}

void deleteGame(Game* g)
{
	deletePlayer(g->p1);
	deletePlayer(g->p2);
	deleteTerrain(g->GameTerrain);
	deleteAnimation(g->GameAnime);
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
			u2->UnitS=dying;
		}
		else
		{
			unitSetHP(u2, 1);
			u1->UnitS=dying;
		}
	}
	else
	{
		if(u1->hp<=0)
		{

			u1->UnitS=dying;
		}
		else
		{
			if(u2->hp<=0)
			{

				u2->UnitS=dying;
			}
		}
	}


}

int checkBulletsUnitsCollision(Bullet* b, Unit* u)
{
	if(u->player==1)
	{
		if((b->x-b->width <= u->x+u->width) && (b->y+b->height >=u->y))
		{
			return 1;
		}
	}
	else
	{
		if((b->x+b->width >= u->x-u->width)&& (b->y+b->height >=u->y))
		{
			return 1;
		}
	}
	return 0;
}

