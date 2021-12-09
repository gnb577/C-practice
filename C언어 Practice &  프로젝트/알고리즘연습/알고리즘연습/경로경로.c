#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define sz 8

typedef struct coord
{
	int row;
	int col;
}coord;

typedef struct node
{
	int prev_col;
	int prev_row;
	int dist;
	int found;
}node;

node graph[sz][sz];

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

void initgraph()
{
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			graph[i][j].found = 0;
			graph[i][j].prev_col = -1;
			graph[i][j].prev_row = -1;
			graph[i][j].dist = 99999;
		}
	}
}

void checkneighbor(int _row,int _col,int me_row,int me_col)
{
	if (_row >= 0 && _col >= 0 && _row < sz && _col < sz && map[_row][_col] == '.' && graph[_row][_col].found == 0&&
		graph[_row][_col].dist > graph[me_row][me_col].dist + 1)
	{
		graph[_row][_col].dist = graph[me_row][me_col].dist + 1;
		graph[_row][_col].prev_col = me_col;
		graph[_row][_col].prev_row = me_row;
	}
}

void checkallneighbors(int me_row,int me_col)
{
	checkneighbor(me_row-1, me_col, me_row, me_col);
	checkneighbor(me_row+1, me_col, me_row, me_col);
	checkneighbor(me_row, me_col-1, me_row, me_col);
	checkneighbor(me_row, me_col+1, me_row, me_col);
}

coord findnext()
{
	coord next;
	int smallest_dist = 99999;
	next.row = next.col = -1;
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			if (graph[i][j].found == 0 && graph[i][j].dist < smallest_dist)
			{
				smallest_dist = graph[i][j].dist;
				next.row = i;
				next.col = j;
			}
		}
	}
	return next;

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
	initgraph();
	graph[0][0].found = 1;
	graph[0][0].dist = 0;
	checkallneighbors(0, 0);
	while (1)
	{
		
		next_vertex = findnext();
		if (next_vertex.col == -1 && next_vertex.row == -1)
		{
			break;
		}
		graph[next_vertex.row][next_vertex.col].found = 1;
		checkallneighbors(next_vertex.row,next_vertex.col);
		
	}

	int r = sz - 1;
	int c = sz - 1;
	
	while (!(r == 0 && c == 0))
	{
		map[r][c] = '^';
		int prev_col, prev_row;
		prev_row = graph[r][c].prev_row;
		prev_col = graph[r][c].prev_col;
		r = prev_row;
		c = prev_col;
	}
	map[0][0] = '^';
	showmap();
	return 0;
}