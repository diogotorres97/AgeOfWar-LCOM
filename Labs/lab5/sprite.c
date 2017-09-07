#include "sprite.h"
#include "read_xpm.h"
#include "video_gr.h"
#include <stdlib.h>

//Colours
#define VIDEO_256_TRANSPARENT		0x00
#define VIDEO_256_BLACK				0xFF

static float xspeed_buffer=0;
static float yspeed_buffer=0;

static int draw_sprite(Sprite*sp);

/*
Creates a new sprite with pixmap "pic", with specified
 *
position (within the screen limits) and speed;
 *
Does not draw the sprite on the screen
 *
Returns NULL on invalid pixmap.
 */

Sprite* create_sprite(char*pic[], int x, int y, float xspeed, float yspeed, unsigned int h_res, unsigned int v_res) {

	//allocate space for the "object"
	Sprite *sp = (Sprite*) malloc ( sizeof(Sprite));
	if( sp == NULL )
		return NULL;
	// read the sprite pixmap
	sp->map = read_xpm(pic, &(sp->width), &(sp->height), h_res, v_res);
	if( sp->map == NULL ) {
		free(sp);
		return NULL;
	}

	sp->x =x;
	sp->y =y;
	sp->xspeed = xspeed;
	sp->yspeed = yspeed;

	return sp;
}

void destroy_sprite(Sprite*sp) {
	if( sp == NULL )
		return;
	free(sp->map);
	free(sp);
	sp = NULL;     // hopeless: pointer is passed by value
}

int animate_sprite(Sprite*sp, double delta) {

	double d1 = (sp->yspeed );
	double d2 = (sp->xspeed );

	printf("xs: %d \n ys:%d \n", d1, d2);

	if(sp->xspeed == 0){
		sp->y += d1;
	}
	else {
		sp->x += d2;
	}

	return draw_sprite(sp);

}

int move_sprite(Sprite *sp){
	clear_sprite_area(sp);


	/*The Algorithm - Created by Diogo Torres*/

	/* Because velocity can be a non-integer value, and for velocity above 1, it's impossible to increment non-integer positions
	 * So yspeed_buffer and x_speed_buffer save the decimal part of velocity in each interruption, and when this value
	 * it's greater than 1, the sprite moves 1 position and decrement the buffer.
	 * Example:
	 * first iteration
	 * if xspeed = 3.4
	 * xspeed_buffer = 0.4
	 * x(position) += 3
	 *
	 * second iteration
	 * same xspeed
	 * xspeed_buffer = 0.8
	 * x(position) +=3
	 *
	 * third iteration
	 * same xspeed
	 * xspeed_buffer = 1.2 - 1
	 * xposition += 3 + 1
	 */

	if(sp->xspeed == 0){
		if(yspeed_buffer >= 1){
			yspeed_buffer -= 1;
			yspeed_buffer += sp->yspeed-(int) sp->yspeed;
			sp->y += sp->yspeed + 1;
		}
		else{
			yspeed_buffer += sp->yspeed-(int) sp->yspeed;
			sp->y += sp->yspeed;
		}
	}
	else
	{
		if(xspeed_buffer >= 1){
			xspeed_buffer-= 1;
			xspeed_buffer += sp->xspeed-(int) sp->xspeed;
			sp->x += sp->xspeed + 1;
		}
		else{
			xspeed_buffer += sp->xspeed-(int) sp->xspeed;
			sp->x += sp->xspeed;
		}
	}

	draw_sprite(sp);
}

/*Some useful non-visible functions*/
static int draw_sprite(Sprite*sp) {
	return vg_set_xpm(sp->x, sp->y, sp->map, sp->width, sp->height);

}

int clear_sprite_area(Sprite *sp)
{
	return vg_set_color(sp->x, sp->y, sp->width, sp->height, VIDEO_256_BLACK);
}



static int check_collision(Sprite*sp, char*base) {
	//...
	return 0;
}



