#ifndef __GAME_H__
#define __GAME_H__

#include "head.h"
#include "bmp.h"
#include "seqstack.h"
#include "touch.h"

struct Panzi
{
    int n;		//盘子的权
    int x;		//盘子的左上角x坐标
    int y;		//盘子的左上角y坐标
    int width;	//盘子的宽
    int height;	//盘子的高
};
struct Bag
{
    int value;
    Seqstack *name; 
};



void game_init(void);

#endif

