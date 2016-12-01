#include "game.h"

Game* InitGame(unsigned int mode) {

	Game* g = (Game*) malloc(sizeof(Game));
	g->p1 = (Player*) malloc(sizeof(Player));
	g->p1= InitPlayer(0);
	g->p2 = (Player*) malloc(sizeof(Player));
	g->p2 = InitPlayer(1);


	if(subscribeDevices(g))
		return NULL;

	g->end=false;

	g->back_bmp=loadBitmap(getImagePath("back"));

	unsigned long key;

	if(mode==0)//multiplayer on the same PC
	{
		while(g->end==false)
		{
			gameInterruptHandler(g, &key);

			//&& timer_counter%TIMER_DEFAULT_FREQ==0 && g->created_unit==1
			if(g->timer_flag==1 ) //a second passed
			{
				clearDoubleBuffer();
				updateGame(g);
				drawGame(g);
				//drawMouse(g);
				updateScreenBuffer();
/*
				if(towerGetHP(g->p1->t)==0 || towerGetHP(g->p2->t)==0)
				{
					g->end=true;

				} */
				g->timer_flag = 0;
				g->created_unit=0;
			}

			if(g->kbd_flag)
			{
				if(key==KEY_RELEASED(KEY_ESC))
				{
					g->end=true;
				}
				else
				{
					if(key==KEY_RELEASED(KEY_P))
					{
						g->pause=true;
					}
					else
					{
						kbdInterruptHandler(g, key);
					}
				}
				g->kbd_flag=0;
			}
		}
	}

	unsubscribeDevices(g);

	return g;

}

int subscribeDevices(Game* g)
{
	g->irq_timer=timer_subscribe_int();
	g->irq_timer=BIT(g->irq_timer);
	g->irq_mouse = mouse_subscribe_int();
	g->irq_mouse = BIT(g->irq_mouse);
	g->irq_kbd = kbd_subscribe_int();
	g->irq_kbd = BIT(g->irq_kbd);

	if (g->irq_timer == -1 || g->irq_kbd == -1 || g->irq_mouse == -1)
		return 1;



	g->timer_flag=g->kbd_flag=g->mouse_flag=g->timer_cntr=g->created_unit=0;

	return 0;
}

void unsubscribeDevices(Game* g)
{
	kbd_unsubscribe_int();
	timer_unsubscribe_int();
	//MS_to_KBD_Commands(MS_DSB_STREAM_M);
	mouse_unsubscribe_int();
	//deleteMouse(g->ms);
}

void gameInterruptHandler(Game* g, unsigned long *key)
{
	int ipc_status, r;
	bool two_byte_flag=false;
	message msg;
	timer_set_square(0, TIMER_DEFAULT_FREQ);

	while (1) {
		r = driver_receive(ANY, &msg, &ipc_status);
		if (r != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & g->irq_timer) {
					g->timer_cntr++;
					g->timer_flag = 1;
				}
				/*if (msg.NOTIFY_ARG & g->irq_mouse) {
						SetPacket(g->ms);
						if (g->ms->packetCounter > 2) {
							g->mouse_flag = 1;
						}
					}*/
				if (msg.NOTIFY_ARG & g->irq_kbd) {
					*key = kbc_get_status_codes();

					if (*key == FIRST_OF_TWO_BYTE_SCANCODES) {
						two_byte_flag = true;
					} else if (two_byte_flag) {
						*key |= FIRST_OF_TWO_BYTE_SCANCODES << 8;
						two_byte_flag = false;
						g->kbd_flag = 1;
					} else {
						g->kbd_flag = 1;
					}
				}

				break;
	 		default:
				break; /* no other notifications expected: do nothing */
			}
		}


	}
}

void kbdInterruptHandler(Game* g, unsigned long key)
{
	switch(key)
	{
	case KEY_RELEASED(KEY_1):
						if(!(is_full_gqueue(g->p1->units))) //may create units
						{
							Unit* u=(Unit*) malloc (sizeof(Unit));
							u=InitUnit(InX_P1, InY_P1, 30, 10, 0, "lvl1_1", 15, 20, 50);
							put_gqueue(g->p1->units, u);
							//g->created_unit=1;
						}
	break;
	default:
		break;
	}
}

void updateGame(Game* g)
{
	/*Unit* u=(Unit*) malloc (sizeof(Unit));
	get_front(g->p1->units, u);
	MoveUnit(u);
	deleteUnit(u);
*/
}

void drawGame(Game* g)
{/*
	drawBitmap(g->back_bmp, 0, 0, ALIGN_LEFT);
	Unit* u=(Unit*) malloc (sizeof(Unit));
	get_front(g->p1->units, u);
	DrawUnit(u);
	deleteUnit(u);*/
}

void deleteGame(Game* g)
{
	deletePlayer(g->p1);
	deletePlayer(g->p2);
	free(g->back_bmp);
	free(g);
}
