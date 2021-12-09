#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int** graph=NULL;
int size;

void make_graph()
{
	if (size == NULL)
	{
		return;
	}
	graph = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++)
	{
		graph[i] = (int*)malloc(sizeof(int) * size);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			graph[i][j] = 0;
		}
	}
	return;
}
void addedge(int _r, int _c)
{
	graph[_r][_c] = 1;	
	graph[_c][_r] = 1;
}

void showadjacent(int _v)
{
	for (int i = 0; i < size; i++)
	{
		if (graph[_v][i] == 1)
		{
			printf("%d is adjacent with %d\n", i, _v);
			
		}
	}
}

int main()
{
	scanf_s("%d", &size);
	int i, j,k=0;
	make_graph();
	addedge(0, 3);
	addedge(0, 2);
	addedge(0, 1);
	addedge(1, 2);
	showadjacent(0);
	/*
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}
	*/
	return 0;
}