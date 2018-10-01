#include "unit.h"

/******************************* Unit functions *****************************************/

Unit *InitUnit(int x, int hp, int strength, int type, char *name_unit,
               int price, int exp_for_killing, int player, int id) {

    Unit *u = (Unit *) malloc(sizeof(Unit));


    char buf[32];
    sprintf(buf, "%s/%s_t1", name_unit, name_unit);
    u->unit_bmp = loadBitmap(getImagePath(buf));

    u->bullets[0] = (Bullet *) malloc(sizeof(Bullet));
    u->bullets[0] = NULL;


    u->x = x;

    u->vel = Unit_Speed;
    u->hp = hp;
    u->strength = strength;
    u->type = type;
    u->price = price;
    u->reward_for_killing = price * (3.0 / 4);
    u->exp_for_killing = exp_for_killing;
    u->player = player;
    u->width = u->unit_bmp->bitmapInfoHeader.width;
    u->height = u->unit_bmp->bitmapInfoHeader.height;
    u->y = In_Units_Y - u->height;
    u->id = id;


    u->name_unit = name_unit;

    if (u->type == 1)
        u->range = Unit_Range;

    u->killed = 0;
    u->UnitS = standing;


    u->UnitAnime_A = InitAnimation(u->id, 0);
    if (u->type == 1) {
        u->UnitAnime_S = InitAnimation(u->id, 1);
    }
    u->UnitAnime_M = InitAnimation(u->id, 2);
    u->UnitAnime_D = InitAnimation(u->id, 4);

    return u;


}

void MoveUnit(Unit *u) {
    if (u->player == 1)
        u->x += u->vel;
    else
        u->x -= u->vel;
}

void DrawUnit(Unit *u, char *doubleBuffer, int counter) {
    if (u->player == 1) {
        switch (u->UnitS) {
            case 0:
                u->y = In_Units_Y - u->UnitAnime_A->sprites[0]->bitmapInfoHeader.height;
                drawAnimation(u->UnitAnime_A, u->x, u->y, 0, doubleBuffer, counter);
                break;
            case 1:
                u->y = In_Units_Y - u->UnitAnime_S->sprites[0]->bitmapInfoHeader.height;
                drawAnimation(u->UnitAnime_S, u->x, u->y, 0, doubleBuffer, counter);
                break;
            case 2:
                u->y = In_Units_Y - u->UnitAnime_M->sprites[0]->bitmapInfoHeader.height;
                drawAnimation(u->UnitAnime_M, u->x, u->y, 0, doubleBuffer, counter);
                break;
            case 3:
                bitmap_draw_transparency(u->unit_bmp, u->x, u->y, ALIGN_LEFT, doubleBuffer);
                break;
            case 4:
                u->y = In_Units_Y - u->UnitAnime_D->sprites[0]->bitmapInfoHeader.height;
                drawAnimation(u->UnitAnime_D, u->x, u->y, 0, doubleBuffer, counter);
                break;
        }
    } else
        switch (u->UnitS) {
            case 0:
                u->y = In_Units_Y - u->UnitAnime_A->sprites[0]->bitmapInfoHeader.height;
                drawAnimation(u->UnitAnime_A, u->x, u->y, 1, doubleBuffer, counter);
                break;
            case 1:
                u->y = In_Units_Y - u->UnitAnime_S->sprites[0]->bitmapInfoHeader.height;
                drawAnimation(u->UnitAnime_S, u->x, u->y, 1, doubleBuffer, counter);
                break;
            case 2:
                u->y = In_Units_Y - u->UnitAnime_M->sprites[0]->bitmapInfoHeader.height;
                drawAnimation(u->UnitAnime_M, u->x, u->y, 1, doubleBuffer, counter);
                break;
            case 3:
                bitmap_draw_transparency(u->unit_bmp, u->x, u->y, ALIGN_RIGHT, doubleBuffer);
                break;
            case 4:
                u->y = In_Units_Y - u->UnitAnime_D->sprites[0]->bitmapInfoHeader.height;
                drawAnimation(u->UnitAnime_D, u->x, u->y, 1, doubleBuffer, counter);
                break;
        }


}

void addBulletsUnits(Unit *u, Bullet *b) {
    u->bullets[0] = b;
}


int emptyBulletsUnits(Unit *u) {
    if (u->bullets[0] == NULL)
        return 1;
    else
        return 0;
}

int fullBulletsUnits(Unit *u) {
    if (u->bullets[0] != NULL)
        return 1;
    else
        return 0;
}

void removeBulletUnit(Unit *u) {
    u->bullets[0] = NULL;
}

void unitSetHP(Unit *u, int new_hp) {
    u->hp = new_hp;
}


void deleteUnit(Unit *u) {

    deleteAnimation(u->UnitAnime_A);
    deleteAnimation(u->UnitAnime_S);
    deleteAnimation(u->UnitAnime_M);
    deleteAnimation(u->UnitAnime_D);
    deleteBitmap(u->unit_bmp);
    free(u);
}
