#ifndef __NUMBER_H
#define __NUMBER_H


#include <minix/syslib.h>
#include <minix/drivers.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "video_gr.h"
#include <time.h>
#include <math.h>
#include "const.h"

/** @defgroup Number Number
 * @{
 *
 * Functions that work with numbers
 */

typedef struct Number {


    int x;
    int y;
    int player;

    int width;
    int height;

    int no;

    Bitmap *n0_bmp;
    Bitmap *n1_bmp;
    Bitmap *n2_bmp;
    Bitmap *n3_bmp;
    Bitmap *n4_bmp;
    Bitmap *n5_bmp;
    Bitmap *n6_bmp;
    Bitmap *n7_bmp;
    Bitmap *n8_bmp;
    Bitmap *n9_bmp;

    Bitmap *nr0_bmp;
    Bitmap *nr1_bmp;
    Bitmap *nr2_bmp;
    Bitmap *nr3_bmp;
    Bitmap *nr4_bmp;
    Bitmap *nr5_bmp;
    Bitmap *nr6_bmp;
    Bitmap *nr7_bmp;
    Bitmap *nr8_bmp;
    Bitmap *nr9_bmp;

    Bitmap *ny0_bmp;
    Bitmap *ny1_bmp;
    Bitmap *ny2_bmp;
    Bitmap *ny3_bmp;
    Bitmap *ny4_bmp;
    Bitmap *ny5_bmp;
    Bitmap *ny6_bmp;
    Bitmap *ny7_bmp;
    Bitmap *ny8_bmp;
    Bitmap *ny9_bmp;

} Number;

/**
 * @brief initiates number object
 *
 * @param x - number position in x
 * @param y - number position in y
 * @param player - to which player (1 or 2) this tower belongs, it determines the unit orientation (left or right)
 * @param no - number to convert to image
 * @return pointer to the unit struct
 */
Number *InitNumber(int x, int y, int player, int no);

void setNumber(Number *n, int newNum);

/**
 * @brief draw number to the second buffer
 *
 * @param pointer to number
 * @param doubleBuffer
 * @param color of the number
 * @return
 */
void DrawNumber(Number *n, char *doubleBuffer, int color);

/**
 * @brief draw number to the second buffer
 *
 * @param pointer to number
 * @param digit to draw
 * @param color of the digit
 * @return
 */
void DrawDigit(Number *n, int digit, char *doubleBuffer, int color);

/**
 * @brief gives number of digits of a number
 *
 * @param number
 * @return number of digits
 */
unsigned int CountDigits(int no);


/**
 * @brief delete number
 *
 * @param pointer to number
 * @return
 */
void deleteNumber(Number *n);

/** @} end of Number */

#endif

