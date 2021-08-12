#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "head.h"

#define TOUCH_PATH "/dev/input/event0"

//用于保存Touch_Start_Stop()的返回值，即起点和终点的横坐标
struct Point
{
    int x_start;
    int y_start;
    int x_stop;
    int y_stop;
};



int Get_Touch(void);

/*
	触点函数，获取起始触点以及最终触点
*/
struct Point Touch_Start_Stop(void);

  
/*  
	判断始触点在哪一区域
	需传入x_start的值
	返回柱子序数
*/	
int Area_Judge_Start(int x);

/*  
	判断最终触点在哪一区域
	需传入x_stop的值
	返回柱子序数
*/	                                                                            
int Area_Judge_Stop(int x);

/*
	touch区域判断，选择难度
	需传入struct Point结构体的值，成功返回初始化盘子数，失败返回1
*/
int Menu_Judge(struct Point p);

/*
	touch区域判断，菜单栏重新开始
	需传入struct Point结构体的值，成功返回0，失败返回-1
*/
int game_again(struct Point p);

#endif
