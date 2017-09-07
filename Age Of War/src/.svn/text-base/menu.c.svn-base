
#include "menu.h"


//****************************************Main Menu****************************************//

MainMenu* InitMainMenu() {
	MainMenu* mm = (MainMenu*)malloc(sizeof(MainMenu));

	mm->MainMenuBMP = loadBitmap(getImagePath("main_menu"));

	mm->multiplayer1 = 0;
	mm->multiplayer2 = 0;
	mm->statistics = 0;
	mm->credits = 0;
	mm->exit = 0;
	mm->option = 0;

	mm->menuBuffer = initDoubleBuffer();

	return mm;
}

void updateMainMenu(MainMenu* mm, Mouse* mouse) {

	if (mm->multiplayer1 == 1 && mouse->leftButton_P) {
		mm->option = 1;
	}
	else if (mm->multiplayer2 == 1 && mouse->leftButton_P) {
		mm->option = 2;
	}
	else if (mm->statistics == 1 && mouse->leftButton_P) {
		mm->option = 3;
	}
	else if (mm->credits == 1 && mouse->leftButton_P) {
		mm->option = 4;
	}
	else if (mm->exit == 1 && mouse->leftButton_P) {
		mm->option = 5;
	}
	else {
		if (MouseOverBMP(MultiPlayer1X, MultiPlayer1Y, MenuWidth, MenuHeight, mouse)) {
			mm->multiplayer1 = 1;
			mm->multiplayer2 = 0;
			mm->statistics = 0;
			mm->credits = 0;
			mm->exit = 0;
		}
		else if (MouseOverBMP(MultiPlayer2X, MultiPlayer2Y, MenuWidth, MenuHeight, mouse)) {
			mm->multiplayer1 = 0;
			mm->multiplayer2 = 1;
			mm->statistics = 0;
			mm->credits = 0;
			mm->exit = 0;
		}
		else if (MouseOverBMP(StatisticsX, StatisticsY, MenuWidth, MenuHeight, mouse)) {
			mm->multiplayer1 = 0;
			mm->multiplayer2 = 0;
			mm->statistics = 1;
			mm->credits = 0;
			mm->exit = 0;
		}
		else if (MouseOverBMP(CreditsX, CreditsY, MenuWidth, MenuHeight, mouse)) {
			mm->multiplayer1 = 0;
			mm->multiplayer2 = 0;
			mm->statistics = 0;
			mm->credits = 1;
			mm->exit = 0;
		}
		else if (MouseOverBMP(ExitX, ExitY, MenuWidth, MenuHeight, mouse)) {
			mm->multiplayer1 = 0;
			mm->multiplayer2 = 0;
			mm->statistics = 0;
			mm->credits = 0;
			mm->exit = 1;
		}
	}
}

void drawMainMenu(MainMenu* mm) {
	drawBitmap(mm->MainMenuBMP, 0, 0, ALIGN_LEFT, mm->menuBuffer);

}

void deleteMainMenu(MainMenu* mm) {
	deleteBitmap(mm->MainMenuBMP);
	free(mm);
}

int MouseOverBMP(int x, int y, int width, int height, Mouse* mouse) {
	return !(x + width < mouse->x || x > mouse->x + mouse->mouseWidth
			|| y + height < mouse->y || y > mouse->y + mouse->mouseHeight);
}

void resetFlagsMenu(MainMenu* mm) {
	mm->multiplayer1 = 0;
	mm->multiplayer2 = 0;
	mm->statistics = 0;
	mm->credits = 0;
	mm->exit = 0;
	mm->option = 0;
}

//***************************************Pause Menu****************************************//

PauseMenu* InitPauseMenu() {
	PauseMenu* pm = (PauseMenu*)malloc(sizeof(PauseMenu));
	pm->PauseMenuBMP = loadBitmap(getImagePath("pause_menu"));
	pm->resume = 0;
	pm->exit = 0;
	pm->option = 0;
	pm->pauseBuffer = initDoubleBuffer();
	return pm;
}

void updatePauseMenu(PauseMenu* pm, Mouse* mouse) {
	if (pm->exit == 1 && mouse->leftButton_P) {
		pm->option = 2;
	}
	else if (pm->resume == 1 && mouse->leftButton_P) {
		pm->option = 1;
	}
	else {
		if (MouseOverBMP(ResumeX, ResumeY, PauseWitdh, PauseHeight, mouse)) {
			pm->resume = 1;
			pm->exit = 0;
		}
		else if (MouseOverBMP(Exit2X, Exit2Y, PauseWitdh, PauseHeight, mouse)) {
			pm->exit = 1;
			pm->resume = 0;
		}
		else {
			pm->exit = 0;
			pm->resume = 0;
		}
	}
}

void drawPauseMenu(PauseMenu* pm) {
	drawBitmap(pm->PauseMenuBMP, 0, 0, ALIGN_LEFT, pm->pauseBuffer);

}

void deletePauseMenu(PauseMenu* pm) {
	deleteBitmap(pm->PauseMenuBMP);
	free(pm);
}

//***************************************HighScores****************************************//

Statistics* InitStatistics() {
	Statistics* hs = (Statistics*)malloc(sizeof(Statistics));
	hs->font = InitFont();
	hs->StatisticsBMP = loadBitmap(getImagePath("highscores_menu"));
	hs->exit = 0;
	hs->option = 0;
	hs->statsBuffer = initDoubleBuffer();
	hs->counter = 0;
	hs->flag = 0;

	hs->lines = (char**) malloc (10*sizeof(char*));

	FILE *file;
	file = fopen("home/lcom/lcom1617-t4g09/project/src/HighScores.txt", "r");

	int i;

	for(i = 0; i < 10; i++)
		hs->lines[i] = (char*)malloc(100*sizeof(char));

	i = 0;
	while(fgets(hs->lines[i],256,file) != NULL){
		i++;
	}

	fclose(file);

	hs->lines[i]=NULL;

	return hs;
}

