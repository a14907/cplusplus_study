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
		printf("����ʧ�ܣ�\n");
		return res;
	}
	else
	{
		printf("���ܳɹ���\n");
	}

	res = DesDecFile("d:/wdq_jiami.txt","d:/wdq_jiemi.txt");
	if (res != 0)
	{
		printf("����ʧ�ܣ�\n");
		return res;
	}
	else
	{
		printf("���ܳɹ���\n");
	}


	return 0;
}