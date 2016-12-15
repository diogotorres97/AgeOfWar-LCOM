#ifndef __MENU_H
#define __MENU_H

#include "bitmap.h"
#include "mouse.h"
#include "video_gr.h"

/** @defgroup menu menu
 * @{
 *
 * Functions related to the Menus
 */

#define MenuWidth       	419
#define MenuHeight      	42
#define MultiPlayer1X       299
#define MultiPlayer1Y       387
#define MultiPlayer2X       299
#define MultiPlayer2Y   	455
#define StatisticsX       	299
#define StatisticsY       	522
#define CreditsX       		299
#define CreditsY      		590
#define ExitX       		299
#define ExitY       		654

#define ResumeX       		312
#define ResumeY       		200
#define Exit2X       		312
#define Exit2Y       		500
#define Exit3X       		74
#define Exit3Y       		624
#define HighScore2X  		312
#define HighScore2Y  		50

//****************************************Main Menu****************************************//

typedef struct{
	Bitmap* MainMenuBMP;
	Bitmap* Highlight;

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
 * @param pointer to the main menu struct and mouse
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

void resetFlagsMenu(MainMenu* mm);

#endif
