#ifndef __FONT_H
#define __FONT_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "video_gr.h"
#include <ctype.h>

/** @defgroup Font Font
 * @{
 *
 * Functions related to the font system used for variable text
 */

typedef struct {
	Bitmap* character;
} Font;

typedef struct {
	Bitmap** numbers;
} DateFont;

/**
 * @brief Initiates of Font struct
 *
 * @param
 * @return pointer to the font struct
 */
Font* InitFont();

/**
 * @brief this function draws on the buffer the char passed as arg
 *
 * @param font pointer to struct Font
 * @param ch char to be wrote
 * @param x x position
 * @param y y position
 * @param doubleBuffer buffer to be drawn to
 * @return
 */
void drawChar(Font *font, char ch, int x, int y,char* doubleBuffer);

/**
 * @brief this function draws on the buffer the text passed as arg. In order to do this it calls the function draw char to each character in the text
 *
 * @param font pointer to struct Font
 * @param text text to be wrote
 * @param x x position
 * @param y y position
 * @param doubleBuffer buffer to be drawn to
 * @return
 */
void drawText(Font *font, char text[], int x, int y,char* doubleBuffer);

/**
 * @brief free all resources used by the Font struct
 *
 * @param pointer to struct font
 * @return
 */
Font* deleteFont(Font* font);

/**
 * @brief Initiates date
 * @return
 */
DateFont* InitDateFont() ;

/**
 * @brief Draws a date's char
 *
 * @param f pointer to struct DateFont
 * @param number
 * @param x x position
 * @param y y position
 * @param doubleBuffer buffer to be drawn to
 * @return
 */
void drawDateChar(DateFont *f, int number, int x, int y, char* doubleBuffer);
/**
 * @brief free all resources used by the DateFont struct
 *
 * @param f
 * @return
 */
void deleteDateFont(DateFont* f);

/** @} end of Font */

#endif
