#include "AgeOfWar.h"


AgeOfWar* InitAgeOfWar(){
	AgeOfWar* aow = (AgeOfWar*) malloc(sizeof(AgeOfWar));

	if(subscribeDevices(aow))
		return NULL;

	aow->timer_flag = 0;
	aow->keyboard_flag = 0;
	aow->mouse_flag = 0;
	aow->timer_counter = 0;

	aow->mm = NULL;
	aow->g = NULL;
	//aow->mp1=NULL;
	//aow->mp2=NULL;
	//aow->stats=NULL;
	//aow->credits=NULL;
	//aow->pm=NULL;
	//aow->sm=NULL;

	//aow->date = malloc(sizeof(Date));
	//aow->date = InitDate();

	aow->mouse = (Mouse*) malloc(sizeof(Mouse));
	aow->mouse = InitMouse();

	mouse_int_handler(SSME); //enable stream mode
	mouse_int_handler(EDR); //enable data reporting

	aow->currentState = MainMenu_S;

	return aow;
}

void updateAgeOfWar(AgeOfWar* aow){
	resetFlags(aow);

	switch (aow->currentState) {
	case MainMenu_S: {
		aow->mm = (MainMenu*) malloc(sizeof(MainMenu));
		aow->mm = InitMainMenu();
		interruptHandler(aow);
		deleteMainMenu(aow->mm);
		break;
	}

	case MultiPlayer1_S: {
		aow->g = (Game*) malloc(sizeof(Game));
		aow->g = InitGame(0);
		interruptHandler(aow);
		deleteGame(aow->g);
		break;
	}
	/*
	case Multiplayer2_S: {
		aow->g = (Game*) malloc(sizeof(Game));
		aow->g = InitGame(2);
		Loop(aow);
		break;
	}
	case Statistics_S:
		aow->stats = (Statistics*) malloc(sizeof(Statistics));
		aow->stats = InitHighScores();
		Loop(aow);
		deleteHighScores(aow->hs);
		break;
	case Credits_S:
		aow->credits = (Credits*) malloc(sizeof(Credits));
		aow->credits = InitCredits();
		Loop(aow);
		deleteHighScores(aow->credits);
		break;
	 */
	case Exit_S:
		//aow->currentState = Exit_S;
		break;
	}
	printf("merdou yey\n");
}

void deleteAgeOfWar(AgeOfWar* aow){
	mouse_int_handler(DDR); //disable data reporting
	unsubscribeDevices(aow);
	//deleteDate(aow->date);
	deleteMouse(aow->mouse);
	free(aow);
}

int subscribeDevices(AgeOfWar* aow)
{
	aow->irq_timer = timer_subscribe_int();
	aow->irq_mouse = mouse_subscribe_int();
	aow->irq_keyboard = kbd_subscribe_int();

	if (aow->irq_timer == -1 || aow->irq_mouse == -1 || aow->irq_keyboard == -1)
		return 1;

	aow->irq_timer=BIT(aow->irq_timer);
	aow->irq_mouse = BIT(aow->irq_mouse);
	aow->irq_keyboard = BIT(aow->irq_keyboard);

	return 0;
}

int unsubscribeDevices(AgeOfWar* aow)
{
	mouse_int_handler(DDR); //disable data reporting
	if(timer_unsubscribe_int()==-1||kbd_unsubscribe_int()==-1||mouse_unsubscribe_int()==-1)
		return 1;


	return 0;
}


