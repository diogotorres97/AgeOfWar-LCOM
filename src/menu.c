
#include "menu.h"


//****************************************Main Menu****************************************//

MainMenu* InitMainMenu(){
	MainMenu* mm = (MainMenu*) malloc(sizeof(MainMenu));

	mm->MainMenuBMP = loadBitmap(getImagePath("ageofwarfinal"));

	mm->multiplayer1=0;
	mm->multiplayer2=0;
	mm->statistics=0;
	mm->credits=0;
	mm->exit=0;
	mm->option=0;

	mm->menuBuffer = initDoubleBuffer();

	return mm;
}

void updateMainMenu(MainMenu* mm, Mouse* mouse){

	if(mm->multiplayer1 == 1 && mouse->leftButton_P){
		mm->option = 1;
	}else if(mm->multiplayer2 == 1 && mouse->leftButton_P){
		mm->option = 2;
	}else if(mm->statistics == 1 && mouse->leftButton_P){
		mm->option = 3;
	}else if(mm->credits == 1 && mouse->leftButton_P){
		mm->option = 4;
	}else if(mm->exit == 1 && mouse->leftButton_P){
		mm->option = 5;
	}else {
		if (MouseOverBMP(MultiPlayer1X, MultiPlayer1Y, MenuWidth, MenuHeight, mouse)) {
			mm->multiplayer1=1;
			mm->multiplayer2=0;
			mm->statistics=0;
			mm->credits=0;
			mm->exit=0;
		} else if (MouseOverBMP(MultiPlayer2X, MultiPlayer2Y, MenuWidth, MenuHeight, mouse)) {
			mm->multiplayer1=0;
			mm->multiplayer2=1;
			mm->statistics=0;
			mm->credits=0;
			mm->exit=0;
		} else if (MouseOverBMP(StatisticsX, StatisticsY, MenuWidth, MenuHeight, mouse)) {
			mm->multiplayer1=0;
			mm->multiplayer2=0;
			mm->statistics=1;
			mm->credits=0;
			mm->exit=0;
		}else if (MouseOverBMP(CreditsX, CreditsY, MenuWidth, MenuHeight, mouse)) {
			mm->multiplayer1=0;
			mm->multiplayer2=0;
			mm->statistics=0;
			mm->credits=1;
			mm->exit=0;
		} else {
			mm->multiplayer1=0;
			mm->multiplayer2=0;
			mm->statistics=0;
			mm->credits=0;
			mm->exit=1;
		}
	}
}

void drawMainMenu(MainMenu* mm){
	drawBitmap(mm->MainMenuBMP, 0, 0, ALIGN_LEFT,mm->menuBuffer);

}

void deleteMainMenu(MainMenu* mm) {
	deleteBitmap(mm->MainMenuBMP);
	free(mm);
}

int MouseOverBMP(int x, int y, int width, int height, Mouse* mouse){
	return !(x + width < mouse->x || x > mouse->x + mouse->mouseWidth
			|| y + height < mouse->y || y > mouse->y + mouse->mouseHeight);
}

void resetFlagsMenu(MainMenu* mm){
	mm->multiplayer1=0;
	mm->multiplayer2=0;
	mm->statistics=0;
	mm->credits=0;
	mm->exit=0;
	mm->option=0;
}
