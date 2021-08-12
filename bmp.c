#include "bmp.h"
/*
	跟BMP图片显示相关的功能模块(函数)
*/

int Display_Bmp(int x0, int y0, const char *bmppath)
{
	int fd_bmp = open(bmppath,O_RDONLY);
	if(fd_bmp == -1)
	{
		perror("Open Bmp Failed");
		return -1;
	}
	//判断此文件是否为BMP文件
	unsigned char buf[4] = {0};
	int ret = read(fd_bmp,buf,2);
	if(ret == -1)
	{
		perror("Read Bmp Failed");
		return -1;
	}
	if(buf[0] == 0x42 && buf[1] == 0x4d)
	{
		//printf("%s is a bmp file\n",bmppath);
	}
	else
	{
		printf("%s is not a bmp file\n",bmppath);
		return -1;
	}

	//读取宽度数据
	lseek(fd_bmp,0x12,SEEK_SET);
	ret = read(fd_bmp,buf,4);
	if(ret == -1)
	{
		perror("Read Bmp Failed");
		return -1;
	}
	//小端模式
	int width = (buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0]);

	//读取高度数据
	lseek(fd_bmp,0x16,SEEK_SET);
	ret = read(fd_bmp,buf,4);
	if(ret == -1)
	{
		perror("Read Bmp Failed");
		return -1;
	}
	//小端模式
	int height = (buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0]);
	
	//读取色深数据
	lseek(fd_bmp,0x1C,SEEK_SET);
	ret = read(fd_bmp,buf,2);
	if(ret == -1)
	{
		perror("Read Bmp Failed");
		return -1;
	}
	//小端模式
	int depth = (buf[1] << 8 | buf[0]);

	//计算出BMP文件的每行所占的字节数
	int width_bit = depth/8 * width;
	//计算出赖子的个数[0,3]
	int laizi = 4 - (width_bit % 4);
	//用来保存像素数组的内存空间一行占字节数=每行所占的字节数+赖子
	int width_bit_mem = width_bit + laizi;
	//用来保存像素数组的内存空间大小为一行占字节数*高度
	int mem = width_bit_mem * height;
	//开辟空间malloc();
	char bmp_buf[mem];
	//将像素数组读取到刚开辟出来的空间中去
	lseek(fd_bmp,0x36,SEEK_SET);
	ret = read(fd_bmp,bmp_buf,mem);
	if(ret == -1)
	{
		perror("Read Bmp_pixel Failed");
		return -1;
	}
	//数据的写入,处理数据,小端模式合成写入,从开辟的数组空间写入到映射区域
	int bmp_color;
	//32位色深，四个字节
	if(depth == 32)
	{
		for(int j = 0;j < height;j++)
		{
			for(int i = 0;i < width_bit;i = i+4)
			{
				bmp_color = (*(bmp_buf + j * width_bit + i + 3) << 24 | *(bmp_buf + j * width_bit + i + 2) << 16 | *(bmp_buf + j * width_bit + i + 1) << 8 | *(bmp_buf + j * width_bit + i));
				Lcd_Draw_Point(x0 + i/4,y0 + (height - j),bmp_color);
			}
		}
	}
	//24位色深，三个字节
	else if(depth == 24)
	{
		for(int j = 0;j < height;j++)
		{
			for(int i = 0;i < width_bit;i = i+3)
			{
				bmp_color = (*(bmp_buf + j * width_bit + i + 2) << 16 | *(bmp_buf + j * width_bit + i + 1) << 8 | *(bmp_buf + j * width_bit + i));
				Lcd_Draw_Point(x0 + i/3,y0 + (height - j),bmp_color);
			}
		}
	}
	close(fd_bmp);
}


