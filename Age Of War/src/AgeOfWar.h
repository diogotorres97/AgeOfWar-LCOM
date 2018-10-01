#ifndef __AGEOFWAR_H
#define __AGEOFWAR_H

#include <minix/drivers.h>
#include <minix/syslib.h>
#include "bitmap.h"
#include "stdio.h"
#include "const.h"
#include "rtc.h"
#include "mouse.h"
#include "timer.h"
#include "keyboard.h"
#include "menu.h"
#include "game.h"
#include "font.h"


/** @defgroup AgeOfWar AgeOfWar
* @{
*
* Functions related to the game's state machine
*/

typedef enum {
    MainMenu_S, MultiPlayer1_S, MultiPlayer2_S,
    Statistics_S, Credits_S, Exit_S,
    PauseMenu_S, SaveMenu_S,
} AgeOfWar_S;

typedef struct {
    int irq_timer;
    int irq_mouse;
    int irq_keyboard;
    int irq_rtc;

    int timer_flag;
    int keyboard_flag;
    int mouse_flag;
    int timer_counter;

    MainMenu *mm;
    Game *g;
    Statistics *stats;
    Credits *credits;
    PauseMenu *pm;
    SaveMenu *sm;

    AgeOfWar_S currentState;

    Date *date;
    Mouse *mouse;
} AgeOfWar;

/**
* @brief initialize the main struct
*
* @param
* @return pointer to main struct
*/
AgeOfWar *InitAgeOfWar();


/**
* @brief update accordingly to current state
*
* @param pointer to main struct
* @return
*/
void updateAgeOfWar(AgeOfWar *aow);

/**
* @brief delete all resources allocated by the struct
*
* @param pointer to main struct
* @return
*/
void deleteAgeOfWar(AgeOfWar *aow);

/**
* @brief subscribe devices
*
* @param pointer to main struct
* @return
*/
int subscribeDevices(AgeOfWar *aow);

/**
* @brief unsubscribe devices
*
* @param pointer to main struct
* @return
*/
int unsubscribeDevices(AgeOfWar *aow);

/**
* @brief interruption handler
*
* @param pointer to main struct
* @return
*/
void interruptHandler(AgeOfWar *aow);

/**
* @brief reset timer, keyboard and mouse flags
*
* @param pointer to main struct
* @return
*/
void resetFlags(AgeOfWar *aow);

/** @} end of AgeOfWar */

#endif
