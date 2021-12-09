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

void initvertexes()
{
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			vertexes[i][j].prev_row = -1;
			vertexes[i][j].prev_col = -1;
			vertexes[i][j].dist = 99999;
			vertexes[i][j].found = 0;
		}
	}
}

coord findnext()
{
		int smallest_dist = 99999;
		coord smallest_vertex;
		smallest_vertex.row = smallest_vertex.col = -1;
		for (int i = 0; i < sz; i++)
		{
			for (int j = 0; j < sz; j++)
			{
				if (vertexes[i][j].found == 0 && vertexes[i][j].dist < smallest_dist)
				{
					smallest_dist = vertexes[i][j].dist;
					smallest_vertex.row = i;
					smallest_vertex.col = j;
				}
			}
		}
		return smallest_vertex;
}

void checkneighbor(int _row, int _col, int me_row, int me_col)
{
	
			if (map[_row][_col] == '.' &&_row >= 0 && _col >= 0 && _row < sz && _col < sz && vertexes[_row][_col].found == 0 && vertexes[_row][_col].dist > vertexes[me_row][me_col].dist + 1)
			{
				vertexes[_row][_col].dist = vertexes[me_row][me_col].dist + 1;
				vertexes[_row][_col].prev_row = me_row;
				vertexes[_row][_col].prev_col = me_col;
			}	
}

void checkallneighbors(int me_row, int me_col)
{
	checkneighbor(me_row - 1, me_col, me_row, me_col);
	checkneighbor(me_row + 1, me_col, me_row, me_col);
	checkneighbor(me_row , me_col-1, me_row, me_col);
	checkneighbor(me_row, me_col+1, me_row, me_col);
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
	
	
	coord next_vertex;
	initvertexes();
	
	vertexes[0][0].dist = 0;
	vertexes[0][0].found = 1;
	checkallneighbors(0, 0);
	while (1)
	{
		next_vertex = findnext(); 
		
			if (next_vertex.col == -1 && next_vertex.row == -1)
			{
				break;
			}
			vertexes[next_vertex.row][next_vertex.col].found = 1;
			checkallneighbors(next_vertex.row, next_vertex.col);
		
	}

	int r, c;
	r = sz - 1;
	c = sz - 1;

	while (!(r == 0 && c == 0))
	{
		int prev_col, prev_row;
		map[r][c] = '^';
		prev_col = vertexes[r][c].prev_col;
		prev_row = vertexes[r][c].prev_row;
		r = prev_row;
		c = prev_col;
	}
	map[0][0] = '^';
	showmap();
	return 0;
}