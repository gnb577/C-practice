#include<stdio.h>
#include<stdlib.h>

int **chessboard
int solutioncnt

isok
checknext(_r)
{
	for (int i = 0; i < size; i++)
	{
		clearrow(_r);
		if (isok(_r, i) == 1)
		{
			chessboard[_r][i] = 1;
			if(_r == sz-1)
		}
		printsolution();
		else
		{
			check_next(_r + 1);
		}
		{

		}
	}
}

int main()
{
	size = n;
	initchessboard;
	checknext(0);

}