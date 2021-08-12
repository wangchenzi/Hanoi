#目标文件名
TARGET:=main

#指定编译器
CC:=arm-linux-gcc

#用来指定工程中所有的.c文件
CSRCS:=$(wildcard *.c)

#用来指定工程中所有的.o文件
OBJS:=$(patsubst %.c,%.o,$(CSRCS))

#用来指定工程中的头文件的搜索路径
INCS+=-I ./ -I ./inc -I /home/china/Tools/arm-jpeg/include

#用来指定工程中的库的搜索路径
LIBS+=-L ./lib -L /home/china/Tools/arm-jpeg/lib -l jpeg

#依赖关系
#目标文件生成的依赖规则
$(TARGET):$(OBJS)
	$(CC) $^ $(LIBS) -o $@
				
%.o:%.c
	$(CC) -c $< $(INCS) -o $@

#清除：所有的中间文件和最终的可执行文件
clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)
