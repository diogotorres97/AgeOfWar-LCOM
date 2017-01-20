#include "special.h"

/******************************* Special functions *****************************************/

Special* InitSpecial(int x, int strength, char* name_special, int player)
{

	Special *s = (Special *)malloc(sizeof(Special));

	s->special_bmp = loadBitmap(getImagePath(name_special));

	s->x = x;

	s->strength = strength;
	s->player = player;
	s->y = 0;

	s->SpecialS = available;

	return s;
}

void DrawSpecial(Special *s, char* doubleBuffer)
{
	if (s->player == 1)

		bitmap_draw_transparency(s->special_bmp, s->x, s->y, ALIGN_LEFT, doubleBuffer);
	else
		bitmap_draw_transparency(s->special_bmp, s->x, s->y, ALIGN_RIGHT, doubleBuffer);
}
void specialSetStrength(Special* s, int newStrength)
{
	s->strength = newStrength;
}

void deleteSpecial(Special* s) {
	deleteBitmap(s->special_bmp);
	free(s);
}
