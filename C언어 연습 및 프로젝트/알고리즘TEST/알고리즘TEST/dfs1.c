#include<stdio.h>
#include<string.h>

char target_str[500];
char pattern_str[100][500];
int number;
int sum = 0;
int* calculate(char* _pattern_str)
{
	int i = 0;
	int j = 0;
	int *_lps;
	
	int len = strlen(_pattern_str);
	_lps = (int*)malloc(sizeof(int) * len);
	memset(_lps, 0, sizeof(int) * len);
	for (i = 0; i < len; i++)
	{
		while (j > 0 && _pattern_str[i] != _pattern_str[j])
		{
			j = _lps[j - 1];
		}
		if (_pattern_str[i] == _pattern_str[j])
		{
			j++;
			_lps[i] = j;
		}

	}
	return _lps;
}

int main()
{
	scanf("%s", target_str);
	scanf("%d", &number);
	for (int i = 0; i < number; i++)
	{
		scanf("%s", pattern_str[i]);
	}
	int target_len = strlen(target_str);
	
	int pattern_len[100];
	for (int i = 0;i < 100; i++)
	{
		pattern_len[i] = 0;
	}
	for (int i = 0; i < number; i++)
	{
		pattern_len[i] = strlen(pattern_str[i]);
	}
	int *lps[100];
	for (int i = 0; i < 100; i++)
	{
		lps[i] = 0;
	}
	for (int i = 0; i < number; i++)
	{
		lps[i] = calculate(pattern_str[i]);
	}
	int j = 0;
	//int idx = 0;
	for (int u = 0; u < number; u++)
	{
		j = 0;
		for (int i = 0; i < target_len; i++)
		{
			while (j > 0 && target_str[i] != pattern_str[u][j])
			{
				j = lps[u][j - 1];
			}
			if (target_str[i] == pattern_str[u][j])
			{
				if (j == pattern_len[u] - 1)
				{
					int l = j; 
					sum = sum + strlen(pattern_str[u]);
					//printf("%d %d",u, i - j);
					for (int o = l - (strlen(pattern_str[u]) + 1); o <= l; o++)
					{
						target_str[o] = '&';
					}
					break;
					//j = lps[j];
				}
				else
				{
					j++;
				}
			}
		}
	}
	printf("%d", sum);
}