#include<stdio.h>

int graph[4][4]; //0으로 초기화

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
			printf("%d is the adjacent vertex\n", i);
		}
	}
}
void main()
{
	addEdge(0, 1); // 0->1, 1->0
	addEdge(0, 2); // 0->2, 2->0

	showAdjacentVertex(0);
}