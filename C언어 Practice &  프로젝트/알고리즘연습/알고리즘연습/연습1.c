#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int** chess_board;
int solutioncnt = 0;
int size;
void make_chessboard()
{
	chess_board = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++)
	{
		chess_board[i] = (int*)malloc(sizeof(int) * size);
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			chess_board[i][j] = 0;
		}
	}
}

void printsolution()
{
	solutioncnt++;
	printf("-----------------------\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d ", chess_board[i][j]);
		}
		printf("\n");
	}
}

int isok(int _r,int _c)
{
	for (int i = 0; i < _r; i++)
	{
		if (chess_board[i][_c] != 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < _c; i++)
	{
		if (chess_board[_r][i] != 0)
		{
			return 0;
		}
	}

	for (int i = 0; i < _r; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (chess_board[i][j] != 0 && abs(i - _r) == abs(j - _c))
			{
				return 0;
			}
		}
	}
	return 1;
}

void clearrow(int _r)
{
	for (int i = 0; i < size; i++)
	{
		chess_board[_r][i] = 0;
	}
}

void checknext(int _r)
{
	for (int i = 0; i < size; i++)
	{
		clearrow(_r);
		if (isok(_r, i) == 1)
		{
			chess_board[_r][i] = 1;
			if (_r == size - 1)
			{
				printsolution();
				return;
			}
			else
			{
				checknext(_r + 1);
			}
		}
	}
}



int main()
{
	int n;
	scanf_s("%d", &n);
	size = n;
	make_chessboard();
	checknext(0);
	return 0;
}
