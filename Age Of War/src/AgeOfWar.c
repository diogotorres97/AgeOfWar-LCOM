#include "AgeOfWar.h"

AgeOfWar *InitAgeOfWar() {
    AgeOfWar *aow = (AgeOfWar *) malloc(sizeof(AgeOfWar));

    if (subscribeDevices(aow))
        return NULL;

    aow->timer_flag = 0;
    aow->keyboard_flag = 0;
    aow->mouse_flag = 0;
    aow->timer_counter = 0;

    aow->mm = NULL;
    aow->g = NULL;

    aow->stats = NULL;
    aow->credits = NULL;
    aow->pm = NULL;
    aow->sm = NULL;

    aow->date = malloc(sizeof(Date));
    aow->date = InitDate();

    aow->mouse = (Mouse *) malloc(sizeof(Mouse));
    aow->mouse = InitMouse();

    mouse_int_handler(SSME); //enable stream mode
    mouse_int_handler(EDR); //enable data reporting

    aow->currentState = MainMenu_S;

    return aow;
}

void updateAgeOfWar(AgeOfWar *aow) {
    resetFlags(aow);

    switch (aow->currentState) {
        case MainMenu_S: {
            aow->mm = (MainMenu *) malloc(sizeof(MainMenu));
            aow->mm = InitMainMenu();
            interruptHandler(aow);
            deleteMainMenu(aow->mm);
            break;
        }

        case MultiPlayer1_S: {
            aow->g = (Game *) malloc(sizeof(Game));
            aow->g = InitGame(0);
            interruptHandler(aow);

            break;
        }

        case Statistics_S: {
            aow->stats = (Statistics *) malloc(sizeof(Statistics));
            aow->stats = InitStatistics();
            interruptHandler(aow);
            deleteStatistics(aow->stats);
            break;
        }
        case Credits_S: {
            aow->credits = (Credits *) malloc(sizeof(Credits));
            aow->credits = InitCredits();
            interruptHandler(aow);
            deleteCredits(aow->credits);
            break;
        }
        case Exit_S:
            aow->currentState = Exit_S;
            break;
    }
}

void deleteAgeOfWar(AgeOfWar *aow) {
    mouse_int_handler(DDR); //disable data reporting
    unsubscribeDevices(aow);
    deleteDate(aow->date);
    deleteMouse(aow->mouse);
    free(aow);
}

int subscribeDevices(AgeOfWar *aow) {
    aow->irq_timer = timer_subscribe_int();
    aow->irq_mouse = mouse_subscribe_int();
    aow->irq_keyboard = kbd_subscribe_int();
    aow->irq_rtc = rtc_subscribe_int();

    if (aow->irq_timer == -1 || aow->irq_mouse == -1 || aow->irq_keyboard == -1 || aow->irq_rtc == -1)
        return 1;

    aow->irq_timer = BIT(aow->irq_timer);
    aow->irq_mouse = BIT(aow->irq_mouse);
    aow->irq_keyboard = BIT(aow->irq_keyboard);
    aow->irq_rtc = BIT(aow->irq_rtc);

    return 0;
}

int unsubscribeDevices(AgeOfWar *aow) {
    mouse_int_handler(DDR); //disable data reporting
    if (timer_unsubscribe_int() == -1 || kbd_unsubscribe_int() == -1 || mouse_unsubscribe_int() == -1 ||
        rtc_unsubscribe_int() == -1)
        return 1;

    return 0;
}


