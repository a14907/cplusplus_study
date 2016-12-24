#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int countStr(char *p, int *len,int *maxSize,char  splitStr)
{
	if (p == NULL || len == NULL || maxSize==NULL)
	{
		return -1;
	}
	*maxSize = 1;
	char *temp = NULL;
	char *preTemp = p;
	char split[] = { splitStr,'\0' };
	temp = strstr(p, split);
	int length = 1;
	do
	{
		if (temp == NULL)
		{
			if (*maxSize<((p + strlen(p)) - preTemp))
			{
				*maxSize = (p + strlen(p)) - preTemp;
			}
		}
		else if (*maxSize<(temp - preTemp))
		{
			*maxSize = temp - preTemp;
		}
		if (temp == NULL)
		{
			*len = length;
			return 0;
		}
		temp++;
		preTemp = temp;
		temp = strstr(temp, split);
		length++;
	} while (1);
	return 0;
}

int getareaarray(char ***str,int count,int size)
{
	if (str==NULL)
	{
		return -1;
	}
	char **p =(char**) malloc(sizeof(char*)*count);
	for (size_t i = 0; i < count; i++)
	{
		p[i] = malloc(sizeof(char)*(size+1));
	}
	*str = p;
	return 0;
}

int freestrarray(char ***str,int num)
{
	if (str==NULL)
	{
		return -1;
	}
	char **temp = *str;
	for (size_t i = 0; i < num; i++)
	{
		free(*(temp + i));
	}
	free(*str);
	*str = NULL;
	return 0;
}

int split_str(const char *p, char ***res, int *len,char  splitStr)
{
	if (p==NULL || res==NULL || len==NULL)
	{
		return -1;
	}
	char *temp = p;
	//1.获取有多少段,and the max size
	int maxsize = 0;
	countStr(p,len,&maxsize, splitStr);
	//2.分配内存
	char **arr = NULL;
	getareaarray(&arr,*len,maxsize);
	//3.复制内容
	int j = 0;
	for (size_t i = 0; i < *len; i++)
	{
		while (*temp !='\0' && *temp != splitStr)
		{
			arr[i][j++] = *temp;
			temp++;
		}
		arr[i][j] = '\0';
		j = 0;
		temp++;
	}
	*res = arr;

	return 0;
}

int print_arr_atr(char **arr,int len)
{
	if (arr==NULL)
	{
		return -1;
	}
	for (size_t i = 0; i < len; i++)
	{
		printf("%s\n",arr[i]);
	}
}

int main()
{
	char *p="asasa";
	char **arr = NULL;
	int len = 0;
	split_str(p,&arr,&len,'s');
	print_arr_atr(arr,len);

	freestrarray(&arr,len);
 

	return 0;
}