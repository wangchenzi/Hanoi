#ifndef __LCD_H__
#define __LCD_H__

#include "head.h"

//屏幕文件的路径
#define LCD_PATH 	"/dev/fb0"

//屏幕文件的宽度
#define LCD_WIDTH 	800
//屏幕文件的高度
#define LCD_HEIGHT 	480

/*
	对LCD屏幕的初始化
		初始化成功返回0,失败返回-1
*/
int Lcd_Init(void);

/*
	画点函数:将(x,y)处的像素点显示成color颜色
*/
void Lcd_Draw_Point(int x,int y,int color);

/*
	画矩形:以(x0,y0)处为起始点画一个宽为w高为h颜色为color的矩形
*/
void Lcd_Draw_Orth(int x0,int y0,int w,int h,int color);

/*
	LCD的解初始化函数
*/
void Lcd_Uinit(void);

/*
	将屏幕分成垂直水平四个矩形
*/
void four_square(void);

/*
	将屏幕分成对角线四个三角形
*/
void diagonal(void);
/*
	彩虹
*/
void rainbow(void);
/*
	太极
*/
void taiji(void);
#endif

