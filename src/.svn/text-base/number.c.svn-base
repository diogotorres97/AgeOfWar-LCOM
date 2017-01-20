#include "number.h"

/******************************************** Number functions *****************************************/

Number* InitNumber(int x, int y, int player, int no)
{
	Number *n = (Number *)malloc(sizeof(Number));

	n->n0_bmp = loadBitmap(getImagePath("0"));
	n->n1_bmp = loadBitmap(getImagePath("1"));
	n->n2_bmp = loadBitmap(getImagePath("2"));
	n->n3_bmp = loadBitmap(getImagePath("3"));
	n->n4_bmp = loadBitmap(getImagePath("4"));
	n->n5_bmp = loadBitmap(getImagePath("5"));
	n->n6_bmp = loadBitmap(getImagePath("6"));
	n->n7_bmp = loadBitmap(getImagePath("7"));
	n->n8_bmp = loadBitmap(getImagePath("8"));
	n->n9_bmp = loadBitmap(getImagePath("9"));

	n->nr0_bmp = loadBitmap(getImagePath("r0"));
	n->nr1_bmp = loadBitmap(getImagePath("r1"));
	n->nr2_bmp = loadBitmap(getImagePath("r2"));
	n->nr3_bmp = loadBitmap(getImagePath("r3"));
	n->nr4_bmp = loadBitmap(getImagePath("r4"));
	n->nr5_bmp = loadBitmap(getImagePath("r5"));
	n->nr6_bmp = loadBitmap(getImagePath("r6"));
	n->nr7_bmp = loadBitmap(getImagePath("r7"));
	n->nr8_bmp = loadBitmap(getImagePath("r8"));
	n->nr9_bmp = loadBitmap(getImagePath("r9"));

	n->ny0_bmp = loadBitmap(getImagePath("y0"));
	n->ny1_bmp = loadBitmap(getImagePath("y1"));
	n->ny2_bmp = loadBitmap(getImagePath("y2"));
	n->ny3_bmp = loadBitmap(getImagePath("y3"));
	n->ny4_bmp = loadBitmap(getImagePath("y4"));
	n->ny5_bmp = loadBitmap(getImagePath("y5"));
	n->ny6_bmp = loadBitmap(getImagePath("y6"));
	n->ny7_bmp = loadBitmap(getImagePath("y7"));
	n->ny8_bmp = loadBitmap(getImagePath("y8"));
	n->ny9_bmp = loadBitmap(getImagePath("y9"));

	n->x = x;
	n->y = y;
	n->width = n->n0_bmp->bitmapInfoHeader.width;
	n->height = n->n0_bmp->bitmapInfoHeader.height;


	n->no = no;

	return n;

}

void setNumber(Number* n, int newNum)
{
	n->no = newNum;
}

void DrawNumber(Number *n, char* doubleBuffer, int color)
{

	if(color==1)
	{
		n->width=n->nr0_bmp->bitmapInfoHeader.width;
		n->height=n->nr0_bmp->bitmapInfoHeader.height;
	}
	else
	{
		n->width=n->n0_bmp->bitmapInfoHeader.width;
		n->height=n->n0_bmp->bitmapInfoHeader.height;
	}

	int number_digits = CountDigits(n->no);

	int x_aux = n->x;
	int aux_no = n->no;
	if (n->no == 0)
	{
		DrawDigit(n, n->no, doubleBuffer,color);

	}
	else
	{

		int i = 0;
		int div;
		for (div = 1; div <= aux_no; div *= 10)
			;

		while (i < number_digits)
		{
			div /= 10;

			DrawDigit(n, aux_no / div, doubleBuffer, color);
			aux_no %= div;
			n->x += n->width;

			i++;
		}

	}
	n->x = x_aux;


}

