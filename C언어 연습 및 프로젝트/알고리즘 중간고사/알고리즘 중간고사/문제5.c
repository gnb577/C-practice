#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int found;
	int prev_col;
	int prev_row;
	int dist;
}node;

node** vertexes;

typedef struct coord
{
	int row;
	int col;
}coord;

int** graph;
int r_size = 0;
int c_size = 0;

int sum = 0;

void initvertexes()
{
	vertexes= (node**)malloc(sizeof(node*) * r_size);
	for (int i = 0; i < r_size; i++)
	{
		vertexes[i] = (node*)malloc(sizeof(node) * c_size);
	}
	for (int i = 0; i < r_size; i++)
	{
		for (int j = 0; j < c_size; j++)
		{
			vertexes[i][j].found = 0;
			vertexes[i][j].prev_col = -1;
			vertexes[i][j].prev_row = -1;
			vertexes[i][j].dist = 99999;
		}
	}
}


void initgraph()//map
{
	graph = (int**)malloc(sizeof(int*) * r_size);
	for (int i = 0; i < r_size; i++)
	{
		graph[i] = (int*)malloc(sizeof(int) * c_size);
	}
	for (int i = 0; i < r_size; i++)
	{
		for (int j = 0; j < c_size; j++)
		{
			graph[i][j] = 0;
		}
	}
}



void checkneighbor(int _d, int _e,int me_d,int me_e)
{
	if (_d >= 0 && _d < r_size && _e >= 0 && _e < c_size && (graph[_d][_e]== 0 ||graph[_d][_e]==5) && vertexes[_d][_e].dist > vertexes[me_d][me_e].dist+1)
	{
		if (graph[_d][_e] == 5)
		{
			sum = sum + 1;
		}
		vertexes[_d][_e].dist = vertexes[me_d][me_e].dist + 1;
		vertexes[_d][_e].prev_col = me_e; 
		vertexes[_d][_e].prev_row = me_d;
		
	}
	return 0;
}

void checkneighbors(int d, int e)
{
	
	checkneighbor(d + 1, e,d,e);
	checkneighbor(d - 1, e,d,e);
	checkneighbor(d, e + 1,d,e);
	checkneighbor(d, e - 1,d,e);
}

coord findnext()
{
	coord next;
	next.col = next.row = -1;
	int smallest_dist = 99999;
	for (int i = 0; i < r_size; i++)
	{
		for (int j = 0; j < c_size; j++)
		{
			if (vertexes[i][j].found == 0 && vertexes[i][j].dist < smallest_dist)
			{
				smallest_dist = vertexes[i][j].dist;
				next.col = j;
				next.row = i;
			}
		}
	}
	return next;
}

void dodijkstra(int r,int c,int q,int w)
{
	
	vertexes[r][c].found = 1;
	vertexes[r][c].dist = 0;
	checkneighbors(r, c);
	coord next_vertex;
	while (1)
	{
		next_vertex = findnext();
		if (next_vertex.row == q && next_vertex.col == w)
		{
			//printf("%d", vertexes[next_vertex.row][next_vertex.col].dist);
			break;
		}
			vertexes[next_vertex.row][next_vertex.col].found = 1;
			checkneighbors(next_vertex.row, next_vertex.col);
		
	}

}



int main()
{
	int r_s, c_s;
	scanf("%d%d", &r_s, &c_s);
	r_size = r_s;
	c_size = c_s;
	initgraph();
	initvertexes();

	int a, b, c;

	while (1)
	{
		scanf("%d%d%d", &a, &b, &c);

		if (a == -1 && b == -1 && c == -1)
		{
			break;
		}
		if (c == 1)
		{
			graph[a][b] = -1;
		}
		if (c == 2)
		{
			graph[a][b] = 5;
		}

	}
	
	int d, e;
	int f, g;
	scanf("%d%d", &d, &e);
	scanf("%d%d", &f, &g);
	dodijkstra(d, e, f, g);

	while (1)
	{
		int prev_col;
		int prev_row;
		graph[f][g] = 5;
		prev_col = vertexes[f][g].prev_col;
		prev_row = vertexes[f][g].prev_row;
		f = prev_row;
		g = prev_col;
		if (prev_row == d && prev_col == e)
		{
			break;
		}
	}
	printf("%d", sum);
	/*
	for (int i = 0; i < r_size; i++)
	{
		for (int j = 0; j < c_size; j++)
		{
			printf("%d ", vertexes[i][j].dist);
		}
	}
*/
	
	
	return 0;

}
