#ifndef __MENU_H
#define __MENU_H

#include <string.h>
#include <stdio.h>
#include "bitmap.h"
#include "mouse.h"
#include "video_gr.h"
#include "font.h"
#include "keyboard.h"


/** @defgroup menu menu
 * @{
 *
 * Functions related to the Menus
 */

#define MenuWidth       	419
#define MenuHeight      	42

#define MultiPlayer1X       297
#define MultiPlayer1Y       434

#define MultiPlayer2X       299
#define MultiPlayer2Y   	455

#define StatisticsX       	298
#define StatisticsY       	498

#define CreditsX       		299
#define CreditsY      		566

#define ExitX       		299
#define ExitY       		631

//Pause Menu
#define PauseWitdh			485
#define PauseHeight			60
#define ResumeX       		278
#define ResumeY       		480
#define Exit2X       		276
#define Exit2Y       		584

//HighScore


//Credits


//****************************************Main Menu****************************************//

typedef struct {
	Bitmap* MainMenuBMP;

	int multiplayer1;
	int multiplayer2;
	int statistics;
	int credits;
	int exit;
	int option;

	char* menuBuffer;
}MainMenu;

/**
 * @brief init of main menu struct
 *
 * @param
 * @return pointer to the main menu struct
 */
MainMenu* InitMainMenu();

/**
 * @brief update all the flags accordingly to mouse input
 *
 * @param mm pointer to the main menu struct
 * @param mouse pointer to the mouse struct
 * @return
 */

void updateMainMenu(MainMenu* mm, Mouse* mouse);

/**
 * @brief draw all bmps to the buffer
 *
 * @param pointer to the main menu struct
 * @return
 */
void drawMainMenu(MainMenu* mm);

/**
 * @brief free all resources allocated by main menu struct
 *
 * @param pointer to the main menu struct
 * @return
 */
void deleteMainMenu(MainMenu* mm);

/**
 * @brief check if mouse actual position is over the bmp
 *
 * @param x and y are the initial coordinates of the bmp
 * @return 0 if is over, 1 otherwise
 */
int MouseOverBMP(int x, int y, int width, int height, Mouse* mouse);

/**
 * resets te flags
 * @param mm
 */
void resetFlagsMenu(MainMenu* mm);

//***************************************Pause Menu****************************************//

typedef struct {
	Bitmap* PauseMenuBMP;

	int resume;
	int exit;

	int option;
	char* pauseBuffer;
}PauseMenu;

/**
 * @brief init of pause menu struct
 *
 * @param
 * @return pointer to the pause menu struct
 */
PauseMenu* InitPauseMenu();

/**
 * @brief update all the flags accordingly to mouse input
 *
 * @param mm pointer to the pause menu struct
 * @param mouse pointer to the mouse struct
 * @return
 */
void updatePauseMenu(PauseMenu* mm, Mouse* mouse);

/**
 * @brief draw all bmps to the buffer
 *
 * @param pointer to the pause menu struct
 * @return
 */
void drawPauseMenu(PauseMenu* mm);

/**
 * @brief free all resources allocated by pause menu struct
 *
 * @param pointer to the pause menu struct
 * @return
 */
void deletePauseMenu(PauseMenu* mm);

//***************************************HighScores****************************************//

typedef struct {
	Bitmap* StatisticsBMP;
	int counter;
	Font* font;

	int exit;
	int flag;
	int option;
	char* statsBuffer;
	char** lines;
}Statistics;

/**
 * @brief init of highscores struct
 *
 * @param
 * @return pointer to the highscores struct
 */
Statistics* InitStatistics();

/**
 * @brief update all the flags accordingly to mouse input
 *
 * @param hs pointer to HighScores struct
 * @param mouse pointer to the mouse struct
 * @return
 */
void updateStatistics(Statistics* hs, Mouse* mouse);

/**
 * @brief draw all bmps to the buffer
 *
 * @param pointer to highscores struct
 * @return
 */
void drawStatistics(Statistics* hs);

/**
 * @brief free all resources allocated by highscores struct
 *
 * @param pointer to highscores struct
 * @return
 */
void deleteStatistics(Statistics* hs);

//***************************************Credits****************************************//

typedef struct {
	Bitmap* CreditsBMP;

	int exit;

	int option;
	char* creditsBuffer;
}Credits;

/**
 * @brief init of credits struct
 *
 * @param
 * @return pointer to the credits struct
 */
Credits* InitCredits();

/**
 * @brief update all the flags accordingly to mouse input
 *
 * @param cr pointer to credits struct
 * @param mouse pointer to mouse
 * @return
 */
void updateCredits(Credits* cr, Mouse* mouse);

/**
 * @brief draw all bmps to the buffer
 *
 * @param pointer to credits struct
 * @return
 */
void drawCredits(Credits* cr);

/**
 * @brief free all resources allocated by credits struct
 *
 * @param pointer to credits struct
 * @return
 */
void deleteCredits(Credits* cr);

//***************************************SaveMenu****************************************//

typedef struct{
	Bitmap* SaveBMP;
	char key;
	char name1[10];
	char name2[10];
	int score1;
	int score2;
	int exit;
	int option;

	int counter;
	int flag_1;
	int flag_2;

	char* saveBuffer;


}SaveMenu;

/**
 * @brief init of SaveMenu struct
 *
 * @param score1
 * @param score2
 * @return pointer to the SaveMenu struct
 */
SaveMenu* InitSaveMenu(int score1, int score2);

/**
 * @brief update all the flags accordingly to mouse input
 *
 * @param sm pointer to SaveMenu struct
 * @param mouse pointer to mouse
 * @return
 */
void updateSaveMenu(SaveMenu* sm, Mouse* mouse);

/**
 * @brief draw all bmps to the buffer
 *
 * @param pointer to SaveMenu struct
 * @return
 */
void drawSaveMenu(SaveMenu* sm);

/**
 * @brief free all resources allocated by SaveMenu struct
 *
 * @param pointer to SaveMenu struct
 * @return
 */
void deleteSaveMenu(SaveMenu* sm);

/**
 * @brief check if the key passed as parameter is eligible and if so, letter1, 2 or 3 is set, accordingly to the mouse position
 *
 * @param pointer to SaveMenu struct and key
 * @return
 */
void kbdSaveHandler(SaveMenu* sm, unsigned long key);

/** @} end of Menu */

#endif
