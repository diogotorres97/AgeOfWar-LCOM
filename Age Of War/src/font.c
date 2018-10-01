#include "font.h"

/******************************************** Font functions *****************************************/

Font *InitFont() {
    Font *font = (Font *) malloc(sizeof(Font));
    if (font == NULL)
        return NULL;
    font->character = NULL;
}

void drawChar(Font *font, char ch, int x, int y, char *doubleBuffer) {

    char buf[32];
    ch = toupper(ch);
    sprintf(buf, "font/%c", ch);
    font->character = loadBitmap(getImagePath(buf));
    bitmap_draw_transparency(font->character, x, y, ALIGN_LEFT, doubleBuffer);
}

void drawText(Font *font, char text[], int x, int y, char *doubleBuffer) {
    char *labelPtr;
    labelPtr = text;
    int i = 0;
    for (i; i < strlen(text); i++) {
        drawChar(font, labelPtr[i], x, y, doubleBuffer);
        x += 20;
    }
}

Font *deleteFont(Font *font) {
    deleteBitmap(font->character);
}


DateFont *InitDateFont() {
    DateFont *f = (DateFont *) malloc(sizeof(DateFont));
    f->numbers = (Bitmap **) malloc(12 * sizeof(Bitmap *));

    int i;
    for (i = 0; i < 12; i++) {
        char buf[10];
        sprintf(buf, "font/s%d", i);
        f->numbers[i] = loadBitmap(getImagePath(buf));
        memset(&buf[0], 0, sizeof(buf));
    }

    return f;
}

void drawDateChar(DateFont *f, int number, int x, int y, char *doubleBuffer) {

    drawBitmap(f->numbers[number], x, y, ALIGN_LEFT, doubleBuffer);

}

void deleteDateFont(DateFont *f) {
    int i = 0;
    for (; i < 12; i++) {
        deleteBitmap(f->numbers[i]);
    }
    free(f);
}
