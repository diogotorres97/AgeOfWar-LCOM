#include "tower.h"

/******************************* Tower functions *****************************************/

Tower *InitTower(int x, int hp, char *name_tower, int player) {

    Tower *t = (Tower *) malloc(sizeof(Tower));

    t->tower_bmp = loadBitmap(getImagePath(name_tower));


    t->x = x;

    t->hp = hp;
    t->player = player;
    t->width = t->tower_bmp->bitmapInfoHeader.width + 30; //+30, makes the enemy units stop before touching the tower
    t->height = t->tower_bmp->bitmapInfoHeader.height;
    t->y = InY - t->height;
    return t;
}

void drawTower(Tower *t, char *doubleBuffer, int life_max, int life_current) {


    if (t->player == 1) {
        vg_life_retangle(15, 250, 25, 300, life_max, life_current, doubleBuffer);
        bitmap_draw_transparency(t->tower_bmp, t->x, t->y, ALIGN_LEFT, doubleBuffer);
    } else {
        vg_life_retangle(989, 250, 25, 300, life_max, life_current, doubleBuffer);
        bitmap_draw_transparency(t->tower_bmp, t->x, t->y, ALIGN_RIGHT, doubleBuffer);
    }

}

void setTower(Tower *t, char *name_tower) {
    deleteBitmap(t->tower_bmp);
    t->tower_bmp = loadBitmap(getImagePath(name_tower));
    t->width = t->tower_bmp->bitmapInfoHeader.width;
    t->height = t->tower_bmp->bitmapInfoHeader.height;
    t->y = InY - t->height;
}


void towerSetHP(Tower *t, int newHP) {
    t->hp = newHP;
}

void deleteTower(Tower *t) {
    deleteBitmap(t->tower_bmp);
    free(t);
}
