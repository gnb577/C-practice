#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ascii 256
#define sz 1000
char buf[sz];
int buf_cnt[ascii];
int main()
{
	int n;
	scanf("%d", &n);
	scanf("%s", buf);
	memset(buf_cnt, 0, ascii * sizeof(int));
	int max = buf_cnt[0];
	int max_index = 0;
	int len = strlen(buf);
	printf("%d", len);
		
	for (int i = 1; i < 1000; i++)
	{
		if (buf[i] == 0)
		{
			break;
		}
		buf_cnt[(int)buf[i]]++;
	}
	for(int i=1;i<1000;i++)
	{
		if (buf_cnt[i - 1] < buf_cnt[i])
		{
			max = buf_cnt[i];
			max_index = i;
		}
	}
	printf("%c", (char)max_index);
	
	return 0;
}