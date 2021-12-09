#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//argc: argument count
//ex) huff.exe -e alice.txt argc==>3°³
//argv: argument º¯¼ö
//argv[0]= "huff.exe" argv[1] = "-e"
#define SZ 100
#define NUM_ASCII 256
char buf_cnt[NUM_ASCII];

void show()
{
	for (int i = 0; i < NUM_ASCII; i++)
	{
		if (buf_cnt[i] > 0)
		{
			printf("ASCII code %d ( %c ) : %d \n", i, (char)i, buf_cnt[i]);
		}
	}
}
void performencoding(char* fname)
{
	FILE* fin;
	char buf[SZ];
	fin = fopen(fname, "rt");
	if (fin == 0)
	{
		printf("unable to open %s. program terminated.\n", fname);
		return;
	}
	memset(buf_cnt, 0, NUM_ASCII * sizeof(int));
	while (fgets(buf, SZ, fin) != 0)
	{
		int len = strlen(buf);
		for (int i = 0; i < len; i++)
		{
			buf_cnt[(int)buf[i]]++;
		}
	}
	show();
	fclose(fin);
}


int main(int argc,char* argv[])
{
	if (argc < 3)
	{
		printf("Usage: huff.exe -e filetoencode\n");
		printf("Usage: huff.exe -d filetodecode\n");
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
	return 0;
}