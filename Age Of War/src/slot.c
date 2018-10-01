#include "slot.h"

/******************************************** Slot functions *****************************************/

Slot *InitSlot(int x, int y, char *name_slot, int player, int first) {
    Slot *s = (Slot *) malloc(sizeof(Slot));

    s->slot_bmp = loadBitmap(getImagePath(name_slot));


    s->x = x;


    s->player = player;
    s->width = s->slot_bmp->bitmapInfoHeader.width;
    s->height = s->slot_bmp->bitmapInfoHeader.height;

    if (first) {
        s->y = y;
    } else {
        s->y = y - s->height;
    }


    return s;
}

void drawSlot(Slot *s, char *doubleBuffer) {
    if (s->player == 1)

        bitmap_draw_transparency(s->slot_bmp, s->x, s->y, ALIGN_LEFT, doubleBuffer);
    else
        bitmap_draw_transparency(s->slot_bmp, s->x, s->y, ALIGN_RIGHT, doubleBuffer);

}

void setSlot(Slot *s, char *name_slot, int x, int y) {

    deleteBitmap(s->slot_bmp);
    s->slot_bmp = loadBitmap(getImagePath(name_slot));
    s->width = s->slot_bmp->bitmapInfoHeader.width;
    s->height = s->slot_bmp->bitmapInfoHeader.height;
    s->x = x;
    s->y = y;
}

void deleteSlot(Slot *s) {
    deleteBitmap(s->slot_bmp);
    free(s);
}
