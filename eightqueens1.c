#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


#define sz 8

int chess_board[sz][sz];

void initboard()
{
	memset(chess_board, 0, sizeof(int) * sz * sz);
}

int isok(int _data3, int _data4)
{
	int i, j, k = 0;
	for (i = 0; i < sz; i++)
	{
		if (chess_board[i][_data4] != 0 && i != _data3)
		{
			return 1;
		}
	}

	for (i = 0; i < sz; i++)
	{
		if (chess_board[_data3][i] != 0 && i != _data4)
		{
			return 1;
		}
	}

	for (i = 0; i < sz; i++)
	{
		for (j = 0; j < sz;j++)
		{
			if ((abs(i - _data3) == abs(j - _data4)) && chess_board[i][j] != 0 && (i != _data3 && j != _data4))
			{
				return 1;
			}
		}
	}
	return 0;
}


int main()
{
	int data1, data2;
	int data3, data4;
	int ans1 = 0;
	int ans2 = 1;
	scanf_s("%d %d", &data1, &data2);
	scanf_s("%d %d", &data3, &data4);
	initboard();

	chess_board[data1][data2] = 1;
	chess_board[data3][data4] = 1;

	int ans = isok(data3, data4);

	printf("%d", ans);
	/*
	if (ans == 1)
	{
		printf("%d", ans1);
	}
	else
	{
		printf("%d", ans2);
	}
	*/
	return 0;
}