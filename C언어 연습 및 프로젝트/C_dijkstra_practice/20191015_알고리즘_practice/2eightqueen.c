#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define sz 4

int solutioncnt = 0;
int chess_board[sz][sz];

void initboard();
int isok(int _r, int _c);
void checknext(int _r);
void printsolution();
void clearrow(int _r);

void initboard()
{
	memset(chess_board, 0, sizeof(int) * sz * sz);
}

void clearrow(int _r)
{
	memset(chess_board[_r], 0, sizeof(int) * sz);
}

int isok(int _r, int _c)
{
	int i = 0;
	for (i = 0; i < _r; i++)
	{
		if (chess_board[i][_c] != 0)
		{
			return 0;
		}
	}

	for (i = 0; i < _c; i++)
	{
		if (chess_board[_r][i] != 0)
		{
			return 0;
		}
	}
	int j = 0;

	for (i = 0; i < _r; i++)
	{
		for (j = 0; j < sz; j++)
		{
			if (abs(i - _r) == abs(j - _c) && chess_board[i][j] == 1)
			{
				return 0;
			}
		}
	}
	return 1;
}


void checknext(int _r)
{
	int i;
	for (i = 0; i < sz; i++)
	{
		clearrow(_r);
		if (isok(_r, i) == 1)
		{
			chess_board[_r][i] = 1;
			if (_r == sz - 1)
			{
				printsolution();
			}
			else
			{
				checknext(_r + 1);
			}
		}
	}
}

void printsolution()
{
	solutioncnt++;
	printf("-------solution # %d -------\n", solutioncnt);
	int i, j;

	for (i = 0; i < sz; i++)
	{
		for (j = 0; j < sz; j++)
		{
			printf("%d ", chess_board[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int c;
	for (c = 0; c < sz; c++)
	{
		clearrow(0);
		if (isok(0, c) == 1)
		{
			chess_board[0][c] = 1;
			checknext(1);
		}

	}
}