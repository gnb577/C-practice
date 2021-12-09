#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LEN 100

int* calculate_lps(char* _pattern_str)
{
	int* _lps;
	int pattern_len;
	pattern_len = strlen(_pattern_str);
	_lps = _lps = (int*)malloc(sizeof(int) * pattern_len);
	memset(_lps, 0, sizeof(int) * pattern_len);
	int j = 0;
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
	int i = 0;
	int j = 0;

	char* target_str;
	target_str = (char*)malloc(sizeof(char) * 100);
	scanf("%s", target_str);

	char* pattern_str;
	pattern_str = (char*)malloc(sizeof(char) * 100);
	scanf("%s", pattern_str);
	int* lps;
	lps = calculate_lps(pattern_str);
	int target_len = strlen(target_str);
	int pattern_len = strlen(pattern_str);
	for (i = 0; i < pattern_len; i++)
	{
		printf("%d---->%d\n", i, lps[i]);
	}
	for (int i = 0; i < target_len; i++)
	{
		while (j > 0 && target_str[i] != pattern_str[j])
		{
			j = lps[j - 1];
		}
		if (target_str[i] == pattern_str[j])
		{
			if(j == pattern_len-1)
			{
				printf("found matching %d\n", i - pattern_len + 1);
			}
			else
			{
				j++;
			}
		}
	}


}