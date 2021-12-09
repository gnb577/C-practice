#include<stdio.h>
#include<string.h>

int graph[4][4];

void addEdge(int v1, int v2)
{
	graph[v1][v2] = 1;
	graph[v2][v1] = 1;
}


void showAdjacentVertex(int v)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		if (graph[v][i] == 1)
		{
			printf("%d is the adjacent vertext\n", i);
		}
	}
}
void main()
{
	addEdge(0, 1);
	addEdge(0, 2);
	showAdjacentVertex(0);
}