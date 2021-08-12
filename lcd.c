#include "lcd.h"

//屏幕文件的文件描述符
static int fd_lcd = -1;

//指向映射区域(实际上就是指向第一个像素点)
static int *plcd = NULL;

/*
	跟显示屏相关的一些功能函数
*/

/*
	对LCD屏幕的初始化
		初始化成功返回0,失败返回-1
*/
int Lcd_Init(void)
{
	//打开文件
	fd_lcd = open(LCD_PATH,O_RDWR);
	if(fd_lcd == -1)
	{
		perror("Open Lcd Failed");
		return -1;
	}

	//将屏幕文件映射到内存中去
	plcd = mmap(NULL,LCD_HEIGHT*LCD_WIDTH*4,PROT_READ | PROT_WRITE,MAP_SHARED,fd_lcd,0);
	if(plcd == MAP_FAILED)
	{
		perror("MMAP Failed");
		return -1;
	}
	return 0;
}

/*
	LCD的解初始化函数
*/
void Lcd_Uinit(void)
{
	munmap(plcd,LCD_HEIGHT*LCD_WIDTH*4);
	close(fd_lcd);
}

/*
	画点函数:将(x,y)处的像素点显示成color颜色
*/
void Lcd_Draw_Point(int x,int y,int color)
{
	if(x >= 0 && x < LCD_WIDTH && y >= 0 && y < LCD_HEIGHT)
	{
		*(plcd + LCD_WIDTH*y + x) = color;
	}
}

/*
	画矩形:以(x0,y0)处为起始点画一个宽为w高为h颜色为color的矩形
*/
void Lcd_Draw_Orth(int x0,int y0,int w,int h,int color)
{
	int x,y;
	for(y = y0;y <= y0 + h;y++)
	{
		for(x = x0;x <= x0 + w;x++)
		{
			Lcd_Draw_Point(x,y,color);
		}
	}
}
/*
	画圆形:以(x0,y0)处为起始点画一个半径为r颜色为color的圆形
*/
void Lcd_Draw_Circle(int x0,int y0,int r,int color)
{
	int x,y;
	for(y = 0;y <= 480;y++)
	{
		for(x = 0;x <= 800;x++)
		{
			if((x - x0)*(x - x0) + (y - y0)*(y - y0) <= r*r);
			{
				Lcd_Draw_Point(x,y,color);
			}
		}
	}
}

/*
	将屏幕分成垂直水平四个矩形
*/
void four_square(void)
{
	//x为宽800，y为高480
	int x,y;
	//1.垂直水平平分四部分
	for(y = 0; y < 480; y++)
	{
		for(x = 0; x < 800; x++)
		{
			if(y >= 0 && y < 240 && x >= 0 && x < 400)
			{
				Lcd_Draw_Point(x,y,0XFF0000);//红色
			}
			if(y >= 0 && y < 240 && x >= 400 && x < 800)
			{
				Lcd_Draw_Point(x,y,0X00FF00);//绿色
			}	
			if(y >= 240 && y < 480 && x >= 400 && x < 800)
			{
				Lcd_Draw_Point(x,y,0X0000FF);//蓝色
			}
			if(y >= 240 && y < 480 && x >= 0 && x < 400)
			{
				Lcd_Draw_Point(x,y,0XFFFF00);//绿色
			}
		}
	}
}

/*
	将屏幕分成对角线四个三角形
*/
void diagonal(void)
{
	//x为宽800，y为高480
	int x,y;
	//2.对角线平分四部分
	for(y = 0; y < 480; y++)
	{
		for(x = 0; x < 800; x++)
		{
			if(y >= 0 && y < 240 && x >= 0 && x < 400)
			{
				if((double)y / x <= (double)480 / 800)
				{
					Lcd_Draw_Point(x,y,0XFF0000);//红色
				}
				if((double)y / x > (double)480 / 800)
				{
					Lcd_Draw_Point(x,y,0XFFFF00);//黄色
				}
			}
			if(y >= 0 && y < 240 && x >= 400 && x < 800)
			{
				if((double)y / (double)(800 - x) <= (double)480 / 800)
				{
					Lcd_Draw_Point(x,y,0XFF0000);//红色
				}
				if(y / (double)(800 - x) > (double)480 / 800)
				{
					Lcd_Draw_Point(x,y,0X00FF00);//绿色
				}
			}	
			if(y >= 240 && y < 480 && x >= 400 && x < 800)
			{
				if((double)(480 - y) / (double)(800 - x) <= (double)480 / 800)
				{
					Lcd_Draw_Point(x,y,0X0000FF);//蓝色
				}
				if((double)(480 - y) / (double)(800 - x) > (double)480 / 800)
				{
					Lcd_Draw_Point(x,y,0X00FF00);//绿色
				}
			}
			if(y >= 240 && y < 480 && x >= 0 && x < 400)
			{
				if((double)(480 - y) / x > (double)480 / 800)
				{
					Lcd_Draw_Point(x,y,0XFFFF00);//黄色
				}
				if((double)(480 - y) / x <= (double)480 / 800)
				{
					Lcd_Draw_Point(x,y,0X0000FF);//蓝色
				}
			}			
		}
	} 
}

