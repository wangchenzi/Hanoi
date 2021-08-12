#ifndef __SEQSTACK_H__
#define __SEQSTACK_H__


#include "head.h"


//栈中数据元素的类型
typedef int Elemtype;

//栈中最大的数据元素的个数
#define MAX_NUM 4096

typedef struct seqstack
{
	Elemtype data[MAX_NUM];			//用来保存数据元素
	int top;						//作为下标使用,指向栈顶元素(满栈)
}
Seqstack;

/*
	初始化一个栈
*/
Seqstack *Init_Seqstack(void);

/*
	销毁一个栈
*/
void Destory_Seqstack(Seqstack *s);

/*
	清空栈
*/
void Clear_Seqstack(Seqstack *s);

/*
	判断一个栈是否为空
		为空返回1,不为空返回0
*/
int Seqstack_Isempty(Seqstack *s);

/*
	返回栈中的元素的个数
*/	
int Seqstack_Len(Seqstack *s);

/*
	返回栈顶元素，但是不出栈
		获取成功返回1，获取失败返回0
*/
int Gettop(Seqstack *s,Elemtype *d);

/*
	出栈
		s:代表栈      d:出栈元素要保存到哪里去
		出栈成功返回1，出栈失败返回0
*/
int Pop(Seqstack *s,Elemtype *d);

/*	
	入栈
		s:代表栈      d:要入栈的元素
		入栈成功返回1，入栈失败返回0
*/
int Push(Seqstack *s,Elemtype d);

#endif

