#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define sz 4
#define sz2 8
int chessboard[sz][sz];

int isok(int r, int c)
{
	for (int i = 0; i < r; i++)
	{
		if (chessboard[i][c] != 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < c; i++)
	{
		if (chessboard[r][i] != 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			if ((abs(i - r) == abs(j - c)) && chessboard[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

void checknext(int r)
{
	for (int i = 0; i < sz; i++)
	{
		for (int k = 0; k < sz; k++)
		{
			chessboard[r][k] = 0;
		}
		if (isok(r, i) == 1)
		{
			chessboard[r][i] = 1;
			if (r == sz - 1)
			{
				printf("--------------------\n");
				for (int i = 0; i < sz; i++)
				{
					for (int j = 0; j < sz; j++)
					{
						printf("%d ", chessboard[i][j]);
					}
					printf("\n");
				}
				printf("--------------------");
			}
			else
			{
				checknext(r + 1);
			}
		}
	}
		
}
int main()
{
	int c;
	for (c = 0; c < sz; c++)
	{
		for (int k = 0; k < sz; k++)
		{
			chessboard[0][k] = 0;
		}
		if (isok(0, c) == 1)
		{
			chessboard[0][c] = 1;
			checknext(1);
		}
	}
}