void interruptHandler(AgeOfWar* aow)
{
	int ipc_status, r;
	unsigned long code;
	message msg;

	/*
		 unsigned long trash;
		sys_inb(OUT_BUF, &trash);
		int two_byte_flag = 0;
		int break_code_flag = 0;
		int pause_flagM = 0;

		int endGame = 0;
	 */
	int pause_flag_S = 0;

	while (1) {
		if (r = driver_receive(ANY, &msg, &ipc_status) != 0) {
			printf("driver_receive failed with: %d", r);
			return;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & aow->irq_timer) {
					aow->timer_counter++;
					aow->timer_flag = 1;
				}

				if (msg.NOTIFY_ARG & aow->irq_mouse) {
					SetPacket(aow->mouse);
					if (aow->mouse->packetCounter > 2) {
						aow->mouse_flag = 1;
					}
				}


				if (msg.NOTIFY_ARG & aow->irq_keyboard) {
					code = kbc_get_status_codes();
					aow->keyboard_flag = 1;
					printf("%x", code);
				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else {
		}

		switch (aow->currentState) {
		case MainMenu_S:
			if (aow->mouse_flag) {
				updateMouse(aow->mouse, 1); //maybe adapt this function
				aow->mouse->packetCounter = 0;
				aow->mouse_flag = 0;
			}

			if (aow->timer_flag) {
				clearDoubleBuffer(aow->mm->menuBuffer);
				//updateDate(aow->date);
				updateMainMenu(aow->mm, aow->mouse);
				drawMainMenu(aow->mm);
				drawMouse(aow->mouse, aow->mm->menuBuffer);
				updateScreenBuffer(aow->mm->menuBuffer);
				aow->timer_flag = 0;
			}

			switch (aow->mm->option) {
			case 1:
				aow->currentState = MultiPlayer1_S;
				return;
			case 2:
				aow->currentState = MultiPlayer2_S;
				return;
			case 3:
				aow->currentState = Statistics_S;
				return;
			case 4:
				aow->currentState = Credits_S;
				return;

			case 5:
				aow->currentState = Exit_S;
				return;

			default:
				break;
			}
			break;


			case MultiPlayer1_S:
				if (aow->keyboard_flag) {

					if(code==KEY_PRESSED(KEY_ESC)){
						aow->currentState = MainMenu_S;
						return;
					}


					if (code == KEY_PRESSED(KEY_P)) {
						pause_flag_S = 1;
					} else {
						kbdInterruptHandler(aow->g, code);
					}
					aow->keyboard_flag = 0;
				}
				if (aow->mouse_flag) {
					updateMouse(aow->mouse, 0);
					aow->mouse->packetCounter = 0;
					aow->mouse_flag = 0;
				}

				if (aow->timer_flag) { //&& aow->timer_counter % 2 == 0
					clearDoubleBuffer(aow->g->gameBuffer);
					aow->g->timer_cntr= aow->timer_counter;
					updateGame(aow->g);
					drawGame(aow->g);
					drawMouse(aow->mouse, 0);
					updateScreenBuffer(aow->g->gameBuffer);
					aow->timer_flag = 0;
					if ((aow->g->p1->t->hp <=0) || (aow->g->p2->t->hp <=0)) {
						aow->currentState = MainMenu_S;
						aow->g->created_unit=0;
						return;
					}
					/*
					else if (BattalionDestroyed(bt->g)) {
						bt->sm = (SaveMenu*) malloc(sizeof(SaveMenu));
						bt->sm = InitSaveMenu(bt->g->score + 100*bt->g->player->lives);
						//deleteGame(bt->g);
						bt->currentState = SaveMenuS;
					}
				}

				if (pause_flagS) {
					bt->pm = (PauseMenu*) malloc(sizeof(PauseMenu));
					bt->pm = InitPauseMenu();
					bt->currentState = PauseMenuS;
				}
					 */
					break;
					/*
			case Multiplayer2_S:
				if (bt->keyboard_flag) {
					if (code == ESC) {
						pause_flagS = true;
					} else {
						KeyboardInputHandler(bt->g->player, code);
					}
					bt->keyboard_flag = 0;
				}
				if (bt->mouse_flag) {
					updateMouse(bt->ms, 0);
					MouseInputHandler(bt->g->player, bt->ms);
					bt->ms->packetCounter = 0;
					bt->mouse_flag = 0;
				}

				if (bt->timer_flag && bt->timer_counter % 2 == 0) {
					clearBuffer();
					updateGame(bt->g);
					drawGame(bt->g);
					drawMouse(bt->ms, 0);
					updateScreenWithBuffer();
					bt->timer_flag = 0;
					if (OutOfLives(bt->g) && bt->g->player->TankExp.explosionNumber == 0) {
						bt->currentState = MainMenuS;
						//deleteGame(bt->g);
						return;
					}

					else if (BattalionDestroyed(bt->g)) {
						bt->sm = (SaveMenu*) malloc(sizeof(SaveMenu));
						bt->sm = InitSaveMenu(bt->g->score + 100*bt->g->player->lives);
						//deleteGame(bt->g);
						bt->currentState = SaveMenuS;
					}
				}

				if (pause_flagS) {
					bt->pm = (PauseMenu*) malloc(sizeof(PauseMenu));
					bt->pm = InitPauseMenu();
					bt->currentState = PauseMenuS;
				}
				break;


			case MultiPlayS:
				if (bt->keyboard_flag) {
					if (code == ESC) {
						pause_flagM = true;
					} else {
						KeyboardInputHandler(bt->mp->player1, code);
						KeyboardInputHandler(bt->mp->player2, code);
					}
					bt->keyboard_flag = 0;
				}
				if (bt->mouse_flag) {
					updateMouse(bt->ms, 0);
					MouseInputHandler(bt->mp->player1, bt->ms);
					bt->ms->packetCounter = 0;
					bt->mouse_flag = 0;
				}

				if (bt->timer_flag && bt->timer_counter % 2 == 0) {
					clearBuffer();
					updateMultiPlayer(bt->mp);
					drawMultiPlayer(bt->mp);
					drawMouse(bt->ms, 0);
					updateScreenWithBuffer();
					bt->timer_flag = 0;

					if ((bt->mp->player1->lives == 0 && bt->mp->player1->TankExp.explosionNumber == 0) || (bt->mp->player2->lives == 0 && bt->mp->player2->TankExp.explosionNumber == 0)) {
						bt->currentState = MainMenuS;
						//deleteMultiPlayer(bt->mp);
						return;
					}
				}

				if (pause_flagM) {
					bt->pm = (PauseMenu*) malloc(sizeof(PauseMenu));
					bt->pm = InitPauseMenu();
					bt->currentState = PauseMenuS;
				}
				break;

			case Statistics_S:
				if (bt->mouse_flag) {
					updateMouse(bt->ms, 1);
					bt->ms->packetCounter = 0;
					bt->mouse_flag = 0;
				}

				if (bt->timer_flag) {
					if(bt->hs->counter == 0){
						clearBuffer();
						drawHighScores(bt->hs);
					}
					updateHighScores(bt->hs, bt->ms);
					drawBitmap(bt->hs->HighScore, HighScore2X, HighScore2Y, ALIGN_LEFT, 0);
					drawBitmap(bt->hs->Exit, Exit3X, Exit3Y, ALIGN_LEFT, 0);
					if (bt->hs->exit == 1) {
						drawBitmap(bt->hs->Highlight, Exit3X, Exit3Y, ALIGN_LEFT, 0);
					}
					updateScreenWithBuffer();
					drawMouse(bt->ms, 1);
					bt->timer_flag = 0;
				}
				if (bt->hs->option) {
					bt->currentState = MainMenuS;
					return;
				}
				break;

			case Credits_S:
				if (bt->mouse_flag) {
					updateMouse(bt->ms, 1);
					bt->ms->packetCounter = 0;
					bt->mouse_flag = 0;
				}

				if (bt->timer_flag) {
					if(bt->hs->counter == 0){
						clearBuffer();
						drawHighScores(bt->hs);
					}
					updateHighScores(bt->hs, bt->ms);
					drawBitmap(bt->hs->HighScore, HighScore2X, HighScore2Y, ALIGN_LEFT, 0);
					drawBitmap(bt->hs->Exit, Exit3X, Exit3Y, ALIGN_LEFT, 0);
					if (bt->hs->exit == 1) {
						drawBitmap(bt->hs->Highlight, Exit3X, Exit3Y, ALIGN_LEFT, 0);
					}
					updateScreenWithBuffer();
					drawMouse(bt->ms, 1);
					bt->timer_flag = 0;
				}
				if (bt->hs->option) {
					bt->currentState = MainMenuS;
					return;
				}
				break;

			case PauseMenu_S:
				if (bt->mouse_flag) {
					updateMouse(bt->ms, 1);
					bt->ms->packetCounter = 0;
					bt->mouse_flag = 0;
				}

				if (bt->timer_flag) {
					clearBuffer();
					updatePauseMenu(bt->pm, bt->ms);
					drawPauseMenu(bt->pm);
					drawMouse(bt->ms, 0);
					updateScreenWithBuffer();
					bt->timer_flag = 0;
				}
				switch (bt->pm->option) {
				case 1:
					if(pause_flagS){
						bt->currentState = PlayS;
						pause_flagS = false;
						deletePauseMenu(bt->pm);
					} else if (pause_flagM) {
						bt->currentState = MultiPlayS;
						pause_flagM = false;
						deletePauseMenu(bt->pm);
					}
					break;
				case 2:
					bt->currentState = MainMenuS;
					deletePauseMenu(bt->pm);
					resetButtons(bt->ms);
					return;
				default:
					break;
				}
				break;



				case SaveMenu_S:
					if (bt->keyboard_flag) {
						KeyboardHandler(bt->sm, code);
						bt->keyboard_flag = 0;
					}
					if (bt->mouse_flag) {
						updateMouse(bt->ms, 1);
						bt->ms->packetCounter = 0;
						bt->mouse_flag = 0;
					}

					if (bt->timer_flag) {
						clearBuffer();
						updateSaveMenu(bt->sm, bt->ms);
						drawSaveMenu(bt->sm);
						drawMouse(bt->ms, 0);
						updateScreenWithBuffer();
						bt->timer_flag = 0;
					}
					switch (bt->sm->option) {
					case 1:
						bt->currentState = MainMenuS;
						deleteSaveMenu(bt->sm);
						return;
					default:
						break;
					}
					break;
					 */
				}
		}
	}
	printf("saiu");
}

void resetFlags(AgeOfWar* aow){
	aow->timer_flag = 0;
	aow->keyboard_flag = 0;
	aow->mouse_flag = 0;
}
