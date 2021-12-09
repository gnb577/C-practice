#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int* chess_board;
int solutioncnt = 0;

void initboard(int _chess_size);
void clearrow(int _r, int _chess_size);
int isok(int _r,int _c,int _chess_size);
void printboard(int _chess_size);
void checknext(int _r, int _chess_size);


void initboard(int _chess_size)
{
	memset(chess_board, 0, sizeof(int) * _chess_size * _chess_size);
}

void clearrow(int _r,int _chess_size)
{
	memset(&chess_board[_r*_chess_size], 0, sizeof(int)* _chess_size);
}

int isok(int _r, int _c,int _chess_size)
{
	for (int i = 0; i < _r; i++)
	{
		if (chess_board[i * _chess_size + _c] != 0)
		{
			return 0;
		}
	}

	for (int i = 0; i < _c; i++)
	{
		if (chess_board[_r * _chess_size + i] != 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < _r; i++)
	{
		for (int j = 0; j < _chess_size; j++)
		{
			if (abs(i - _r) == abs(j - _c) && chess_board[i * _chess_size + j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

void checknext(int _r, int _chess_size)
{
	int i;
	for (i = 0; i < _chess_size; i++)
	{
		clearrow(_r,_chess_size);
		if (isok(_r, i, _chess_size) == 1)
		{
			chess_board[_r * _chess_size + i] = 1;
			if (_r == _chess_size - 1)
			{
				printboard(_chess_size);
			}
			else
			{
				checknext(_r + 1,_chess_size);
			}
		}
	}
}

void printboard(int _chess_size)
{
	solutioncnt++;
	printf("------------ #%d solution ---------------------\n", solutioncnt);
	for (int i = 0; i < _chess_size; i++)
	{
		for (int j = 0; j < _chess_size; j++)
		{
			printf("%d ", chess_board[i * _chess_size + j]);
		}
		printf("\n");
	}
}
int main()
{
	int a;
	int chess_size;
	scanf_s("%d", &chess_size);
	chess_board = (int*)malloc(sizeof(int) * chess_size * chess_size);
	initboard(chess_size);
	for (a = 0; a < chess_size; a++)
	{
		clearrow(0,chess_size);
		if (isok(0,a,chess_size)==1)
		{
			chess_board[a] = 1;
			checknext(1,chess_size);
		}
	}
}