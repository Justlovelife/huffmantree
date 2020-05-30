#include "huffmantree.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

struct symbol{
	char ch;//字符
	int   num; //字符出现的次数
};

struct Filestate{
	struct symbol symbols[128];//可见字符一共127个  每个字符对应一个元素
	int ct;//记录一共有多少个字符
};

struct Filestate filestate;//全局变量，保存了字符的统计数据

void calc_ct(char ch)
{
	//分析ch有没有出现在数组symbols里，有则该元素的结构体num++   否则放入新的元素
	int flag = 0;
	int i;
	for (i = 0; i < filestate.ct; i++)//循环次数是已有字符的个数
	{
		if (ch == filestate.symbols[i].ch)
		{
			filestate.symbols[i].num++;
			flag = 1;    //代表已经找到了
			break;       //字符已经被存储过了，num++后就可以退出了
		}
	}
		if (flag == 0)  //前面遍历了但没有已保存的字符
		{
			 //找到数组里面第一个没有用到的数组元素位置，放进去   此时的i在最后一个数组元素i=filestate.ct-1
			filestate.symbols[filestate.ct].ch = ch;
			filestate.ct++;
			
		}
			
	
}



int main(void)
{
	bzero(&filestate, sizeof(filestate));//清空
	//memset(&filestate, 0, sizeof(filestate));
	//打开文件，读取字符，将字符存入数组，然后将次数+1
	int fd = open("ane.txt", O_RDONLY);   //只读权限
	if (fd == -1) return -1;
	char buffer;
	while (read(fd, &buffer, 1) == 1)
    {
			calc_ct(buffer);
		
	}
	int i;
	for (i = 0; i < filestate.ct; i++)
	{
		printf("symbol:%c,num=%d\n", filestate.symbols[i].ch, filestate.symbols[i].num);
		
	}
	int num[128];//临时变量，暂时存储num
	for (i = 0; i < filestate.ct; i++)
	{
		num[i] = filestate.symbols[i].num;
	}
	struct huffman *huffman = huffman_create(num, filestate.ct);
	//试着获取编码
	char code[20] = { 0 };
	int lenofcode;
	huffman_getcode(huffman, 5, code, &lenofcode);
	printf("字符是%c,编码是", filestate.symbols[5].ch);//获取5号数据的编码
	for (i = 0; i < lenofcode; i++)
		printf("%d", code[i]);
	printf("\n");

	//原理：
	//读压缩对象文件，每读一个字符，就找到它的编码，该编码可能多于8位，可能少于8位，凑够
	//读写内容已字节为单位
	//凑够8个位，将该字节写入文件，后面一样的处理，直到将整个文件读完，这就是压缩原理



}