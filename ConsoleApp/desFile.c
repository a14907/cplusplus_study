#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "des.h"
#include "desFile.h"

//���ļ�����
int DesEncFile(const char * fromFileName, const char * toFileName)
{
	FILE *from = NULL, *to = NULL;
	int readLen = 0, writeLen = 0, res = 0, writebuflen = 0, desRes = 0;
	char buf[1024 * 4 - 1] = { 0 }, writeBuf[1024 * 4] = { 0 };

	from = fopen(fromFileName, "rb");
	if (from == NULL)
	{
		printf("�������ļ������ڣ�\n");
		res = -1;
		goto End;
	}
	to = fopen(toFileName, "wb");
	if (to == NULL)
	{
		printf("����������\n");
		res = -1;
		goto End;
	}
	while (!feof(from))
	{
		memset(buf, 0, sizeof(buf));
		memset(writeBuf, 0, sizeof(writeBuf));
		readLen = fread(buf, 1, sizeof(char) * 1024 * 4 - 1, from);
		if (!feof(from) && readLen != (sizeof(char) * 1024 * 4-1))
		{
			printf("��ȡ����\n");
			res = -1;
			goto End;
		}

		desRes = DesEnc(buf, readLen, writeBuf, &writebuflen);
		if (desRes != 0)
		{
			res = -1;
			goto End;
		}
		writeLen = fwrite(writeBuf, 1, writebuflen, to);
		if (writeLen != writebuflen)
		{
			printf("д�����\n");
			res = -1;
			goto End;
		}
	}

End:
	if (from != NULL)
	{
		fclose(from);
		from = NULL;
	}
	if (to != NULL)
	{
		fclose(to);
		to = NULL;
	}
	return res;
}

//���ļ�����
int DesDecFile(const char * fromFileName, const char * toFileName)
{
	FILE *from = NULL, *to = NULL;
	int readLen = 0, writeLen = 0, res = 0, writebuflen = 0, desRes = 0;
	char buf[1024 * 4] = { 0 }, writeBuf[1024 * 4 - 1] = { 0 };

	from = fopen(fromFileName, "rb");
	if (from == NULL)
	{
		printf("�������ļ������ڣ�\n");
		res = -1;
		goto End;
	}
	to = fopen(toFileName, "wb");
	if (to == NULL)
	{
		printf("����������\n");
		res = -1;
		goto End;
	}
	while (!feof(from))
	{
		memset(buf, 0, sizeof(buf));
		memset(writeBuf, 0, sizeof(writeBuf));
		readLen = fread(buf, 1, sizeof(char) * 1024 * 4 , from);
		if (!feof(from) && readLen != ( sizeof(char) * 1024 * 4))
		{
			printf("��ȡ����\n");
			res = -1;
			goto End;
		}

		desRes = DesDec(buf, readLen, writeBuf, &writebuflen);
		if (desRes != 0)
		{
			res = -1;
			goto End;
		}
		writeLen = fwrite(writeBuf, 1, writebuflen, to);
		if (writeLen != writebuflen)
		{
			printf("д�����\n");
			res = -1;
			goto End;
		}
	}

End:
	if (from != NULL)
	{
		fclose(from);
		from = NULL;
	}
	if (to != NULL)
	{
		fclose(to);
		to = NULL;
	}
	return res;
}