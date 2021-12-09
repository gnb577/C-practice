#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define sz 9

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

int solutioncnt = 0;
int readonlysudoku[sz][sz];

void initreadonlysudoku()
{
	memcpy(readonlysudoku, sudoku, sizeof(int) * sz * sz);
}

int isok(int _r, int _c, int _value);
void checknext(int _r, int _c);
void solve(int _r, int _c);
void printsolution();

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

void checknext(int _r,int _c)
{
	if (_r == sz - 1 && _c == sz - 1)
	{
		printsolution();
		return;
	}
	else
	{
		_c++;
		if (_c == sz)
		{
			_c = 0;
			_r++;
		}
		solve(_r, _c);
	}
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

void solve(int _r, int _c)
{
	int i;
	if (sudoku[_r][_c] > 0)
	{
		checknext(_r, _c);
	}
	else {
		for (i = 1; i <= sz; i++)
		{
			memcpy(&sudoku[_r][_c], &readonlysudoku[_r][_c], sizeof(int) * (sz * sz - _r * _c));
			if (isok(_r, _c, i) == 1)
			{
				sudoku[_r][_c] = i;
				checknext(_r, _c);
			}
		}
	}
}

int main()
{
	initreadonlysudoku();
	solve(0, 0);
	return 0;
}