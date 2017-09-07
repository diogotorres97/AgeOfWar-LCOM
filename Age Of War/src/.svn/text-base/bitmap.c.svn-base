#include "bitmap.h"

#include "stdio.h"
#include "video_gr.h"
#include "const.h"


Bitmap* loadBitmap(const char* filename) {
	// allocating necessary size
	Bitmap* bmp = (Bitmap*)malloc(sizeof(Bitmap));

	// open filename in read binary mode
	FILE *filePtr;
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// read the bitmap file header
	BitmapFileHeader bitmapFileHeader;
	fread(&bitmapFileHeader, 2, 1, filePtr);

	// verify that this is a bmp file by check bitmap id
	if (bitmapFileHeader.type != 0x4D42) {
		fclose(filePtr);
		return NULL;
	}

	int rd;
	do {
		if ((rd = fread(&bitmapFileHeader.size, 4, 1, filePtr)) != 1)
			break;
		if ((rd = fread(&bitmapFileHeader.reserved, 4, 1, filePtr)) != 1)
			break;
		if ((rd = fread(&bitmapFileHeader.offset, 4, 1, filePtr)) != 1)
			break;
	} while (0);

	if (rd = !1) {
		fprintf(stderr, "Error reading file\n");
		exit(-1);
	}

	// read the bitmap info header
	BitmapInfoHeader bitmapInfoHeader;
	fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePtr);

	// move file pointer to the begining of bitmap data
	fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

	// allocate enough memory for the bitmap image data
	unsigned char* bitmapImage = (unsigned char*)malloc(
		bitmapInfoHeader.imageSize);

	// verify memory allocation
	if (!bitmapImage) {
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImage, bitmapInfoHeader.imageSize, 1, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL) {
		fclose(filePtr);
		return NULL;
	}

	// close file and return bitmap image data
	fclose(filePtr);

	bmp->bitmapData = bitmapImage;
	bmp->bitmapInfoHeader = bitmapInfoHeader;

	return bmp;
}

void drawBitmap(Bitmap* bmp, int x, int y, Alignment alignment, char* buffer) {

	if (bmp == NULL)

		return;

	int width = bmp->bitmapInfoHeader.width;

	int drawWidth = width;

	int height = bmp->bitmapInfoHeader.height;

	if (alignment == ALIGN_CENTER)

		x -= width / 2;

	else if (alignment == ALIGN_RIGHT)

		x -= width;

	if (x + width < 0 || x > H_RES || y + height < 0

		|| y > V_RES)

		return;

	int xCorrection = 0;

	if (x < 0) {

		xCorrection = -x;

		drawWidth -= xCorrection;

		x = 0;

		if (drawWidth > H_RES)

			drawWidth = H_RES;

	}
	else if (x + drawWidth >= H_RES) {

		drawWidth = H_RES - x;

	}

	char* bufferStartPos;

	char* imgStartPos;

	int i;

	for (i = 0; i < height; i++) {

		int pos = y + height - 1 - i;

		if (pos < 0 || pos >= V_RES)

			continue;

		bufferStartPos = buffer;

		bufferStartPos += x * 2 + pos * H_RES * 2;

		imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;

		memcpy(bufferStartPos, imgStartPos, drawWidth * 2);

	}

}


void deleteBitmap(Bitmap* bmp) {
	if (bmp == NULL)
		return;

	free(bmp->bitmapData);
	free(bmp);
}

const char* getImagePath(const char* img)
{
	char num[256];
	sprintf(num, "/home/project/res/%s.bmp", img);
	char* str = (char*)malloc(256);
	strcpy(str, num);
	return str;
}

void bitmap_draw_transparency(Bitmap* bmp, int x, int y, Alignment alignment, char* buffer)
{
	if (bmp == NULL)

		return;

	int width = bmp->bitmapInfoHeader.width;

	int drawWidth = width;

	int height = bmp->bitmapInfoHeader.height;

	if (alignment == ALIGN_CENTER)

		x -= width / 2;

	else if (alignment == ALIGN_RIGHT)

		x -= width;

	if (x + width < 0 || x > H_RES || y + height < 0

		|| y > V_RES)

		return;

	int xCorrection = 0;

	if (x < 0) {

		xCorrection = -x;

		drawWidth -= xCorrection;

		x = 0;

		if (drawWidth > H_RES)

			drawWidth = H_RES;

	}
	else if (x + drawWidth >= H_RES) {

		drawWidth = H_RES - x;

	}

	char* bufferStartPos;
	char* imgStartPos;

	int i, j;


	for (i = 0; i < height; i++) {

		int pos = y + height - 1 - i;

		if (pos < 0 || pos >= V_RES)

			continue;

		bufferStartPos = buffer;
		bufferStartPos += x * 2 + (pos + 1) * H_RES * 2;

		for (j = 0; j < width * 2; j++, bufferStartPos++) {
			if (x + j < 0 || x * 2 + j >= H_RES * 2)
				continue;

			int pos = j + i * width * 2;
			unsigned short tmp1 = bmp->bitmapData[pos];
			unsigned short tmp2 = bmp->bitmapData[pos + 1];
			unsigned short temp = (tmp1 | (tmp2 << 8));

			if (temp != 0xF81F && temp!=0xD03A && temp!=0xB857 && temp!=0xB916 && temp!=0xC0D6 && temp!=0xD85B&&temp!=0xB133 && temp!=0xC897 && temp!=0xB151&&temp!=0xB171 && temp!=0xB113&& temp!=0xE83C && temp!=0xD85A && temp!=0xC0B8 && temp!=0xA894 && temp!=0xC839 && temp!= 0xD89B && temp!=0xA951 && temp!=0xC098 && temp!=0xB195 && temp!=0xE07B && temp!=0x9A2F && temp!=0x9A70 && temp!= 0x9291 && temp!=0xF01E && temp!=0xA931 && temp!=0x99D0 && temp!=0xB8B6 && temp!=0xA954 && temp !=0xB0F5 && temp!=0xD079) { //Pink Color in RGB565
				*bufferStartPos = bmp->bitmapData[j + i * width * 2];
				j++;
				bufferStartPos++;
				*bufferStartPos = bmp->bitmapData[j + i * width * 2];
			}
			else {
				j++;
				bufferStartPos++;
			}
		}
	}
}