void interruptHandler(AgeOfWar *aow) {
    int ipc_status, r;
    unsigned long code;
    message msg;


    int pause_flag = 0;

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
                    updateMouse(aow->mouse, 1);
                    aow->mouse->packetCounter = 0;
                    aow->mouse_flag = 0;
                }

                if (aow->timer_flag) {
                    clearDoubleBuffer(aow->mm->menuBuffer);
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

                    if (code == KEY_PRESSED(KEY_ESC)) {
                        aow->currentState = MainMenu_S;
                        return;
                    }

                    if (code == KEY_PRESSED(KEY_SPACE)) {
                        pause_flag = 1;
                    } else {
                        kbdInterruptHandler(aow->g, code);
                    }
                    aow->keyboard_flag = 0;
                }
                if (aow->mouse_flag) {
                    updateMouse(aow->mouse, 1);
                    aow->mouse->packetCounter = 0;
                    aow->mouse_flag = 0;
                }

                if (aow->timer_flag) {
                    clearDoubleBuffer(aow->g->gameBuffer);
                    aow->g->timer_cntr = aow->timer_counter;
                    if (aow->timer_counter % 2 == 0) //FPS
                        aow->g->timer_anime++;
                    updateGame(aow->g);
                    drawGame(aow->g);

                    updateScreenBuffer(aow->g->gameBuffer);
                    aow->timer_flag = 0;

                    if (pause_flag) {
                        aow->pm = (PauseMenu *) malloc(sizeof(PauseMenu));
                        aow->pm = InitPauseMenu();
                        aow->currentState = PauseMenu_S;
                    } else if ((aow->g->p1->t->hp <= 0) || (aow->g->p2->t->hp <= 0)) {
                        aow->sm = (SaveMenu *) malloc(sizeof(SaveMenu));
                        aow->sm = InitSaveMenu(aow->g->p1->experience, aow->g->p2->experience);
                        aow->currentState = SaveMenu_S;
                        aow->g->created_unit = 0;

                    }

                    break;

                    case Statistics_S:
                        if (aow->keyboard_flag) {
                            if (code == KEY_PRESSED(KEY_ESC)) {
                                aow->currentState = MainMenu_S;
                                return;
                            }
                            aow->keyboard_flag = 0;
                        }

                    if (aow->mouse_flag) {

                        resetButtons(aow->mouse);
                        aow->mouse->packetCounter = 0;
                        aow->mouse_flag = 0;
                    }

                    if (aow->timer_flag) {
                        if (aow->stats->flag == 0) {
                            clearDoubleBuffer(aow->stats->statsBuffer);
                            updateStatistics(aow->stats, aow->mouse);
                            drawStatistics(aow->stats);
                            updateScreenBuffer(aow->stats->statsBuffer);
                        }

                        aow->timer_flag = 0;
                    }
                    if (aow->stats->option) {
                        aow->currentState = MainMenu_S;
                        return;
                    }
                    break;

                    case Credits_S:
                        if (aow->keyboard_flag) {
                            if (code == KEY_PRESSED(KEY_ESC)) {
                                aow->currentState = MainMenu_S;
                                return;
                            }
                            aow->keyboard_flag = 0;
                        }
                    if (aow->mouse_flag) {

                        resetButtons(aow->mouse);
                        aow->mouse->packetCounter = 0;
                        aow->mouse_flag = 0;
                    }
                    if (aow->timer_flag) {
                        clearDoubleBuffer(aow->credits->creditsBuffer);
                        updateCredits(aow->credits, aow->mouse);
                        updateDate(aow->date);
                        drawCredits(aow->credits);
                        drawDate(aow->date, 750, 5, aow->credits->creditsBuffer);
                        updateScreenBuffer(aow->credits->creditsBuffer);
                        aow->timer_flag = 0;
                    }
                    if (aow->credits->option) {
                        aow->currentState = MainMenu_S;
                        return;
                    }
                    break;

                    case PauseMenu_S:
                        if (aow->mouse_flag) {
                            updateMouse(aow->mouse, 1);
                            aow->mouse->packetCounter = 0;
                            aow->mouse_flag = 0;
                        }

                    if (aow->timer_flag) {
                        clearDoubleBuffer(aow->pm->pauseBuffer);
                        updatePauseMenu(aow->pm, aow->mouse);
                        drawPauseMenu(aow->pm);
                        drawMouse(aow->mouse, aow->pm->pauseBuffer);
                        updateScreenBuffer(aow->pm->pauseBuffer);
                        aow->timer_flag = 0;
                    }
                    switch (aow->pm->option) {
                        case 1:
                            if (pause_flag) {
                                aow->currentState = MultiPlayer1_S;
                                pause_flag = 0;
                                deletePauseMenu(aow->pm);
                            }
                            break;
                        case 2:
                            aow->currentState = MainMenu_S;
                            deletePauseMenu(aow->pm);
                            resetButtons(aow->mouse);
                            return;
                        default:
                            break;
                    }
                    break;


                    case SaveMenu_S:
                        if (aow->keyboard_flag) {
                            if (code == KEY_PRESSED(KEY_ESC)) {
                                aow->currentState = MainMenu_S;
                                return;
                            }
                            kbdSaveHandler(aow->sm, code);
                            aow->keyboard_flag = 0;
                        }
                    if (aow->mouse_flag) {

                        aow->mouse->packetCounter = 0;
                        aow->mouse_flag = 0;
                    }

                    if (aow->timer_flag) {
                        clearDoubleBuffer(aow->sm->saveBuffer);
                        updateSaveMenu(aow->sm, aow->mouse);

                        drawSaveMenu(aow->sm);


                        updateScreenBuffer(aow->sm->saveBuffer);
                        aow->timer_flag = 0;
                    }
                    switch (aow->sm->option) {
                        case 1:
                            aow->currentState = MainMenu_S;
                            deleteSaveMenu(aow->sm);
                            return;
                        default:
                            break;
                    }
                    break;

                }
        }
    }
}

void resetFlags(AgeOfWar *aow) {
    aow->timer_flag = 0;
    aow->keyboard_flag = 0;
    aow->mouse_flag = 0;
}
