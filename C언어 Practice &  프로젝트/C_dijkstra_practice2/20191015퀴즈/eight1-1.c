#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define sz 8

int chess_board[sz][sz];

void initboard()
{
	memset(chess_board, 0, sizeof(int) * sz * sz);
}

int isok(int _data1, int _data2, int _data3, int _data4)
{
	int i, j, k = 0;
	for (i = 0; i < sz; i++)
	{
		if (chess_board[_data1][i] == 1 || chess_board[i][_data2])
		{
4
return 1;
		}
	}

	

	for (i = 0; i < sz; i++)
	{
		for (j = 0; j < sz; j++)
		{
			if (abs(i - _data1) == abs(j - _data2) && chess_board[i][j] != 0)
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
	scanf_s("%d %d", &data1, &data2);
	scanf_s("%d %d", &data3, &data4);
	initboard();

	chess_board[data1][data2] = 1;
	chess_board[data3][data4] = 1;
	int ans = isok(data1, data2, data3, data4);
	printf("%d", ans);
	return 0;
}