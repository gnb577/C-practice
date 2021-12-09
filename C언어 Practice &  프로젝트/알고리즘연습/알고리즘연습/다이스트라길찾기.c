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

vertex vertexes[sz][sz] = { 0, };

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

void checkneighbor(int _row, int _col, int me_row, int me_col)
{

	int 
	if (vertexes[_row][_col].dist < vertexes[me_row][me_col].dist + 1)
	{

	}
}

coord findnext()
{
	int smallest	coord next;
	next.col
	for (i = 0; i < size; i)
	{
		if(vertexes[i][j].found ==0 && vertexs[i][j].dist < smallest

	}
}