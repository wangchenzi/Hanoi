#include "seqstack.h"

/*
	初始化一个栈
*/
Seqstack *Init_Seqstack(void)
{
	Seqstack *s = malloc(sizeof(Seqstack));
	s->top = -1;		//满栈
	

	return s;
}

/*
	销毁一个栈
*/
void Destory_Seqstack(Seqstack *s)
{
	s->top = -1;
	free(s);
}

/*
	清空栈
*/
void Clear_Seqstack(Seqstack *s)
{
	s->top = -1;
}

/*
	判断一个栈是否为空
		为空返回1,不为空返回0
*/
int Seqstack_Isempty(Seqstack *s)
{
	return (s->top == -1) ? 1 : 0;
}

/*
	返回栈中的元素的个数
*/	
int Seqstack_Len(Seqstack *s)
{
	return s->top + 1;
}

/*
	返回栈顶元素，但是不出栈
		获取成功返回1，获取失败返回0
*/
int Gettop(Seqstack *s,Elemtype *d)
{
	if(Seqstack_Isempty(s) || s == NULL)
	{
		return 0;
	}
	*d = s->data[s->top];
	return 1;
}

/*
	出栈
		s:代表栈      d:出栈元素要保存到哪里去
		出栈成功返回1，出栈失败返回0
*/
int Pop(Seqstack *s,Elemtype *d)
{
	if(s == NULL || s->top == -1)
	{
		return 0;
	}
	*d = s->data[s->top--];
	return 1;
}

/*	
	入栈
		s:代表栈      d:要入栈的元素
		入栈成功返回1，入栈失败返回0
*/
int Push(Seqstack *s,Elemtype d)
{
	if(s == NULL || s->top == MAX_NUM - 1)
	{
		return 0;
	}
	s->data[++s->top] = d;
	return 1;
}

