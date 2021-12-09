#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SZ 100
#define ascii 256

char code[256][100];
//char* code[256];
char buf[100];
int buf_cnt[ascii];
char decode_buf[ascii] = { 0, };
char make_code[100];

int main()
{
	int num;
	char code_code;
	char letter;
	char number;
	int k = 0;
	scanf("%d", &num);
	scanf("%c", &code_code);
	int w = num;
	while (1)
	{
		if (code_code == '$') 
		{
			break;
		}

		scanf("%c", &number);
		buf_cnt[code_code] = (int)number;
		/*
		int buf_counting = 0;
		while(buf_counting != number)
		{
			buf[k] = code_code;
			buf_counting++;
			k++;
		}
		*/
		char _code = code_code;
		int i = 0;

		while (1)
		{
			num--;
			scanf("%c", &code_code);
			if (code_code == '$')
			{
				break;
			}
			if (code_code < '0' || code_code > '1')
			{
				code[_code][i] = 0;
				break;
			}
			else
			{
				code[_code][i] = code_code;
				i++;
			}
		}
		printf("%s\n", code[_code]);
	}

	int j = 0;
	int flag = 0;
	int i = 0;
	int cnt = 0;
	while (1)
	{
		scanf("%c", &number);
		if (number == '#')
		{
			break;
		}
		make_code[j] = number; //number를 추가하고
		make_code[j + 1] = 0; //null을 끝자락에 붙힘
		//printf("%s\n", make_code);
		for (int k = 0; k < 256; k++)
		{
			//모든 코드 테이블을 뒤져서
			flag = 0;
			
			for (int o = 0; o < j+1; o++) //현재 makecode의 길이 만큼
			{
				if (make_code[o] == code[k][o])
				{
					flag++;
				}
			}
			
			if (j+1 == flag)
			{
				printf("%c", k);
				for (int i = 0; i < 100; i++)
				{
					make_code[i] = 0;
				}
				//flag = 0;
				j = -1;
				break;
			}
			
		}
		j++;
	}
	return 1;
}
//3a200b11c201$00001101#