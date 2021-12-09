#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define sz 8

typedef struct coord
{
	int row;
	int col;
}coord;

typedef struct vertex
{
	int prev_row;
	int prev_col;
	int found;
	int dist;
}vertex;

vertex vertexes[sz][sz];

char map[sz][sz] =
{
	{'.','#','.','#','.','.','.','#'},
	{'.','#','.','#','.','#','.','#'},
	{'.','#','.','#','.','#','.','.'},
	{'.','#','.','.','.','#','#','.'},
	{'.','#','.','#','#','#','#','.'},
	{'.','#','.','#','.','#','.','.'},
	{'.','#','.','.','.','#','.','#'},
	{'.','.','.','#','.','#','.','.'}
};

void initvertex()
{
	int i, j;
	for (i = 0; i < sz; i++)
	{
		for (j = 0; j < sz; j++)
		{
			vertexes[i][j].dist = 999999;
			vertexes[i][j].prev_row = -1;
			vertexes[i][j].prev_col = -1;
			vertexes[i][j].found = 0;
		}
	}
}


void checkneighbor(int _row, int _col, int me_row, int me_col)
{
	if (_row >= 0 && _col >= 0 && _row < sz && _col<sz && vertexes[_row][_col].found == 0 && map[_row][_col] == '.' &&
		vertexes[_row][_col].dist > vertexes[me_row][me_col].dist + 1)
	{
		vertexes[_row][_col].dist = vertexes[me_row][me_col].dist + 1;
		vertexes[_row][_col].prev_row = me_row;
		vertexes[_row][_col].prev_col = me_col;
	}
}

void checkallneighbors(int me_row, int me_col)
{
		checkneighbor(me_row+1, me_col, me_row, me_col);
		checkneighbor(me_row-1, me_col, me_row, me_col);
		checkneighbor(me_row, me_col-1, me_row, me_col);
		checkneighbor(me_row, me_col+1, me_row, me_col);
}

coord findnextvertex()
{
	int i, j;
	coord sm_coord;
	int smallest_dist = 999999;
	sm_coord.row = sm_coord.col = -1;
	for (i = 0; i < sz; i++)
	{
		for (j = 0; j < sz; j++)
		{
			if (vertexes[i][j].found == 0 && vertexes[i][j].dist < smallest_dist)
			{
				sm_coord.row = i;
				sm_coord.col = j;
				smallest_dist = vertexes[i][j].dist;
			}
		}
	}
	return sm_coord;

}

void showmap()
{
	int i, j;
	for (i = 0; i < sz; i++)
	{
		for (j = 0; j < sz; j++)
		{
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	coord next;
	initvertex();
	vertexes[0][0].dist = 0;
	vertexes[0][0].found = 1;
	checkallneighbors(0, 0);
	while (1)
	{
		next = findnextvertex();
		if (next.row == -1 && next.col == -1)
		{
			break;
		}
		vertexes[next.row][next.col].found = 1;
		checkallneighbors(next.row, next.col);
	}

	int r, c;
	r = sz - 1;
	c = sz - 1;
	while (1)
	{
		int prev_row, prev_col;
		map[r][c] = '^';

		prev_row = vertexes[r][c].prev_row;
		prev_col = vertexes[r][c].prev_col;

		if (prev_row == 0 && prev_col == 0)
		{
			map[prev_row][prev_col] = '^';
			break;
		}
		r = prev_row;
		c = prev_col;
	}
	showmap();
	return 0;
}