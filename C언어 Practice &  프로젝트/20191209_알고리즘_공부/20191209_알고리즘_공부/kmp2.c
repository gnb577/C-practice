#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int* calculate(char* _pattern_str)
{
	int j = 0;
	int *_lps;
	int pattern_len = strlen(_pattern_str);
	_lps = (int*)malloc(sizeof(int) * pattern_len);
	memset(_lps, 0, sizeof(int) * pattern_len);
	for (int i = 1; i < pattern_len; i++)
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
	char pattern_str[100] = "ABABABABC";
	char target_str[100] = "ABABABABBABABABABCABABABABC";
	int* lps;
	lps = calculate(pattern_str);
	int pattern_len = strlen(pattern_str);
	int target_len = strlen(target_str);
	int j = 0;
	for (int i = 0; i < pattern_len; i++)
	{
		printf("%d-----%d\n", i, lps[i]);
	}
	for (int i = 0; i < target_len; i++)
	{
		while (j > 0 && target_str[i] != pattern_str[j])
		{
			j = lps[j - 1];
		}
		if (target_str[i] == pattern_str[j])
		{
			if (j == pattern_len - 1)
			{
				printf("%d 에서 찾았으요.", i - pattern_len);
				j = lps[j];
			}
			j++;
		}
	}
	
}