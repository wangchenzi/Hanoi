#ifndef __BMP_H__
#define __BMP_H__

#include "head.h"
#include "lcd.h"


//#define Bmppath "/bz/Project/bmp"

int Display_Bmp(int x0, int y0, const char *bmppath);
int Display_Bmp_cover(int x0,int y0,const char *bmppath,int Height,int Width);
void show_num(int count);

#endif