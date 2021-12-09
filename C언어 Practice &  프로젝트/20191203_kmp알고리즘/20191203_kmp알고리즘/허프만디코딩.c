#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int* calculate_lps(char* _pattern_str)
{
	int* _lps;
	int len = strlen(_pattern_str);
	_lps = (int*)malloc(sizeof(int) * len);
	memset(_lps, 0, sizeof(int) * len);
	int j = 0;
	for (int i = 1; i < len; i++)
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
	lps = calculate_lps(pattern_str);
	for (int i = 0; i < strlen(pattern_str); i++)
	{
		printf("%d------%d\n", i, lps[i]);
	}
	int j = 0;
	for (int i = 0; i < strlen(target_str); i++)
	{
		while (j > 0 && target_str[i] != pattern_str[j])
		{
			j = lps[j - 1];
		}
		if (target_str[i] == pattern_str[j])
		{
			if (j == strlen(pattern_str) - 1)
			{
				printf("¤¸¤¸\n");
				j = lps[j];
			}
			j++;
		}
	}


}