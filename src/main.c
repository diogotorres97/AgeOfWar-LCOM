#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "game.h"

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
	Game* g = (Game*) malloc(sizeof(Game));
	//Bitmap* test=loadBitmap(getImagePath("back1"));

	g=InitGame(0);

	//drawBitmap(test, 0, 0, ALIGN_LEFT);
	//vg_fill_square(500, 500, 100, 10);
	//sleep(2);
	//deleteBitmap(test);
	deleteGame(g);
	vg_exit();


	return 0;



}
