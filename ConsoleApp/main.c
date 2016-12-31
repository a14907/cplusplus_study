#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ctfOpt.h"

void printMenu()
{
	printf("==========================\n");
	printf("��ѡ�������\n");
	printf("1.д������\n");
	printf("2.��ȡ����\n");
	printf("0.�˳�\n");
	printf("��ѡ��");
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
			printf("������key:");
			scanf("%s",key);
			printf("\n������value:");
			scanf("%s", value);
			res=writeCfgItem(fileName,key,value);
			if (res!=0)
			{
				printf("д�����\n");
			}
			else
			{
				printf("д��ɹ���%s=%s\n",key,value);
			}
			break;
		case 2:
			printf("������key:");
			scanf("%s", key);
			res = readCfgItem(fileName, key, value);
			if (res != 0)
			{
				printf("��ȡ����\n");
			}
			else
			{
				printf("��ȡ�ɹ���%s=%s\n", key, value);
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