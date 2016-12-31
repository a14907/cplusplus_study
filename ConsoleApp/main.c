#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ctfOpt.h"

void printMenu()
{
	printf("==========================\n");
	printf("请选择操作：\n");
	printf("1.写入配置\n");
	printf("2.读取配置\n");
	printf("0.退出\n");
	printf("请选择：");
	printf("==========================\n");
}

int main()
{
	int opt = 0, res = 0;
	char key[100] = { 0 }, value[100] = {0};
	char *fileName = "./cfgfile.cfg";
	while (1)
	{
		printMenu();
		scanf("%d", &opt);
		switch (opt)
		{
		case 1:
			printf("请输入key:");
			scanf("%s",key);
			printf("\n请输入value:");
			scanf("%s", value);
			res=writeCfgItem(fileName,key,value);
			if (res!=0)
			{
				printf("写入出错！\n");
			}
			else
			{
				printf("写入成功！%s=%s\n",key,value);
			}
			break;
		case 2:
			printf("请输入key:");
			scanf("%s", key);
			res = readCfgItem(fileName, key, value);
			if (res != 0)
			{
				printf("读取出错！\n");
			}
			else
			{
				printf("读取成功！%s=%s\n", key, value);
			}
			break;
		case 0:
		default:
			exit(0);
			break;
		}
	}
	return 0;
}