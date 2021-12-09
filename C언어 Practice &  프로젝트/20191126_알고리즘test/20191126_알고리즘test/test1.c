#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//+48

#define SZ 100
#define ascii 256

char code[256][100];
char buf[100];
int buf_cnt[ascii];
char decode_buf[ascii] = { 0, };
char make_code[100];

int main()
{
	int num;
	char code_code=0;
	char letter;
	char number;
	
	scanf("%d", &num);
	int w = num;
	while (1)
	{
		if (code_code == '$')
		{
			break;
		}
		if (w == num)
		{
			scanf("%c", &letter);
		}
			scanf("%c", &number);
		if (w == num)
		{
			buf_cnt[letter] = number - 48;
		}
		if (w != num)
		{
			buf_cnt[code_code] = number - 48;
		}
		printf(" %d ", buf_cnt[letter]);
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
				code[letter][i] = 0;
				break;
			}
			else
			{
				code[letter][i] = code_code;
				i++;
			}
		
		}
		printf("%s\n", code[letter]);
	}

		
	
	   char number2=0;
		int j=0;
		while (1)
		{
			scanf("%c", &number2);
			if (number2 == '#')
			{
				break;
			}
			make_code[j] = number2;
			make_code[j + 1] = 0;
			for (int k = 0; k < 256; k++)
			{
				if (strcmp(make_code, code[k]) == 0)
				{
					printf("%c", k);
					j = 0;
					for (int m = 0; m < 100; m++)
					{
						make_code[m] = 0;
					}
				}
			}
			j++;
		}

}