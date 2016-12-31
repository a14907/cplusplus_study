#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ctfOpt.h"

int isContainKey(const char *line, const char * key)
{
	if (line == NULL || key == NULL)
	{
		printf("isContainKey error:%d\n", -1);
		return -1;
	}
	int res = 0;
	char *p1 = strstr(line, key);
	if (p1 == NULL)
	{
		res = -1;
		return res;
	}
	char *p2 = strstr(line, "=");
	if (p1 > p2)
	{
		res = -1;
		return res;
	}
	else
	{
		while (line < p1)
		{
			if (*line != ' ')
			{
				res = -1;
				break;
			}
		}
		char * temp1 = p1 + strlen(key);
		while (temp1 < p2)
		{
			if (*temp1 != ' ')
			{
				res = -1;
				break;
			}
		}
	}
	return res;
}

int freeMallocStr(char *** buf, int len)
{
	if (buf == NULL)
	{
		return -1;
	}
	char ** temp = *buf;
	for (size_t i = 0; i < len; i++)
	{
		if (temp[i] != NULL)
		{
			free(temp[i]);
			temp[i] = NULL;
		}
	}
	if (temp!=NULL)
	{
		free(temp);
	}
	*buf = NULL;

	return 0;
}

int writeCfgItem(const char * filename, const char * key, const char * value)
{
	if (filename == NULL || key == NULL || value == NULL)
	{
		printf("writeCfgItem error:%d\n", -1);
		return -1;
	}
	//如果key不存在则新增key，存在则修改key
	FILE *p = fopen(filename, "r+");
	if (p == NULL)
	{
		//不存在配置文件，新建一个
		p = fopen(filename, "w+");
		if (p == NULL)
		{
			printf("磁盘空间已满！\n");
			return -1;
		}
	}
	int res = 0, keyExists = -1, i = 0, lineCount = 0;
	char line[1024] = { 0 };
	while (!feof(p))
	{
		memset(line, 0, 1024);
		fgets(line, 1024, p);
		lineCount++;
	}
	char ** fileCache =(char**) calloc(sizeof(char *)*(lineCount),1);

	fseek(p, 0, SEEK_SET);
	//循环读取一行一行文件，判断key
	while (!feof(p))
	{
		memset(line,0,1024);
		fgets(line, 1024, p);
		//判断key的存在
		res = isContainKey(line, key);
		if (res == 0)//存在
		{
			keyExists = 0;
			char * equstr = strstr(line, "=");
			fileCache[i] = (char*)calloc(sizeof(char)*((equstr - line) + strlen(value) + 3), 1);
			int j = 0;
			while ((line + j) <= equstr)
			{
				fileCache[i][j] = line[j];
				j++;
			}
			strcat(fileCache[i], value);
			strcat(fileCache[i], "\n");
		}
		else//这一行不存在
		{
			char *yyy = fileCache[i];
			fileCache[i] = (char*)malloc(sizeof(char)*(strlen(line) + 1));
			memset(fileCache[i], 0, sizeof(char)*(strlen(line) + 1));
			strcpy(fileCache[i], line);
		}
		i++;
	}
	char *extLine = NULL;
	if (keyExists != 0)//整个文件范围内不存在
	{
		extLine = calloc(sizeof(char)*(strlen(key) + strlen(value) + 3), 1);
		sprintf(extLine, "%s=%s\n", key, value);
	}
	//保存
	fseek(p, 0, SEEK_SET);
	for (i = 0; i < lineCount; i++)
	{
		if (strlen(fileCache[i]) == 0)
		{
			continue;
		}
		fputs(fileCache[i], p);
	}
	if (extLine != NULL)
	{
		fputs(extLine, p);
	}

	if (fileCache != NULL)
	{
		res = freeMallocStr(&fileCache, lineCount);
		if (res != 0)
		{
			return -1;
		}
	}
	if (extLine != NULL)
	{
		free(extLine);
	}


	if (p != NULL)
	{
		fclose(p);
	}
	return 0;
}
int readCfgItem(const char * filename, const char * key, char * value)
{
	if (filename == NULL || key == NULL || value == NULL)
	{
		return -1;
	}
	char buf[1024] = { 0 };
	FILE *p = fopen(filename, "r");
	if (p == NULL)
	{
		return -1;
	}
	int res = 0;
	while (!feof(p))
	{
		fgets(buf, 1024, p);
		res = isContainKey(buf, key);
		if (res != 0)
		{
			continue;
		}
		else
		{
			char *temp = strstr(buf, "=") + 1;
			while (isspace(*temp))
			{
				temp++;
			}
			char *temp2 = buf + strlen(buf) - 1;
			while (isspace(*temp2))
			{
				temp2--;
			}
			strncpy(value, temp, temp2 - temp + 3);
			break;
		}
	}

	return 0;
}
