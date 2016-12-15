#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
//#include "game.h"
#include "AgeOfWar.h"

//#include "pixmap.h"

/**
 * main of the project - Age of Wars game
 *
 */
int main() {

	srand(time(NULL)); // randomize the seed
	sef_startup();
	sys_enable_iop(SELF);

	vg_init(0x117);
	AgeOfWar* aow = (AgeOfWar*) malloc(sizeof(AgeOfWar));
	aow = InitAgeOfWar();

	while(aow->currentState != Exit_S){
		updateAgeOfWar(aow);
	}
	deleteAgeOfWar(aow);


	if(vg_exit() != 0)
		return 1;
	return 0;


	return 0;



}
