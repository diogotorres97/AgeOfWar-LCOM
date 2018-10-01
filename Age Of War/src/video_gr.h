#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

/** @defgroup video_gr video_gr
* @{
*
* Functions for outputing data to screen in graphics mode
*/

/**
* @brief Initializes the video module in graphics mode
*
* Uses the VBE INT 0x10 interface to set the desired
*  graphics mode, maps VRAM to the process' address space and
*  initializes static global variables with the resolution of the screen,
*  and the number of colors
*
* @param mode 16-bit VBE mode to set
* @return Virtual address VRAM was mapped to. NULL, upon failure.
*/
void *vg_init(unsigned short mode);

/**
* @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
*
* @return 0 upon success, non-zero upon failure
*/
int vg_exit(void);

/**
* @brief gives the video mem
* @return buffer pointer
*/
void *getVideoMem();

/**
* @brief gives the screen buffer
* @return buffer pointer
*/

void *initDoubleBuffer();

/**
* @brief clear double buffer
* @return
*/
void clearDoubleBuffer(char *double_buffer);

/**
* @brief updates screen with the double buffer
* @return
*/
void updateScreenBuffer(char *double_buffer);

/**
* @brief clears video mem
* @return
*/
void clearVideoMem();

/**
 * @brief set 2 pixel in a specific buffer
 *
 * @param x
 * @param y
 * @param color
 * @param doubleBuffer
 * @return
 */
int vg_set_2pixel(unsigned short x, unsigned short y, unsigned long color, char *doubleBuffer);


/**
 * @brief draw a retangle in a specific buffer
 *
 * @param x
 * @param y
 * @param length
 * @param height
 * @param life_max
 * @param life_actual
 * @param doubleBuffer
 * @return
 */
int vg_life_retangle(unsigned short x, unsigned short y, float length, float height, float life_max, float life_actual,
                     char *doubleBuffer);

/** @} end of video_gr */

#endif /* __VIDEO_GR_H */
