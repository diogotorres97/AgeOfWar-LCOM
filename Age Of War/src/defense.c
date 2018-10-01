#include "defense.h"

/******************************************** Defense functions *****************************************/

Defense *InitDefense(int x, int y, int strength, char *name_defense, int price, int player, int range) {
    Defense *d = (Defense *) malloc(sizeof(Defense));

    d->defense_bmp = loadBitmap(getImagePath(name_defense));

    d->bullets[0] = (Bullet *) malloc(sizeof(Bullet));
    d->bullets[0] = NULL;

    d->x = x;
    d->y = y;
    d->strength = strength;
    d->player = player;
    d->price = price;

    d->width = d->defense_bmp->bitmapInfoHeader.width;
    d->height = d->defense_bmp->bitmapInfoHeader.height;

    d->range = range;

    return d;
}

void DrawDefense(Defense *d, char *doubleBuffer) {
    if (d->player == 1)
        bitmap_draw_transparency(d->defense_bmp, d->x, d->y, ALIGN_LEFT, doubleBuffer);
    else
        bitmap_draw_transparency(d->defense_bmp, d->x, d->y, ALIGN_RIGHT, doubleBuffer);
}


void addBulletsDefense(Defense *d, Bullet *b) {
    d->bullets[0] = b;
}

int emptyBulletsDefenses(Defense *d) {
    if (d->bullets[0] == NULL)
        return 1;
    else
        return 0;
}

int fullBulletsDefenses(Defense *d) {
    if (d->bullets[0] != NULL)
        return 1;
    else
        return 0;
}

void removeBulletDefense(Defense *d) {
    d->bullets[0] = NULL;
}

void deleteDefense(Defense *d) {
    deleteBitmap(d->defense_bmp);
    free(d);
}
