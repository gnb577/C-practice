#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ascii 256
#define sz 100

void performencoding(char* fname)
{
	FILE* fin;
	fin = fopen(fname, "rt");
	char buf[sz];
	int buf_cnt[ascii];
	memset(buf_cnt, 0, ascii * sizeof(int));

	while (fgets(buf, sz, fin) != 0)
	{
		int len = strlen(buf);
		for (int i = 0; i < len; i++)
		{
			buf_cnt[(int)buf[i]]++;
		}
		printf("%s", buf);
	}
}


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("?߸??߾?\n");
		return -1;
	}
	if (strcmp(argv[1], "-e") == 0)
	{
		printf("start encoding\n");
		performencoding(argv[2]);
	}
	else if (strcmp(argv[1], "-d") == 0)
	{
		printf("start decoding\n");
	}

}