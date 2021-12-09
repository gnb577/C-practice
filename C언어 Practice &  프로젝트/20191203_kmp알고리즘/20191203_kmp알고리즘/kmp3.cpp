#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int* calculate_lps(char* _pattern_str)
{
	int pattern_len = strlen(_pattern_str);
	int i, j = 0;
	int* _lps = (int*)malloc(sizeof(int) * pattern_len);
	memset(_lps, 0, sizeof(int) * pattern_len);

	for (i = 1; i < pattern_len; i++)
	{
		while (j > 0 && pattern_len[i] != pattern_len[j])
		{
			j = lps[j - 1];
		}
		if (_pattern_str[i] == _pattern_str[j])
		{
			lps[i] = j;
			j++;
		}
	}
}

int main()
{
	int i = 0;
	int j = 0;

	int* lps = 0;
	char* target_str = 0;
	char* pattern_str = 0;
	target_str = (char*)malloc(sizeof(char) * 100);
	pattern_str = (char*)malloc(sizeof(char) * 100);
	lps = calculate_lps(pattern_str);
	int pattern_len = strlen(pattern_str);
	int target_len = strlen(target_str);

	for (i = 0; i < pattern_len; i++)
	{
		printf("%d -------> %d", i, lps[i]);
	}
	for (i = 0; i < target_len; i++)
	{
		while (j > 0 && target_str[i] != pattern_str[j])
		{
			j = lps[j - 1];
		}
		if (target_str[i] == pattern_str[j])
		{
			if (j == pattern_len - 1)
			{
				printf("found");
				j = lps[j];
			}
		else
		{
			j++;
		}
		}
	}


}