#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "desFile.h"


int main()
{
	char * fileName = "d:/wdq.txt";
	int res = 0;
	res=	DesEncFile(fileName,"d:/wdq_jiami.txt");
	if (res!=0)
	{
		printf("加密失败！\n");
		return res;
	}
	else
	{
		printf("加密成功！\n");
	}

	res = DesDecFile("d:/wdq_jiami.txt","d:/wdq_jiemi.txt");
	if (res != 0)
	{
		printf("解密失败！\n");
		return res;
	}
	else
	{
		printf("解密成功！\n");
	}


	return 0;
}