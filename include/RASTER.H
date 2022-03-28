/*
Authors: Daniel Bahrami, Scott Charles
Instructor: Paul Pospisil
*/
#ifndef RASTER_H
#define RASTER_H
#include "types.h"
#include "constant.h"
void clearScreen(UINT16 *base);
void verticalLine(UINT16 *base, int x, int fromY, int toY);

void plot_bitmap_16(UINT16 *base, int x, int y, UINT16 *bitmap, int height);
void plot_bitmap_32(UINT16 *base, int x, int y, UINT32 *bitmap, int height);
void plot_Borders(UINT16 *base, int x, int y, UINT16 *bitmap, int height);

/*
Purpose: Prints the gap for the platforms.
*/
void horizontalGap(UINT16 *base, int fromX, int toX, int y);

/*
Plots Horizontal Line.
*/
void plot_hline (UINT16 *base, int y, int x1, int x2);
/*
Plots Vertical Line.
*/
void plot_vline (UINT16 *base, int x, int y1, int y2);

/*
Plots Pixel.
*/
void plot_pixel(UINT16 *base, int x, int y);



#endif
