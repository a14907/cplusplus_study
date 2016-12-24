#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

int countStr(char *p, int *len, int *maxSize, char * splitStr)
{
	if (p == NULL || len == NULL || maxSize == NULL)
	{
		return -1;
	}
	*maxSize = 1;
	char *temp = NULL;
	char *preTemp = p;
	temp = strstr(p, splitStr);
	int length = 1;
	do
	{
		if (temp == NULL)
		{
			if (*maxSize < ((p + strlen(p)) - preTemp))
			{
				*maxSize = (p + strlen(p)) - preTemp;
			}
		}
		else if (*maxSize < (temp - preTemp))
		{
			*maxSize = temp - preTemp;
		}
		if (temp == NULL)
		{
			*len = length;
			return 0;
		}
		temp += strlen(splitStr);
		preTemp = temp;
		temp = strstr(temp, splitStr);
		length++;
	} while (1);
	return 0;
}

int getareaarray(char ***str, int count, int size)
{
	if (str == NULL)
	{
		return -1;
	}
	char **p = (char**)malloc(sizeof(char*)*count);
	for (size_t i = 0; i < count; i++)
	{
		p[i] = malloc(sizeof(char)*(size + 1));
	}
	*str = p;
	return 0;
}

int freestrarray(char ***str, int num)
{
	if (str == NULL)
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

//1表示是，0表示否，-1表示出错
int nextIsStr(const char * p, char * splitStr, int  len)
{
	if (p == NULL || splitStr == NULL)
	{
		return -1;
	}
	for (size_t i = 0; i < len; i++)
	{
		if (*p++ != *splitStr++)
		{
			return 0;
		}
	}
	return 1;
}

int split_str(const char *p, char ***res, int *len, char * splitStr)
{
	if (p == NULL || res == NULL || len == NULL)
	{
		return -1;
	}
	char *temp = p;
	//1.获取有多少段,and the max size
	int maxsize = 0;
	countStr(p, len, &maxsize, splitStr);
	//2.分配内存
	char **arr = NULL;
	getareaarray(&arr, *len, maxsize);
	//3.复制内容
	int j = 0;
	for (size_t i = 0; i < *len; i++)
	{
		while (*temp != '\0' && nextIsStr(temp, splitStr, strlen(splitStr)) == 0)
		{
			arr[i][j++] = *temp;
			temp++;
		}
		arr[i][j] = '\0';
		j = 0;
		temp += strlen(splitStr);
	}
	*res = arr;

	return 0;
}

int print_arr_atr(char **arr, int len)
{
	if (arr == NULL)
	{
		return -1;
	}
	for (size_t i = 0; i < len; i++)
	{
		printf("%s\n", arr[i]);
	}
}

int countTimesInStr(const char * oldstr, const char * findStr, int * count)
{
	if (oldstr == NULL || findStr == NULL || count == NULL)
	{
		return -1;
	}
	int i = 0;
	while (oldstr = strstr(oldstr, findStr))
	{
		i++;
		oldstr += strlen(findStr);
	}
	*count = i;

	return 0;
}

int findAndReplaceStr(const char *oldstr, const char * findStr, const char *replacestr, int *count, char **newstr)
{
	if (oldstr == NULL || replacestr == NULL || count == NULL || newstr == NULL)
	{
		return -1;
	}
	//1.统计出现次数
	if (countTimesInStr(oldstr, findStr, count) != 0)
	{
		return -1;
	}
	//2.分配内存
	char *tempStr = malloc(1 + sizeof(char)*(strlen(oldstr) + (strlen(replacestr) - strlen(findStr))* *count));
	char *ttstr = tempStr;

	//3.复制数据
	int splen = 0;
	char **strarr = NULL;
	if (split_str(oldstr, &strarr, &splen, findStr) == -1)
	{
		return -1;
	}
	for (size_t i = 0; i < splen; i++)
	{
		strncpy(ttstr, strarr[i], strlen(strarr[i]));//拷贝第一段
		ttstr += strlen(strarr[i]);
		if (i == (splen - 1))
		{
			break;
		}
		//拷贝替换字符串
		strncpy(ttstr, replacestr, strlen(replacestr));//拷贝第一段
		ttstr += strlen(replacestr);
	}
	//添加结束表示
	*ttstr = '\0';

	*newstr = tempStr;
	freestrarray(&strarr, splen);

	return 0;
}

int main()
{
	char *p = "111aa222aa333aa444aa";
	char *newstr = NULL;
	int count = 0;
	findAndReplaceStr(p, "111", "---", &count, &newstr);

	printf("newstr:%s\ntimes:%d\n", newstr, count);

	if (newstr != NULL)
	{
		free(newstr);
		newstr = NULL;
	}

	return 0;
}