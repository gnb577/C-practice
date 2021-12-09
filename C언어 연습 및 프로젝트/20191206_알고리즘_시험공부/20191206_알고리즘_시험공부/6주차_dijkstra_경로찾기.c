#include<stdio.h>
#include<stdlib.h>

#define sz 4
#define sz2 5
#define sz3 8

int col_num;
int row_num;
int start_row;
int start_col;
int dest_row;
int dest_col;

typedef struct vertex
{
	int found; //경로를 찾앗는지?
	int dist; // dist
	int prev_row;
	int prev_col;
}vertex;

typedef struct coord
{
	int row;
	int col;
}coord;


vertex** dtable;
int** map;


void make_map()
{
	map = (int**)malloc(sizeof(int*) * row_num);
	for (int i = 0; i < row_num; i++)
	{
		map[i] = (int*)malloc(sizeof(int) * col_num);
		for (int j = 0; j < col_num; j++)
		{
			map[i][j] = 0;
		}
	}
}

void make_dtable()
{
	dtable = (vertex **)malloc(sizeof(vertex*) * row_num);
	for (int i = 0; i < row_num; i++)
	{
		dtable[i] = (vertex*)malloc(sizeof(vertex)* col_num);
		for (int j = 0; j < col_num; j++)
		{
			dtable[i][j].found = 0;
			dtable[i][j].dist = 99999;
			dtable[i][j].prev_col = -1;
			dtable[i][j].prev_row = -1;
		}
	}
}

struct coord findnext()
{
	int i, j;
	coord sm_coord;
	int smallest_dist = 99999;
	sm_coord.row = sm_coord.col = -1;
	for (i = 0; i < row_num; i++)
	{
		for (j = 0; j < col_num; j++)
		{
			if (dtable[i][j].found == 0 && dtable[i][j].dist < smallest_dist)
			{
				smallest_dist = dtable[i][j].dist;
				sm_coord.col = j;
				sm_coord.row = i;
			}
		}
	}
	return sm_coord;
}
void checkneighbor(int _r, int _c, int me_r, int me_c)
{
	if (_r >= 0 && _c >= 0 && _r < row_num && _c < col_num && dtable[_r][_c].found == 0 && map[_r][_c] != 1)
	{
		if (dtable[_r][_c].dist > dtable[me_r][me_c].dist + 1)
		{
			dtable[_r][_c].dist = dtable[me_r][me_c].dist + 1;
			dtable[_r][_c].prev_row = me_r;
			dtable[_r][_c].prev_col = me_c;
		}
	}
}

void checkallneighbors(int r, int c)
{
	checkneighbor(r - 1, c, r, c);
	checkneighbor(r, c-1, r, c);
	checkneighbor(r + 1, c, r, c);
	checkneighbor(r, c+1, r, c);
}

int main()
{
	scanf("%d %d", &row_num, &col_num);
	make_map();
	make_dtable();
	int ro, co, bo=0;
	while (!(bo == -1))
	{
		scanf("%d %d %d", &ro, &co, &bo);
		if (bo == 1)
		{
			map[ro][co] = 1;
		}
		if (bo == 2)
		{
			map[ro][co] = 2;
		}
	}

	scanf("%d %d", &start_row, &start_col);
	scanf("%d %d", &dest_row, &dest_col);

	dtable[start_row][start_col].found = 1;
	dtable[start_row][start_col].dist= 0;
	
	checkallneighbors(start_row, start_col);
	coord next;
	


	while (1)
	{
		next = findnext();
		if ((next.row == -1) && (next.col == -1))
		{
			break;
		}
		dtable[next.row][next.col].found = 1;
		checkallneighbors(next.row, next.col);

	}
	int count = 0;
	for (int i = 0; i < row_num; i++)
	{
		for (int j = 0; j < col_num; j++)
		{
			printf("%d ", dtable[i][j].dist);
		}
		printf("\n");
	}

	for (int i = 0; i < row_num; i++)
	{
		for (int j = 0; j < col_num; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}

	int prev_row, prev_col;
	while (1)
	{
	
		map[dest_row][dest_col] = 5;

		prev_row = dtable[dest_row][dest_col].prev_row;
		prev_col = dtable[dest_row][dest_col].prev_col;
		if (map[prev_row][prev_col] == 2)
		{
			count++;
		}
		if (prev_row == start_row && prev_col == start_col)
		{
			map[prev_row][prev_col] = 5;
			break;
		}
		dest_row = prev_row;
		dest_col = prev_col;
	}
	for (int i = 0; i < row_num; i++)
	{
		for (int j = 0; j < col_num; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	
	printf("%d", count);
	return 0;
}

/*
c
*/