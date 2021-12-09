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
			vertexes[i][j].dist = 99999;
			vertexes[i][j].prev_row = -1;
			vertexes[i][j].prev_col = -1;
			vertexes[i][j].found = 0;
		}
	}
}


void checkneighbor(int _row, int _col, int me_row, int me_col)
{
	if (_row)
	{
		vertexes[_row][_col].dist = ver + 1;
		vertexes[_row][_col].prev_col = _col;
	}
}

void checkallneighbors(int me_row, int me_col)
{
	checkneighbor(me_row + 1, me_col, me_row, me_col);
	checkneighbor(me_row - 1, me_col, me_row, me_col);
	checkneighbor(me_row, me_col - 1, me_row, me_col);
	checkneighbor(me_row, me_col + 1, me_row, me_col);
}

coord findnextvertex()
{
	coord smallest_vertex;
	int smallest_distance = 99999;
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			if (vertexes[i][j].found == 0 && vertexes[i][j].dist < smallest_distance)
			{
				smallest_distance = vertexes[i][j].dist;
				smallest_vertex.col = j;
				smallest_vertex.row = i;
			}
		}
	}
	return smallest_vertex;
}



