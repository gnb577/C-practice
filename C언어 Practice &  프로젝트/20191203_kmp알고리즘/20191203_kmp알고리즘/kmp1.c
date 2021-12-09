#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LEN 100

int* calculate_lps(char* _pattern_str)
{
	//pattern을 index별 값할당하기
	int pattern_len;
	int* _lps = 0;
	int i, j = 0;

	pattern_len = strlen(_pattern_str);

	//lps배열 생성
	_lps =(int*)malloc(sizeof(int) * pattern_len);

	//lps초기화
	memset(_lps, 0, sizeof(int) * pattern_len);


	//lps 계산
	for (i = 1; i < pattern_len; i++)
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
	int i, j=0;
	int target_len;
	int pattern_len;
	int* lps = 0;
	//target string
	//char target_str2[LEN] = "ABABABABBABABABABC";
	char target_str[LEN] = "ABABABABBABABABABCABABABABC";
	//pattern string
	char pattern_str[LEN] = "ABABABABC";
	//char pattern_str2[LEN] = "ABCABABCA";
	target_len = strlen(target_str);
	pattern_len = strlen(pattern_str);
	lps = calculate_lps(pattern_str);

	for (i = 0; i < pattern_len; i++)
	{
		printf("%d --> %d \n", i, lps[i]);
	}
	printf("-----start string matching of %s to %s \n", pattern_str, target_str);
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
				printf("found matching at %d\n", i - pattern_len + 1);
				j = lps[j];
			}
			else
			{
				j++;
			}
		}
	}
	return 0;
}