void updateStatistics(Statistics* hs, Mouse* mouse) {
	if (hs->exit == 1 && mouse->leftButton_P) {
		hs->option = 1;
	}
}

void drawStatistics(Statistics* hs) {
	drawBitmap(hs->StatisticsBMP, 0, 0, ALIGN_LEFT, hs->statsBuffer);

	int Xpos = 100;
	int Ypos = 380;

	while(hs->lines[hs->counter]!=NULL){
		int j;
		char NAME[10];
		char SCORE[100];
		char* temp = strchr(hs->lines[hs->counter], '|');
		for(j=0; hs->lines[hs->counter][j] != *temp ; j++){
			NAME[j]=hs->lines[hs->counter][j];
		}
		NAME[j+1] = '\0';
		drawText(hs->font, NAME, Xpos, Ypos, hs->statsBuffer);
		j++;
		int z;
		for(z=0; hs->lines[hs->counter][j] != '\n' ;j++,z++){
			SCORE[z] = hs->lines[hs->counter][j];
		}
		SCORE[z+1]='\0';
		drawText(hs->font, SCORE, Xpos+600, Ypos, hs->statsBuffer);
		if(Ypos<768)
			Ypos += 50;
		else
			break;
		memset(&NAME[0], 0, sizeof(NAME));
		memset(&SCORE[0], 0, sizeof(SCORE));
		hs->counter++;
	}
	hs->flag=1;
}

void deleteStatistics(Statistics* hs) {
	deleteBitmap(hs->StatisticsBMP);
	deleteFont(hs->font);
	free(hs);
}

//***************************************Credits Menu****************************************//

Credits* InitCredits() {
	Credits* cr = (Credits*)malloc(sizeof(Credits));
	cr->CreditsBMP = loadBitmap(getImagePath("credits_menu"));
	cr->exit = 0;
	cr->option = 0;
	cr->creditsBuffer = initDoubleBuffer();
	return cr;
}

void updateCredits(Credits* cr, Mouse* mouse) {
	if (cr->exit == 1 && mouse->leftButton_P) {
		cr->option = 1;
	}

}

void drawCredits(Credits* cr) {
	drawBitmap(cr->CreditsBMP, 0, 0, ALIGN_LEFT, cr->creditsBuffer);

}

void deleteCredits(Credits* cr) {
	deleteBitmap(cr->CreditsBMP);
	free(cr);
}

//***************************************SaveMenu****************************************//

SaveMenu* InitSaveMenu(int score1, int score2) {
	SaveMenu* sm = (SaveMenu*) malloc(sizeof(SaveMenu));
	sm->SaveBMP = loadBitmap(getImagePath("highscores_menu"));

	sm->counter = 0;
	sm->flag_1 = 0;
	sm->flag_2 = 1;

	sm->key = 0;
	sm->exit = 0;
	sm->option = 0;

	sm->score1 = score1;
	sm->score2 = score2;

	memset(&sm->name1[0], 0, sizeof(sm->name1));
	memset(&sm->name2[0], 0, sizeof(sm->name2));

	sm->saveBuffer = initDoubleBuffer();

	return sm;
}


void kbdSaveHandler(SaveMenu* sm, unsigned long key){
	sm->key = scanCodeToAscii(key);
}

void updateSaveMenu(SaveMenu* sm, Mouse* mouse) {
	if (sm->exit == 1) {
		sm->option = 1;
	}

	if(sm->flag_1 == 0){
		if(sm->key == '0'){
			sm->counter = 0;
			sm->flag_1 = 1;
			sm->flag_2 = 0;
			sm->key = '=';
		}
		else{
			if(sm->key != '='){
				if( sm->key != 0){
					if( sm->counter <9){
						sm->name1[sm->counter]=sm->key;
						sm->counter++;
						sm->key = '=';
						sm->flag_2 = 1;
					}
				}

			}

		}
	}

	if(sm->flag_2 == 0){
		if(sm->key == '0'){
			sm->counter = 0;
			sm->flag_2 = 1;
			sm->key = '=';
			sm->flag_1=1;

			FILE *file;
			file = fopen("home/lcom/lcom1617-t4g09/project/src/HighScores.txt", "a+");
			fprintf(file, "%s|%d\n", sm->name1,sm->score1);
			fprintf(file, "%s|%d\n", sm->name2,sm->score2);
			fclose(file);
		}
		else{
			if(sm->key != '='){
				if( sm->key != 0){
					if( sm->counter <9){
						sm->name2[sm->counter]=sm->key;
						sm->counter++;
						sm->key = '=';
						sm->flag_1=1;
					}

				}
			}
		}
	}
}

void drawSaveMenu(SaveMenu* sm){
	Font* font = InitFont();
	drawBitmap(sm->SaveBMP, 0, 0, ALIGN_LEFT, sm->saveBuffer);

	char scr1[15];
	char scr2[15];
	sprintf(scr1, "%d", sm->score1);
	sprintf(scr2, "%d", sm->score2);

	if(sm->flag_1 == 1) {
		drawText(font, sm->name1, 100, 450, sm->saveBuffer);
	}
	if(sm->flag_2 == 1 && sm->flag_1 == 1){
		drawText(font, sm->name2, 100, 550, sm->saveBuffer);
	}

	drawText(font, scr1, 693, 450, sm->saveBuffer);
	drawText(font, scr2, 693, 550, sm->saveBuffer);
	deleteFont(font);

}

void deleteSaveMenu(SaveMenu* sm){
	deleteBitmap(sm->SaveBMP);
	free(sm);
}
