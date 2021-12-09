#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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


int readonlysudoku[sz][sz];
int solutioncnt = 0;

void initreadonlysudoku()
{
	memcpy(readonlysudoku, sudoku, sizeof(int) * sz * sz);
}
void solvesudoku(int _r, int _c);

int isok(int _r, int _c, int _value)
{
	int i;
	for (i = 0; i < sz; i++)
	{
		if (sudoku[_r][i] == _value && i != _c)
		{
			return 0;
		}
	}
	for (i = 0; i < sz; i++)
	{
		if (sudoku[i][_c] == _value && i != _r)
		{
			return 0;
		}
	}
	int x, y;
	x = _r / 3;
	y = _c / 3;
	for (int i = x * 3; i <= x * 3 + 2; i++)
	{
		for (int j = y * 3; j <= y * 3 + 2; j++)
		{
			if (sudoku[i][j] == _value && i != _r && j != _c)
			{
				return 0;
			}
		}
	}
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

void solvesudoku(int _r, int _c)
{
	if (sudoku[_r][_c] > 0)
	{
		checknext(_r, _c);
		return;
	}
	for (int i = 1; i <= sz; i++)
	{
		memcpy(&sudoku[_r][_c], &readonlysudoku[_r][_c], sizeof(int) * (sz * sz - _r * sz + _c));
		if (isok(_r, _c, i) == 1)
		{
			sudoku[_r][_c] = i;
			checknext(_r, _c);
		}
	}
}

int main()
{
	initreadonlysudoku();
	solvesudoku(0, 0);
	return 0;
}