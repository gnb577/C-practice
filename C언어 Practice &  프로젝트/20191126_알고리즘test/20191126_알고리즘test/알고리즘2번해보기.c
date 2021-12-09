#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SZ 100
#define ascii 256

char code[256][100];
char buf[100];
int buf_cnt[ascii];
char decode_buf[ascii] = { 0, };
char make_code[100];
int letter_cnt = 0;
//3a200b11c201$00001101#

int main()
{
	char letter;
	char alphabet;
	code[97][0] = '0';
	code[98][0] = '1';
	code[98][1] = '0';
	code[99][0] = '1';
	code[99][1] = '1';
	int i=0;
	while (1)
	{
		scanf("%c", &letter);
		if (letter == '\n')
		{
			break;
		}
		buf_cnt[letter]++;
		if (buf_cnt[letter] == 1) //처음으로 들어온 알파벳
		{
			letter_cnt++; //알파벳 수 출력
		}
		buf[i] = letter;
		i++;
		//printf("%c", letter);
	}
	printf("%d", letter_cnt);
	i = 0;
	for(int j=0;j<256;j++)
	{
		if (buf_cnt[j] > 0)
		{
			printf("%c", j);
			printf("%d", buf_cnt[j]);
			printf("%s", code[j]);
		}
	}
	printf("$");
	i = 0;
	while (buf[i] != 0)
	{
		printf("%s", code[buf[i]]);
		i++;
	}
	printf("#");

	return 0;
}
