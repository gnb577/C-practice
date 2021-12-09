#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

void initreadonlysudoku();
void printsolution();
int isok(int _r, int _c,int _value);
void checknext(int _r, int _c);
void solvesudoku(int _r, int _c);


void initreadonlysudoku()
{
	memcpy(readonlysudoku, sudoku, sizeof(int) * sz * sz);
}

int isok(int _r, int _c, int _value)
{
	int i;
	for (i = 0; i < sz; i++)
	{
		if (i != _r && sudoku[i][_c] == _value)
		{
			return 0;
		}
	}

	for (i = 0; i < sz; i++)
	{
		if (i != _c && sudoku[_r][i] == _value)
		{
			return 0;
		}
	}

	int tr = _r / 3;
	int tc = _c / 3;

	for (i = 3*tr; i <= 3*tr+2; i++)
	{
		for (int j = 3 * tc; j <= 3 * tc + 2; j++)
		{
			if(i != _r && j != _c && sudoku[i][j] == _value)
			return 0;
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
	else
	{
		_c++;
		if (_c == sz)
		{
			_c = 0;
			_r++;
		}
		solvesudoku(_r,_c);
	}
}

void solvesudoku(int _r, int _c)
{
	if (sudoku[_r][_c] > 0)
	{
		checknext(_r, _c);
	}
	else
	{
		for (int i = 1; i <= sz; i++)
		{
			memcpy(&sudoku[_r][_c], &readonlysudoku[_r][_c], sizeof(int) * sz * sz - sizeof(int) * (_r * sz + _c));
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
	solvesudoku(0, 0);
	return 0;
}