void DrawDigit(Number *n, int digit, char* doubleBuffer, int color)
{
	switch(color)
	{
	case 0:
		switch (digit)
		{
		case 0:
			bitmap_draw_transparency(n->n0_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
			break;
		case 1:
			bitmap_draw_transparency(n->n1_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
			break;
		case 2:
			bitmap_draw_transparency(n->n2_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
			break;
		case 3:
			bitmap_draw_transparency(n->n3_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
			break;
		case 4:
			bitmap_draw_transparency(n->n4_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
			break;
		case 5:
			bitmap_draw_transparency(n->n5_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
			break;
		case 6:
			bitmap_draw_transparency(n->n6_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
			break;
		case 7:
			bitmap_draw_transparency(n->n7_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
			break;
		case 8:
			bitmap_draw_transparency(n->n8_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
			break;
		case 9:
			bitmap_draw_transparency(n->n9_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
			break;

		}
		break;

		case 1:
			switch (digit)
			{
			case 0:
				bitmap_draw_transparency(n->nr0_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
				break;
			case 1:
				bitmap_draw_transparency(n->nr1_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
				break;
			case 2:
				bitmap_draw_transparency(n->nr2_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
				break;
			case 3:
				bitmap_draw_transparency(n->nr3_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
				break;
			case 4:
				bitmap_draw_transparency(n->nr4_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
				break;
			case 5:
				bitmap_draw_transparency(n->nr5_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
				break;
			case 6:
				bitmap_draw_transparency(n->nr6_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
				break;
			case 7:
				bitmap_draw_transparency(n->nr7_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
				break;
			case 8:
				bitmap_draw_transparency(n->nr8_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
				break;
			case 9:
				bitmap_draw_transparency(n->nr9_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
				break;

			}
			break;
			case 2:
				switch (digit)
				{
				case 0:
					bitmap_draw_transparency(n->ny0_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
					break;
				case 1:
					bitmap_draw_transparency(n->ny1_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
					break;
				case 2:
					bitmap_draw_transparency(n->ny2_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
					break;
				case 3:
					bitmap_draw_transparency(n->ny3_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
					break;
				case 4:
					bitmap_draw_transparency(n->ny4_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
					break;
				case 5:
					bitmap_draw_transparency(n->ny5_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
					break;
				case 6:
					bitmap_draw_transparency(n->ny6_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
					break;
				case 7:
					bitmap_draw_transparency(n->ny7_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
					break;
				case 8:
					bitmap_draw_transparency(n->ny8_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
					break;
				case 9:
					bitmap_draw_transparency(n->ny9_bmp, n->x, n->y, ALIGN_LEFT, doubleBuffer);
					break;

				}
				break;
	}

}

unsigned int CountDigits(int no) {
	unsigned int ret = 1;
	while (no /= 10) ret++;
	return ret;
}


void deleteNumber(Number *n)
{
	deleteBitmap(n->n0_bmp);
	deleteBitmap(n->n1_bmp);
	deleteBitmap(n->n2_bmp);
	deleteBitmap(n->n3_bmp);
	deleteBitmap(n->n4_bmp);
	deleteBitmap(n->n5_bmp);
	deleteBitmap(n->n6_bmp);
	deleteBitmap(n->n7_bmp);
	deleteBitmap(n->n8_bmp);
	deleteBitmap(n->n9_bmp);

	deleteBitmap(n->nr0_bmp);
	deleteBitmap(n->nr1_bmp);
	deleteBitmap(n->nr2_bmp);
	deleteBitmap(n->nr3_bmp);
	deleteBitmap(n->nr4_bmp);
	deleteBitmap(n->nr5_bmp);
	deleteBitmap(n->nr6_bmp);
	deleteBitmap(n->nr7_bmp);
	deleteBitmap(n->nr8_bmp);
	deleteBitmap(n->nr9_bmp);

	deleteBitmap(n->ny0_bmp);
	deleteBitmap(n->ny1_bmp);
	deleteBitmap(n->ny2_bmp);
	deleteBitmap(n->ny3_bmp);
	deleteBitmap(n->ny4_bmp);
	deleteBitmap(n->ny5_bmp);
	deleteBitmap(n->ny6_bmp);
	deleteBitmap(n->ny7_bmp);
	deleteBitmap(n->ny8_bmp);
	deleteBitmap(n->ny9_bmp);

	free(n);
}
