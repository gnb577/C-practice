#include<stdio.h>
#include<string.h>
#include<math.h>

#define sz 4

//체스판
int chess_board[sz][sz];

//발견한 솔류선의 개수
int solutioncnt = 0;

//체스판을 0으로 초기화
void initboard()
{

	memset(chess_board, 0, sizeof(int) * sz * sz);
	//같은 의미로 초기화
#if 0
	int i, j;
	for (i = 0; i < sz; i++)
	{
		for (j = 0; j < sz; j++)
		{
			chess_board[i][j] = 0;
		}
	}
#endif
}


//반환값 1:좌표(_r,_c)에 놓을 수 있다
//		 0:안되
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
		for (j = 0; j < sz; j++)
		{
			if ((abs(i - _r) == abs(j - _c)) && chess_board[i][j] != 0) // 열과 행의 차이가 동등하면서  해당자리에 퀸이 있을 경우
			{
				return 0;
			}
		}
	}

	return 1;

}

//행 r을 0으로 초기화
void clearRow(int _r)
{
	//int i;

	memset(&chess_board[_r][0], 0, sizeof(int) * sz);

#if 0
	for (i = 0; i < sz; i++)
	{
		chess_board[_r][i] = 0;
	}
#endif

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
//행 _r에 queen을 놓을 수 있는 위치를 찾는다

void checknext(int _r)
{
	int i;

	//행 _r에 모든 열에 대해서 모든 열에 대해서
	for (i = 0; i < sz; i++)
	{
		clearRow(_r);
		//좌표(_r,i)에 queen을 놓고
		if (isok(_r, i) == 1)
		{
			chess_board[_r][i] = 1;
			if (_r == sz - 1)
			{
				printsolution();// (chess_board판을 찍을 것)
			}
			else
			{
				checknext(_r+1);
			}
		}
	}

}

int main()
{

	int c; //열을 나타내는 변수

	initboard();

	for (c = 0; c < sz; c++)
	{
		clearRow(0);
		//(0,0) (0,1) (0,2) (0,3) 순으로 검사
		if (isok(0, c) == 1)
		{
			chess_board[0][c] = 1;
			checknext(1);
		}
	}
	return 0;
}