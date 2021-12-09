#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int** chess_board;
int size;
int solutioncnt = 0;

void make_chess_board()
{
	chess_board = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++)
	{
		chess_board[i] = (int*)malloc(sizeof(int) * size);
	}
	//memset(chess_board, 0, sizeof(int) * size * size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
		  chess_board[i][j] = 0;
		}
	}
}

int isok(int _r, int _c)
{
	for (int i = 0; i < _r; i++)
	{
		if (chess_board[i][_c] == 1)
		{
			return 0;
		}
	}
	for (int i = 0; i < _c; i++)
	{
		if (chess_board[_r][i] == 1)
		{
			return 0;
		}
	}
	for (int i = 0; i < _r; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (abs(i - _r) == abs(j - _c) && chess_board[i][j] != 0)
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
	int i;
	for (i = 0; i < size; i++)
	{
		clearrow(_r);
		if (isok(_r, i) == 1)
		{
			chess_board[_r][i] = 1;
			if (_r == size - 1)
			{
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
	int num;
	scanf_s("%d", &num);
	size = num;
	make_chess_board();
	for (int k = 0; k < size; k++)
	{
		clearrow(0);
	00000	if (isok(0, k) == 1)
		{
			chess_board[0][k] = 1;
			checknext(1);
		}
	}
	return 0;
}