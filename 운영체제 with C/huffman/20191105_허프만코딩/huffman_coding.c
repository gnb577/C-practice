#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//전역변수와 지역변수의 차이
//전역변수 자동으로 0으로 초기화, 지역변수는 쓰레기값
//지역변수는 stack영역, 전역변수는 heap영역
//stack영역은 크기가 작아서
//메모리를 크게 사용하고 싶으면 전역변수,(heap 영역)을 사용

int char_cnt[256];

void show_table()
{
	for (int i = 0; i < 256; i++)
	{
		unsigned char k;
		k = i;
		printf("%d-------->%d\n", i, char_cnt[i]);
	}
}

int main()
{
	FILE* f;
	char buf[1000];

	memset(char_cnt, 0, sizeof(int)*256);
	for (int i = 0; i < 256; i++)
	{
		printf("%d-------->%d\n", i, char_cnt[i]);
	}
	//fopen
	f = fopen("alice.txt","rt");
	if (f == 0)
	{
		printf("unable to open alice.txt");
		return;
	}
	while (1)
	{
		int i;
		char *temp = fgets(buf, 1000, f); // 100byte만 읽겟다
		if (temp == 0)
		{
			break;
		}
		
		for (i = 0; i < strlen(buf); i++)
		{
			char_cnt[buf[i]]++;
		}
		printf("%s", buf);
	}
	show_table();
	//fclose
	fclose(f);
    
	return 0;
}