/*
	清空盘子图片
*/
int Display_Bmp_cover(int x0,int y0,const char *bmppath,int Height,int Width)
{
	//打开BMP文件
	int fd_bmp = open(bmppath,O_RDONLY);
	if(fd_bmp == -1)
	{
		perror("Open Bmp File Failed");
		return -1;
	}
	unsigned char buf[4] = {0};
	//判断此文件是否为BMP文件
	int ret = read(fd_bmp,buf,2);
	if(ret == -1)
	{
		perror("Read Bmp Failed");
		return -1;
	}

	if(buf[0] == 0x42 && buf[1] == 0x4D)
	{
 		//printf("%s is bmp file ",bmppath);
	}
	else
	{
		printf("%s is not bmp file,bye bye!\n",bmppath);
		return -1;
	}

	//读取宽度数据
	lseek(fd_bmp,0x12,SEEK_SET);
	ret = read(fd_bmp,buf,4);
	if(ret == -1)
	{
		perror("Read Bmp Width Failed");
		return -1;
	}
	int width = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

	//读取高度数据
	lseek(fd_bmp,0x16,SEEK_SET);
	ret = read(fd_bmp,buf,4);
	if(ret == -1)
	{
		perror("Read Bmp Height Failed");
		return -1;
    }
	int height = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];  

	//读取色深数据
	lseek(fd_bmp,0x1C,SEEK_SET);
	ret = read(fd_bmp,buf,2);
	if(ret == -1)
	{
		perror("Read Bmp Depth Failed");
		return -1;
	}
	int depth = (buf[1] << 8) | buf[0];

	//printf("[WIDTH : %d] [HEIGHT : %d] [DEPTH : %d]\n",width,height,depth);

	//计算出BMP文件的每行所占的字节数
	int bytes_line_bmp = (depth / 8) * abs(width);
				
	//通过BMP文件每行所占的字节数计算出赖子的个数
	int laizi = 0;
	if(bytes_line_bmp % 4 != 0)
	{
		laizi = 4 - bytes_line_bmp % 4;
	}

	//用来保存像素数组的内存空间一行占字节数=BMP文件每行所占的字节数+赖子的个数
	int bytes_line_mem = bytes_line_bmp + laizi;

	//用来保存像素数组的内存空间大小为=一行占字节数*高度
	int size = bytes_line_mem * abs(height);
			
	//开辟空间
	unsigned char *piexl = malloc(size);

	//将像素数组读取到刚开辟出来的空间中去
	lseek(fd_bmp,54,SEEK_SET);
	ret = read(fd_bmp,piexl,size);
	if(ret == -1)
	{
		perror("Read Piexl Failed");
		return -1;
	}

	//数据的处理
	int x,y;
	unsigned char a,r,g,b;
	int i = 0;
	int color;

	for(y = 0;  y < height;y++)
	{                                      
		for(x = 0;x < width;x++)         
		{
            
			//取像素点的四个分量值
            
			b = piexl[i++];
			g = piexl[i++];
			r = piexl[i++];
			if(depth == 24)
			{
				a = 0x00;
			}
			else if(depth == 32)
			{
				a = piexl[i++];
			}
			//合成像素点的值
			color = (a << 24) | (r << 16) | (g << 8) | b;
			if(x0 <= x && x<= x0 + Width && y0 <= y &&y <= y0 + Height)     
			{
 				Lcd_Draw_Point(x ,y-1 ,color);   //把背景图上的y0 --y0+Height区域和x0 --x0+Width区域写入屏幕上的y0 --y0+Height区域和x0 --x0+Width区域
			}
		}
		i = i + laizi;
	}

	close(fd_bmp);
	return 0;
}
void show_num(int count)
{
	int count_1 = count % 10;//个位
	int count_2 = count / 10;//十位

	char buf[512];
	sprintf(buf,"/lxy/wang/allbmp/n%d.bmp",count_1);
	
	Display_Bmp(740,220,buf);


	
	sprintf(buf,"/lxy/wang/allbmp/n%d.bmp",count_2);
	Display_Bmp(700,220,buf);

}
