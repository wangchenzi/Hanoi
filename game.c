#include "game.h"
/*
	项目相关的主逻辑函数
*/
void game_init(void)
{
	
	Display_Bmp(0,0,"/lxy/wang/allbmp/timi.bmp");
	

	
	if (Get_Touch())
	{
	//背景
		
		Display_Bmp(0,0,"/lxy/wang/allbmp/bg.bmp");
	}
	
	start:
	Display_Bmp(0,0,"/lxy/wang/allbmp/bg.bmp");
	
	struct Point point;
	point = Touch_Start_Stop();
	
	

	int NUM = Menu_Judge(point);
	if (game_again(point) == 0 || (NUM!=3 && NUM!=5 && NUM!=7))
	{
		goto start;
	}

	

	Seqstack *s1 = Init_Seqstack();
	Seqstack *s2 = Init_Seqstack();
	Seqstack *s3 = Init_Seqstack();
	struct Panzi panzi[NUM];
	struct Bag bag;
	int i;
	int width = 140;
	int height = 30;
	int n[3];
	int top = -1;
	int count = 0;
	char bmp_buf[512];
	char bg[512];
	
	show_num(count);
	for(i = 0;i < NUM;i++)
	{
		panzi[i].n = i;//盘子的权值为数组下标
		panzi[i].width = 80 + 10*i;
		panzi[i].height = 30;
		panzi[i].x = 100 - (panzi[i].width/2);
		panzi[i].y = 480 - 60 - 30*(NUM-i);
	}

	for(i = 0;i < NUM;i++)
	{
		sprintf(bg,"/lxy/wang/allbmp/p%d.bmp",i);
		Display_Bmp(panzi[i].x,panzi[i].y,bg);
	}

	//权值大盘子大先入栈
	for(i = NUM-1;i >= 0;i--)
	{
		Push(s1,panzi[i].n);
	}
	
	
	while(1)
	{
		//判断起始盘子

		point = Touch_Start_Stop();

		if(game_again(point) == 0)
		{
			goto start;
		}
		if(Area_Judge_Start(point.x_start) == 1)
		{
	
			//判断起始柱子是否有盘子
			if(Seqstack_Len(s1) == 0)
			{
				//没有的话此步重开
				continue;
			}
	
			//有的话将栈顶元素出栈
			Pop(s1,&bag.value);
			bag.name = s1;
	
			//将原盘子位置显示背景

	
			Display_Bmp_cover(panzi[bag.value].x,panzi[bag.value].y,"/lxy/wang/allbmp/bg.bmp",height,width);
	
		}
		else if(Area_Judge_Start(point.x_start) == 2)
		{	
			//判断起始柱子是否有盘子
			if(Seqstack_Len(s2) == 0)
			{
				//没有的话此步重开
				continue;
			}
			//有的话将栈顶元素出栈
			Pop(s2,&bag.value);
			bag.name = s2;
			//将原盘子位置显示背景
			Display_Bmp_cover(panzi[bag.value].x,panzi[bag.value].y,"/lxy/wang/allbmp/bg.bmp",height,width);
		}
		else if(Area_Judge_Start(point.x_start) == 3)
		{
			//判断起始柱子是否有盘子
			if(Seqstack_Len(s3) == 0)
			{
				//没有的话此步重开
				continue;
			}
			//有的话将栈顶元素出栈
			Pop(s3,&bag.value);
			bag.name = s3;
			//将原盘子位置显示背景
			Display_Bmp_cover(panzi[bag.value].x,panzi[bag.value].y,"/lxy/wang/allbmp/bg.bmp",height,width);
		}


		//判断终点柱子
		if(Area_Judge_Stop(point.x_stop) == 1)
		{	
	
			//判断终点柱子是否有盘子
			if(Seqstack_Len(s1) == 0)
			{
				//没有的话将"盘子"置为最大
				top = 10;
			}
			else
			{	
				//有的话读取栈顶(最小盘子)的权
				Gettop(s1,&top);
			}
			//如果将入栈盘子的权小于入栈栈顶盘子的权
			if(bag.value < top)
			{
				//将小盘子入栈
				Push(s1,bag.value);
				//通过判断栈顶元素个数选择放置位置
				panzi[bag.value].x = 100 - (panzi[bag.value].width/2);;
				panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s1));
		
				sprintf(bmp_buf,"/lxy/wang/allbmp/p%d.bmp",bag.value);
		
				Display_Bmp(panzi[bag.value].x,panzi[bag.value].y,bmp_buf);
			}
			else
			{
				//如果将入栈盘子的权
				//大于入栈栈顶盘子的权的话
				//此步重开
				Push(bag.name,bag.value);
				//通过判断栈顶元素个数选择放置位置
				if(bag.name == s1)
				{
					panzi[bag.value].x = 100 - (panzi[bag.value].width/2);;
					panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s1));
				}
				if(bag.name == s2)
				{
					panzi[bag.value].x = 300 - (panzi[bag.value].width/2);;
					panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s2));
				}
				if(bag.name == s3)
				{
					panzi[bag.value].x = 500 - (panzi[bag.value].width/2);;
					panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s3));
				}
				
				sprintf(bmp_buf,"/lxy/wang/allbmp/p%d.bmp",bag.value);
		
				Display_Bmp(panzi[bag.value].x,panzi[bag.value].y,bmp_buf);
			}
			count++;
			show_num(count);

		}

		if(Area_Judge_Stop(point.x_stop) == 2)
		{
	
			//判断终点柱子是否有盘子
			if(Seqstack_Len(s2) == 0)
			{
				//没有的话将"盘子"置为最大
				top = 10;
			}
			else
			{
		
				//有的话读取栈顶(最小盘子)的权
				Gettop(s2,&top);
			}
			//如果将入栈盘子的权小于入栈栈顶盘子的权
	
			if(bag.value < top)
			{
		
				//将小盘子入栈
				Push(s2,bag.value);
				//通过判断栈顶元素个数选择放置位置
				panzi[bag.value].x = 300 - (panzi[bag.value].width/2);;
				panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s2));
		
				sprintf(bmp_buf,"/lxy/wang/allbmp/p%d.bmp",bag.value);
		
				Display_Bmp(panzi[bag.value].x,panzi[bag.value].y,bmp_buf);
			}
			else
			{
				//如果将入栈盘子的权
				//大于入栈栈顶盘子的权的话
				//此步重开
				Push(bag.name,bag.value);
				//通过判断栈顶元素个数选择放置位置
				if(bag.name == s1)
				{
					panzi[bag.value].x = 100 - (panzi[bag.value].width/2);;
					panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s1));
				}
				if(bag.name == s2)
				{
					panzi[bag.value].x = 300 - (panzi[bag.value].width/2);;
					panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s2));
				}
				if(bag.name == s3)
				{
					panzi[bag.value].x = 500 - (panzi[bag.value].width/2);;
					panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s3));
				}
		
				sprintf(bmp_buf,"/lxy/wang/allbmp/p%d.bmp",bag.value);
		
				Display_Bmp(panzi[bag.value].x,panzi[bag.value].y,bmp_buf);
			}
			count++;
			show_num(count);
		}
		if(Area_Judge_Stop(point.x_stop) == 3)
		{
			//判断终点柱子是否有盘子
			if(Seqstack_Len(s3) == 0)
			{
				//没有的话将"盘子"置为最大
				top = 10;
			}
			else
			{
				//有的话读取栈顶(最小盘子)的权
				Gettop(s3,&top);
			}
			//如果将入栈盘子的权小于入栈栈顶盘子的权
			if(bag.value < top)
			{
				//将小盘子入栈
				Push(s3,bag.value);
				//通过判断栈顶元素个数选择放置位置
				panzi[bag.value].x = 500 - (panzi[bag.value].width/2);;
				panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s3));
				sprintf(bmp_buf,"/lxy/wang/allbmp/p%d.bmp",bag.value);
				Display_Bmp(panzi[bag.value].x,panzi[bag.value].y,bmp_buf);
			}
			else
			{
				//如果将入栈盘子的权
				//大于入栈栈顶盘子的权的话
				//此步重开
				Push(bag.name,bag.value);
				//通过判断栈顶元素个数选择放置位置
				if(bag.name == s1)
				{
					panzi[bag.value].x = 100 - (panzi[bag.value].width/2);;
					panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s1));
				}
				if(bag.name == s2)
				{
					panzi[bag.value].x = 300 - (panzi[bag.value].width/2);;
					panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s2));
				}
				if(bag.name == s3)
				{
					panzi[bag.value].x = 500 - (panzi[bag.value].width/2);;
					panzi[bag.value].y = 480 - 60 - 30*(Seqstack_Len(s3));
				}
		
				sprintf(bmp_buf,"/lxy/wang/allbmp/p%d.bmp",bag.value);
		
				Display_Bmp(panzi[bag.value].x,panzi[bag.value].y,bmp_buf);
			}
			count++;
			show_num(count);
		}
		if(Seqstack_Len(s3) == NUM)
		{
			//结束游戏
			//你赢了
			Display_Bmp(0,0,"/lxy/wang/allbmp/you_win.bmp");
			if(Get_Touch() == 1)
			{
				goto start;
			}
		}
	}
}





