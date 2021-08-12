#include "touch.h"

/***************************************
	跟触摸屏相关的一些功能函数
***************************************/

int Get_Touch(void)
{
	//打开触摸屏文件
	int fd_touch = open(TOUCH_PATH,O_RDWR);
	if(fd_touch == -1)
	{
		perror("Open Touch file failed");
		return -1;
	}

	int x = -1,y = -1;
	int ret;
	struct input_event ev;
	while(1)
	{
		ret = read(fd_touch,&ev,sizeof(ev));
		if(ret != sizeof(ev))
		{
			continue;
		}

		if(ev.type == EV_ABS && ev.code == ABS_X)
		{
			//意味着这是一个x轴的坐标输入事件
			x = ev.value;
		}
		else if(ev.type == EV_ABS && ev.code == ABS_Y)
		{
			//意味着这是一个y轴的坐标输入事件
			y = ev.value;			
		}
		else if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
		{
			//意味着手指离开了屏幕
		}

		if(x >= 0 && y >= 0)
		{
			printf("Touch Point [ %d %d ]\n",x,y);
		}
		return 1;
	}
}

/*
	触点函数，获取起始触点以及最终触点
	返回point结构体，其保存开始触点以及最终触点的(x,y)值
*/
struct Point Touch_Start_Stop(void)
{
	struct Point point;
	point.x_start = point.x_stop = 0;
	point.y_start = point.y_stop = 0;
	//打开触摸屏文件
	int fd_touch = open(TOUCH_PATH,O_RDWR);
	if(fd_touch == -1)
	{
		perror("Open Touch file failed");
		return point;
	}

	int x,y;
	int ret;
	struct input_event ev;
	while(1)
	{
		//读取触摸屏文件
		ret = read(fd_touch,&ev,sizeof(ev));
		if(ret != sizeof(ev))
		{
			perror("Read Touch file failed");
			return point;
		}
		//判断
		if(ev.type == EV_ABS && ev.code == ABS_X)
		{
			x = ev.value; //获取x坐标
		}
		if(ev.type == EV_ABS && ev.code == ABS_Y)
		{
			y = ev.value; //获取y坐标
		}

		if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 1)
		{
			//按下去
			point.x_start = x;
			point.y_start = y;
			printf("Start point : %d %d ",point.x_start,point.y_start);
		}
		if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
		{
			//松开
			point.x_stop = x;
			point.y_stop = y;
			printf("Stop point : %d %d ",point.x_stop,point.y_stop);
			break;
		}
	}
	return point;
}

/*  
	判断始触点在哪一区域
	需传入x_start的值
	返回柱子序数
*/	
int Area_Judge_Start(int x)
{
	if(x >= 0 && x < 256)
	{
		//表示在第一根柱子区域
		return 1;

	}
	else if(x >= 256 && x < 512)
	{
		//表示在第二根柱子区域
		return 2;
	}
	else if(x >= 512 && x < 768)
	{
		//表示在第三根柱子区域
		return 3;
	}
}

/*  
	判断最终触点在哪一区域
	需传入x_stop的值
	返回柱子序数
*/	                                                                            
int Area_Judge_Stop(int x)
{
	if(x >= 0 && x < 256)
	{
		//表示在第一根柱子区域
		return 1;

	}
	else if(x >= 256 && x < 512)
	{
		//表示在第二根柱子区域
		return 2;
	}
	else if(x >= 512 && x < 768)
	{
		//表示在第三根柱子区域
		return 3;
	}
}


/*
	touch区域判断，选择难度
	需传入struct Point结构体的值，成功返回初始化盘子数，失败返回1
*/
int Menu_Judge(struct Point p)
{
	int panzi_init;
	
	if(p.x_start >= 819 && p.x_stop <= 973)
	{
		//表示在我难度菜单范围内
		if(p.y_start >= 88 && p.y_stop <= 138)
		{
			//难度为简单
			panzi_init = 3;
		}
		else if(p.y_start >= 150 && p.y_stop <= 200)
		{
			//难度为中等
			panzi_init = 5;
			
		}
		else if(p.y_start >= 213 && p.y_stop <= 263)
		{
			//难度为困难
			panzi_init = 7;
			
		}
	}
	else
	{
		panzi_init = 0;
	}
	
	return panzi_init;
}


/*
	touch区域判断，菜单栏重新开始
	需传入struct Point结构体的值，成功返回0，失败返回-1
*/
int game_again(struct Point p)
{
	if(p.x_start >= 806&& p.x_stop <= 986 && p.y_start >= 437 && p.y_stop <= 500)
	{
		//重新开始
		return 0;
	}
	return -1;
}
