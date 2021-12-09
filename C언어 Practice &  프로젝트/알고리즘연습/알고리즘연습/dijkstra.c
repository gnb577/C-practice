#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int size;
int** chess_board;
int solutioncnt = 0;

void makechessboard();
int isok(int _r, int _c);
void checknext(int _r);
void clearrow(int _r);

void makechessboard()
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

int isok(int _r, int _c)
{
	int i, j;

	// 위쪽 방향을 검사
	for (i = 0; i < _r; i++)
	{
		if (chess_board[i][_c] != 0)
		{
			//같은 열을 검사해서 뭐가 있다면 문제가 있음
			return 0;
		}
	}

	// 왼쪽 방향을 검사
	for (i = 0; i < _c; i++)
	{
		if (chess_board[_r][i] != 0)
		{
			//같은 열을 검사해서 뭐가 있다면 문제가 있음
			return 0;
		}
	}

	// 대각선 방향을 검사 (위쪽 대각선)
	for (i = 0; i < _r; i++)
	{
		for (j = 0; j < size; j++)
		{
			if ((abs(i - _r) == abs(j - _c)) && chess_board[i][j] != 0) // 열과 행의 차이가 동등하면서  해당자리에 퀸이 있을 경우
			{
				return 0;
			}
		}
	}

	return 1;

}

void clearrow(int _r)
{
	int i;
	for (i = 0; i < size; i++)
	{
		chess_board[_r][i] = 0;
	}

}

void printsolution()
{
	solutioncnt++;
	printf("-------solution # %d -------\n", solutioncnt);
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			printf("%d ", chess_board[i][j]);
		}
		printf("\n");
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
	makechessboard();
	
	checknext(0);
	return 0;
}