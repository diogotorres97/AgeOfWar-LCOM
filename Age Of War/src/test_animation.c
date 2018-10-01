#include "test_animation.h"

/******************************************** Animation functions *****************************************/

Animation *InitAnimation(int u1_id, int state) {
    Animation *anime = (Animation *) malloc(sizeof(Animation));
    char temp[25];
    switch (u1_id) {
        case 1: {
            strcpy(temp, "lvl1_1_l");
            switch (state) {
                case 0:
                    anime->counter = LVL1_1_A;
                    break;
                case 1:
                    anime->counter = LVL1_1_S;
                    break;
                case 2:
                    anime->counter = LVL1_1_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL1_1_D;
                    break;
            }
            break;
        }
        case 2: {
            strcpy(temp, "lvl1_1_r");
            switch (state) {
                case 0:
                    anime->counter = LVL1_1_A;
                    break;
                case 1:
                    anime->counter = LVL1_1_S;
                    break;
                case 2:
                    anime->counter = LVL1_1_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL1_1_D;
                    break;
            }
            break;
        }
        case 3: {
            strcpy(temp, "lvl1_2_l");
            switch (state) {
                case 0:
                    anime->counter = LVL1_2_A;
                    break;
                case 1:
                    anime->counter = LVL1_2_S;
                    break;
                case 2:
                    anime->counter = LVL1_2_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL1_2_D;
                    break;
            }
            break;
        }
        case 4: {
            strcpy(temp, "lvl1_2_r");
            switch (state) {
                case 0:
                    anime->counter = LVL1_2_A;
                    break;
                case 1:
                    anime->counter = LVL1_2_S;
                    break;
                case 2:
                    anime->counter = LVL1_2_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL1_2_D;
                    break;
            }
            break;
        }
        case 5: {
            strcpy(temp, "lvl1_3_l");
            switch (state) {
                case 0:
                    anime->counter = LVL1_3_A;
                    break;
                case 1:
                    anime->counter = LVL1_3_S;
                    break;
                case 2:
                    anime->counter = LVL1_3_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL1_3_D;
                    break;
            }
            break;
        }
        case 6: {
            strcpy(temp, "lvl1_3_r");
            switch (state) {
                case 0:
                    anime->counter = LVL1_3_A;
                    break;
                case 1:
                    anime->counter = LVL1_3_S;
                    break;
                case 2:
                    anime->counter = LVL1_3_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL1_3_D;
                    break;
            }
            break;
        }
        case 7: {
            strcpy(temp, "lvl2_1_l");
            switch (state) {
                case 0:
                    anime->counter = LVL2_1_A;
                    break;
                case 1:
                    anime->counter = LVL2_1_S;
                    break;
                case 2:
                    anime->counter = LVL2_1_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL2_1_D;
                    break;
            }
            break;
        }
        case 8: {
            strcpy(temp, "lvl2_1_r");
            switch (state) {
                case 0:
                    anime->counter = LVL2_1_A;
                    break;
                case 1:
                    anime->counter = LVL2_1_S;
                    break;
                case 2:
                    anime->counter = LVL2_1_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL2_1_D;
                    break;
            }
            break;
        }
        case 9: {
            strcpy(temp, "lvl2_2_l");
            switch (state) {
                case 0:
                    anime->counter = LVL2_2_A;
                    break;
                case 1:
                    anime->counter = LVL2_2_S;
                    break;
                case 2:
                    anime->counter = LVL2_2_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL2_2_D;
                    break;
            }
            break;
        }
        case 10: {
            strcpy(temp, "lvl2_2_r");
            switch (state) {
                case 0:
                    anime->counter = LVL2_2_A;
                    break;
                case 1:
                    anime->counter = LVL2_2_S;
                    break;
                case 2:
                    anime->counter = LVL2_2_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL2_2_D;
                    break;
            }
            break;
        }
        case 11: {
            strcpy(temp, "lvl2_3_l");
            switch (state) {
                case 0:
                    anime->counter = LVL2_3_A;
                    break;
                case 1:
                    anime->counter = LVL2_3_S;
                    break;
                case 2:
                    anime->counter = LVL2_3_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL2_3_D;
                    break;
            }
            break;
        }
        case 12: {
            strcpy(temp, "lvl2_3_r");
            switch (state) {
                case 0:
                    anime->counter = LVL2_3_A;
                    break;
                case 1:
                    anime->counter = LVL2_3_S;
                    break;
                case 2:
                    anime->counter = LVL2_3_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL2_3_D;
                    break;
            }
            break;
        }
        case 13: {
            strcpy(temp, "lvl3_1_l");
            switch (state) {
                case 0:
                    anime->counter = LVL3_1_A;
                    break;
                case 1:
                    anime->counter = LVL3_1_S;
                    break;
                case 2:
                    anime->counter = LVL3_1_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL3_1_D;
                    break;
            }
            break;
        }
        case 14: {
            strcpy(temp, "lvl3_1_r");
            switch (state) {
                case 0:
                    anime->counter = LVL3_1_A;
                    break;
                case 1:
                    anime->counter = LVL3_1_S;
                    break;
                case 2:
                    anime->counter = LVL3_1_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL3_1_D;
                    break;
            }
            break;
        }
        case 15: {
            strcpy(temp, "lvl3_2_l");
            switch (state) {
                case 0:
                    anime->counter = LVL3_2_A;
                    break;
                case 1:
                    anime->counter = LVL3_2_S;
                    break;
                case 2:
                    anime->counter = LVL3_2_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL3_2_D;
                    break;
            }
            break;
        }
        case 16: {
            strcpy(temp, "lvl3_2_r");
            switch (state) {
                case 0:
                    anime->counter = LVL3_2_A;
                    break;
                case 1:
                    anime->counter = LVL3_2_S;
                    break;
                case 2:
                    anime->counter = LVL3_2_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL3_2_D;
                    break;
            }
            break;
        }
        case 17: {
            strcpy(temp, "lvl3_3_l");
            switch (state) {
                case 0:
                    anime->counter = LVL3_3_A;
                    break;
                case 1:
                    anime->counter = LVL3_3_S;
                    break;
                case 2:
                    anime->counter = LVL3_3_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL3_3_D;
                    break;
            }
            break;
        }
        case 18: {
            strcpy(temp, "lvl3_3_r");
            switch (state) {
                case 0:
                    anime->counter = LVL3_3_A;
                    break;
                case 1:
                    anime->counter = LVL3_3_S;
                    break;
                case 2:
                    anime->counter = LVL3_3_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL3_3_D;
                    break;
            }
            break;
        }
        case 19: {
            strcpy(temp, "lvl4_1_l");
            switch (state) {
                case 0:
                    anime->counter = LVL4_1_A;
                    break;
                case 1:
                    anime->counter = LVL4_1_S;
                    break;
                case 2:
                    anime->counter = LVL4_1_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL4_1_D;
                    break;
            }
            break;
        }
        case 20: {
            strcpy(temp, "lvl4_1_r");
            switch (state) {
                case 0:
                    anime->counter = LVL4_1_A;
                    break;
                case 1:
                    anime->counter = LVL4_1_S;
                    break;
                case 2:
                    anime->counter = LVL4_1_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL4_1_D;
                    break;
            }
            break;
        }
        case 21: {
            strcpy(temp, "lvl4_2_l");
            switch (state) {
                case 0:
                    anime->counter = LVL4_2_A;
                    break;
                case 1:
                    anime->counter = LVL4_2_S;
                    break;
                case 2:
                    anime->counter = LVL4_2_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL4_2_D;
                    break;
            }
            break;
        }
        case 22: {
            strcpy(temp, "lvl4_2_r");
            switch (state) {
                case 0:
                    anime->counter = LVL4_2_A;
                    break;
                case 1:
                    anime->counter = LVL4_2_S;
                    break;
                case 2:
                    anime->counter = LVL4_2_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL4_2_D;
                    break;
            }
            break;
        }
        case 23: {
            strcpy(temp, "lvl4_3_l");
            switch (state) {
                case 0:
                    anime->counter = LVL4_3_A;
                    break;
                case 1:
                    anime->counter = LVL4_3_S;
                    break;
                case 2:
                    anime->counter = LVL4_3_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL4_3_D;
                    break;
            }
            break;
        }
        case 24: {
            strcpy(temp, "lvl4_3_r");
            switch (state) {
                case 0:
                    anime->counter = LVL4_3_A;
                    break;
                case 1:
                    anime->counter = LVL4_3_S;
                    break;
                case 2:
                    anime->counter = LVL4_3_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL4_3_D;
                    break;
            }
            break;
        }
        case 25: {
            strcpy(temp, "lvl5_1_l");
            switch (state) {
                case 0:
                    anime->counter = LVL5_1_A;
                    break;
                case 1:
                    anime->counter = LVL5_1_S;
                    break;
                case 2:
                    anime->counter = LVL5_1_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL5_1_D;
                    break;
            }
            break;
        }
        case 26: {
            strcpy(temp, "lvl5_1_r");
            switch (state) {
                case 0:
                    anime->counter = LVL5_1_A;
                    break;
                case 1:
                    anime->counter = LVL5_1_S;
                    break;
                case 2:
                    anime->counter = LVL5_1_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL5_1_D;
                    break;
            }
            break;
        }
        case 27: {
            strcpy(temp, "lvl5_2_l");
            switch (state) {
                case 0:
                    anime->counter = LVL5_2_A;
                    break;
                case 1:
                    anime->counter = LVL5_2_S;
                    break;
                case 2:
                    anime->counter = LVL5_2_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL5_2_D;
                    break;
            }
            break;
        }
        case 28: {
            strcpy(temp, "lvl5_2_r");
            switch (state) {
                case 0:
                    anime->counter = LVL5_2_A;
                    break;
                case 1:
                    anime->counter = LVL5_2_S;
                    break;
                case 2:
                    anime->counter = LVL5_2_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL5_2_D;
                    break;
            }
            break;
        }
        case 29: {
            strcpy(temp, "lvl5_3_l");
            switch (state) {
                case 0:
                    anime->counter = LVL5_3_A;
                    break;
                case 1:
                    anime->counter = LVL5_3_S;
                    break;
                case 2:
                    anime->counter = LVL5_3_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL5_3_D;
                    break;
            }
            break;
        }
        case 30: {
            strcpy(temp, "lvl5_3_r");
            switch (state) {
                case 0:
                    anime->counter = LVL5_3_A;
                    break;
                case 1:
                    anime->counter = LVL5_3_S;
                    break;
                case 2:
                    anime->counter = LVL5_3_M;
                    break;
                case 3:
                    anime->counter = 1;
                    break;
                case 4:
                    anime->counter = LVL5_3_D;
                    break;
            }
            break;
        }
    }


    anime->sprites = (Bitmap **) malloc(anime->counter * sizeof(Bitmap *));
    int i;
    for (i = 0; i < anime->counter; i++) {
        anime->sprites[i] = loadBitmap(getImagePathAnimation(temp, state, i + 1));
    }


    return anime;
}

void drawAnimation(Animation *anime, int x, int y, int position, char *doubleBuffer, int counter) {

    int calculator;
    calculator = counter % anime->counter;
    if (position == 0)
        bitmap_draw_transparency(anime->sprites[calculator], x, y, ALIGN_LEFT, doubleBuffer);
    else
        bitmap_draw_transparency(anime->sprites[calculator], x, y, ALIGN_RIGHT, doubleBuffer);


}

void deleteAnimation(Animation *anime) {


    int i = 0;
    for (; i < anime->counter; i++) {
        deleteBitmap(anime->sprites[i]);
    }


    free(anime);
}

const char *getImagePathAnimation(char *path, unsigned int state, unsigned int count) {


    char temp[1];

    switch (state) {
        case 0:
            temp[0] = 'a';
            break;
        case 1:
            temp[0] = 's';
            break;
        case 2:
            temp[0] = 'm';
            break;
        case 3:
            temp[0] = 't';
            break;
        case 4:
            temp[0] = 'd';
            break;
        default:
            return NULL;
            break;
    }

    char num[256];
    sprintf(num, "/home/project/res/%s/%s_%c%d.bmp", path, path, temp[0], count);
    char *str = (char *) malloc(256);
    strcpy(str, num);
    return str;

}
