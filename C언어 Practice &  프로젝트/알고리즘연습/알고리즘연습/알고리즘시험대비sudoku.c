#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define sz 9
/*
int sudoku[sz][sz] =
{
				4,0,7,5,0,0,0,0,8,
				 0,5,0,7,0,0,4,0,9,
				  0,0,6,0,0,4,0,7,0,
				  9,0,0,6,0,0,2,4,3,
				  0,4,0,9,0,3,0,8,0,
				  7,3,1,0,0,2,0,0,5,
				  0,2,0,8,0,0,7,0,0,
				   3,0,9,0,0,6,0,5,0,
				  5,0,0,0,0,7,3,0,4

};
*/

int sudoku[sz][sz] =
{
				4,0,7,5,0,0,0,0,8,
				 0,5,0,7,0,0,4,0,9,
				  0,0,6,0,0,4,0,7,0,
				  9,0,0,6,0,0,2,4,3,
				  0,0,0,0,0,0,0,0,0,
				  7,3,1,0,0,2,0,0,5,
				  0,2,0,8,0,0,7,0,0,
				   3,0,9,0,0,6,0,5,0,
				  5,0,0,0,0,7,3,0,4

};

int solutioncnt = 0;
int readonlysudoku[sz][sz];

void initreadonlysudoku()
{
	memcpy(readonlysudoku, sudoku, sizeof(int) * sz * sz);
}

void solvesudoku(int _r, int _c);
//_r,_c에 value가 들어갈 수 있는가? return 1 = 됨
int isok(int _r, int _c, int _value)
{
	//상하
	for (int i = 0; i < sz; i++)
	{
		if (sudoku[i][_c] == _value && i != _r)
		{
			return 0;
		}
	}

	//좌우
	for (int i = 0; i < sz; i++)
	{
		if (sudoku[_r][i] == _value && i != _c)
		{
			return 0;
		}
	}

	//region
	int region_row = _r / 3;
	int region_col = _c / 3;

	for (int i = region_row * 3; i <= region_row * 3 + 2; i++)
	{
		for (int j = region_col * 3; j <= region_col * 3 + 2; j++)
		{
			if (sudoku[i][j] == _value && i != _r && j != _c)
			{
				return 0;
			}
		}
	}
	//_r,_c에 값을 넣어도 좋다

	return 1;
}


void printsolution()
{
	solutioncnt++;
	printf("----------- solution # %d -----------------\n", solutioncnt);
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
}
void checknext(int _r, int _c)
{
	if (_r == sz - 1 && _c == sz - 1)
	{
		printsolution();
		return;
	}

	_c++;
	if (_c == sz)
	{
		_c = 0;
		_r++;
	}
	solvesudoku(_r, _c);



}


//r하고 c위치에 들어갈 숫자 정하기
void solvesudoku(int _r, int _c)
{
	//이미 수도쿠에 숫자가 주어졌는지 검산
	if (sudoku[_r][_c] > 0)
	{
		//다음 칸으로 이동해서 처리
		checknext(_r, _c);

	}
	// 아닌경우
	else
	{
		//1~9까지 대입해서 하나하나 체크
		for (int i = 1; i <= 9; i++)
		{
			memcpy(&sudoku[_r][_c], &readonlysudoku[_r][_c], sizeof(int) * sz * sz - sizeof(int) * (_r * sz + _c));
			if (isok(_r, _c, i) == 1)
			{
				sudoku[_r][_c] = i;
				//다음 칸으로 이동해서 처리
				checknext(_r, _c);
			}
		}
	}
}

int main()
{
	initreadonlysudoku();
	solvesudoku(0, 0);
	return 0;
}