/*
	太极
*/
void taiji(void)
{
	//x为宽800，y为高480
	int x,y;
	//3.太极
	for(y = 0; y < 480; y++)
	{
		for(x = 0; x < 800; x++)
		{
			if((x - 400)*(x - 400) + (y - 240)*(y - 240) <= 200*200)
			{
				if(y >= 0 && y < 240)
				{
					Lcd_Draw_Point(x,y,0X000000);//黑色
				}
				if(y >= 240 && y < 480)
				{
					Lcd_Draw_Point(x,y,0XFFFFFF);//白色
				}
			}
			if((x - 300)*(x - 300) + (y - 240)*(y - 240) <= 100*100)
			{
				if(y >= 0 && y < 240)
				{
					Lcd_Draw_Point(x,y,0XFFFFFF);//白色
				}
			}
			if((x - 500)*(x - 500) + (y - 240)*(y - 240) <= 100*100)
			{
				if(y >= 240 && y < 480)
				{
					Lcd_Draw_Point(x,y,0X000000);//黑色
				}
			}
			if((x - 300)*(x - 300) + (y - 240)*(y - 240) <= 30*30)
			{
				Lcd_Draw_Point(x,y,0X000000);//黑色
			}
			if((x - 500)*(x - 500) + (y - 240)*(y - 240) <= 30*30)
			{
				Lcd_Draw_Point(x,y,0XFFFFFF);//白色
			}
		}
	}
}

/*
	彩虹
*/
void rainbow(void)
{
	//x为宽800，y为高480
	int x,y;
	//彩虹
	for(y = 0; y < 480; y++)
	{
		for(x = 0; x < 800; x++)
		{
			if((x - 400)*(x - 400) + (y - 480)*(y - 480) <= 400*400)
			{
				Lcd_Draw_Point(x,y,0XFF0000);//赤色
			}
			if((x - 400)*(x - 400) + (y - 480)*(y - 480) <= 350*350)
			{
				Lcd_Draw_Point(x,y,0XFF7F00);//橙色
			}
			if((x - 400)*(x - 400) + (y - 480)*(y - 480) <= 300*300)
			{
				Lcd_Draw_Point(x,y,0XFFFF00);//黄色
			}
			if((x - 400)*(x - 400) + (y - 480)*(y - 480) <= 250*250)
			{
				Lcd_Draw_Point(x,y,0X00FF00);//绿色
			}
			if((x - 400)*(x - 400) + (y - 480)*(y - 480) <= 200*200)
			{
				Lcd_Draw_Point(x,y,0X0000FF);//蓝色
			}
			if((x - 400)*(x - 400) + (y - 480)*(y - 480) <= 150*150)
			{
				Lcd_Draw_Point(x,y,0X7FFFD4);//靛色
			}
			if((x - 400)*(x - 400) + (y - 480)*(y - 480) <= 100*100)
			{
				Lcd_Draw_Point(x,y,0XFF00FF);//紫色
			}
			if((x - 400)*(x - 400) + (y - 480)*(y - 480) <= 50*50)
			{
				Lcd_Draw_Point(x,y,0XFFFFFF);//白色
			}
		}
	}
}

/*
	五星红旗
*/
void flag(void)
{
	//x为宽800，y为高480
	int x,y;
	//4.五星红旗
	for(y = 0; y < 480; y++)
	{
		for(x = 0; x < 800; x++)
		{
			
			
		}
	}
}

