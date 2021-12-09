#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ascii 256
#define sz 1000
char buf[sz];
int buf_cnt[ascii];
int buf_cnt_cnt[ascii];

int main()
{
	int n;
	scanf("%d", &n);
	scanf("%s", buf);
	memset(buf_cnt, 0, ascii * sizeof(int));
	memset(buf_cnt_cnt, 0, ascii * sizeof(int));
	int max = buf_cnt_cnt[0];
	int max_index = 0;
	int len = strlen(buf);
	//printf("%d\n", len);
	
	for (int i = 0; i < len; i++)
	{
		buf_cnt[(int)buf[i]]++;
	}
	for (int i = 1; i < ascii; i++)
	{
		if (buf_cnt[i] != 0)
		{
			buf_cnt_cnt[buf_cnt[i]]++;
		}
	}
	for (int i = 1; i < ascii; i++)
	{
		if (buf_cnt_cnt[i - 1] < buf_cnt_cnt[i])
		{
			max = buf_cnt_cnt[i];
			max_index = i;
		}
	}
	//printf("%d\n", max);
	printf("%d\n", max_index);

	return 0;
}