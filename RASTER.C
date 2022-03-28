/*
Authors: Daniel Bahrami, Scott Charles
Instructor: Paul Pospisil

Purpose:
File Contains 5 functions, all of which interact with the frame buffer.
1) Clears the screen
2) Prints a vertical Line
3) Prints a horizontal Line
4) Plots Pixel
5) Plots Bitmap16
6) Darken the Screen

*/
#include <stdio.h>
#include <osbind.h>
#include "include/raster.h"


	
UINT16 whiteBlock16[16] = 
	{
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0000
	};
	
UINT16 blackBlock[16] = 
	{
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF,
		0xFFFF
	
	};

void plot_pixel(UINT16 *base, int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		*(base + y * 40 + (x >> 4)) |= (0x80 >> (x & 15));
}
void clearScreen(UINT16 *base)
{
	int x;
	int y;
	int height = 16;

	for(y = 0; y < SCREEN_HEIGHT; y+=16)
	{
		for(x = 208; x < 416; x+=16)
		{
			plot_bitmap_16(base,x ,y, whiteBlock16, height);
		}
	}
}

void verticalLine(UINT16 *base, int x, int fromY, int toY)
{
	int height = toY - fromY; 
	int offset = 0;
	int i = 0;
	int xCord = x;
	int yCord = fromY;
	for(i = 0; i < height; i++)
	{
			offset = (40 * yCord) + (xCord >> 4);
			*(base + offset + (40 * i)) =  0x0200 >> (xCord & 15);
			*(base + offset + (40 * i) + 1) =  0x0F00 << 16 - (xCord & 15);
	}
}

void plot_hline (UINT16 *base, int y, int x1, int x2)
{
	UINT16 p1, p2;
	int row1, row2, i;
	int shift_F, shift_B;

/*	row1 = x1 / BITS_IN_BYTE; */
	row1 = x1 >> TWO_CUBED;
/*	row2 = x2 / BITS_IN_BYTE; */
	row2 = x2 >> TWO_CUBED;
/*	shift_F = x1 % BITS_IN_BYTE; */
	shift_F = x1 & (BITS_IN_BYTE - 1);
/*	shift_B = (BITS_IN_BYTE - 1) - (x2 % BITS_IN_BYTE); */
	shift_B = (BITS_IN_BYTE - 1) - (x2 & (BITS_IN_BYTE-1));

	if (row1 == row2)
	{
		p1 = SOLID >> shift_F;
		p2 = SOLID << shift_B;
		*(base + y * 40 + row1) = p1 & p2;
	}
    else
    {
		p1 = SOLID >> shift_F;
		p2 = SOLID << shift_B;
		*(base + y * 40 + row1) = p1;
		for (i = row1 + 1; i < row2; i++)
		{
			*(base + y * 40 + i) = SOLID;
		}
		*(base + y * 40 + row2) = p2;
  }
  return;
}

void plot_vline (UINT16 *base, int x, int y1, int y2)
{
  int temp;
  
  if (y1 > y2)	
  {
	  temp = y1;
	  y1 = y2;
	  y2 = temp;
  }
  if (y1 < 0) y1 = 0;
  if (y2 > 399) y2 = 399;
  
  for ( ; y1 <= y2; y1++)
	  plot_pixel(base, x, y1);
  
  return;
}


void horizontalGap(UINT16 *base, int fromX, int toX, int y)
{
	int offset = 0;
	int i = 0;
	int xCord = fromX;
	int yCord = y;
	for(xCord = fromX; xCord < toX; xCord++)
	{
		offset = (40 * yCord) + (xCord >> 4);
		*(base + offset + (40 * i)) =  0x00000000;
	}
}



void plot_bitmap_16(UINT16 *base, int x, int y, UINT16 *bitmap, int height)
{
  int offset;
  int i;
  
  if(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
  {
		offset = ((40 * y) + (x >> 4));

		for (i = 0; i < height; i++)
		{
			*(base + offset + (40 * i)) = bitmap[i] >> (x & 15);
			*(base + offset + (40 * i) + 1) = bitmap[i] << 16 - (x & 15);
		}
  }
}



void plot_bitmap_32(UINT16 *base, int x, int y, UINT32 *bitmap, int height)
{
  int offset;
  int i;
  
  if(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
  {
		offset = ((20 * y) + (x >> 5));

		for (i = 0; i < height; i++)
		{
			*(base + offset + (20 * i)) = bitmap[i] >> (x & 31);
			*(base + offset + (20 * i) + 1) = bitmap[i] << 32 - (x & 31);
		}
  }
}
void plot_Borders(UINT16 *base, int x, int y, UINT16 *bitmap, int height)
{
	int offset;
	int i;
	int bShift;
  
  if(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
  {
		offset = ((40 * y) + (x >> 4));

		for (i = 0; i < height; i++)
		{
			offset = (40 * y) + (x >> 4);
			*(base + offset + (40 * i)) =  bitmap[i];
		}
  }
}



