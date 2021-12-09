#include<stdio.h>
#include<stdlib.h>

int size;
int solutioncnt;
int** chessboard;


void makechessboard()
{
	chessboard = (int **)malloc(sizeof(int*) * size);
	{
		for (int i = 0; i < size; i++)
		{
			chessboard[i] = (int*)malloc(sizeof(int) * size);
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			chessboard[i][j] = 0;
		}
	}
}

int isok(int _r, int _c)
{
	for (int i = 0; i < _r; i++)
	{
		if (chessboard[i][_c] != 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < _c; i++)
	{
		if (chessboard[_r][i] != 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < _r; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (chessboard[i][j] != 0 && abs(i-_r)==abs(j-_c))
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
		chessboard[_r][i] = 0;
	}
}

void printsolution()
{
	solutioncnt++;
	printf("%d----------------------\n", solutioncnt);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d ",chessboard[i][j]);
		}
		printf("\n");
	}
	return;
}

void checknext(int _r)
{
	for (int i = 0; i < size; i++)
	{
		clearrow(_r);
		if (isok(_r, i) == 1)
		{
			chessboard[_r][i] = 1;
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

}