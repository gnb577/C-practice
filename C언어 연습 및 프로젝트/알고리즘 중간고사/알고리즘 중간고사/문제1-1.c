#include<stdio.h>
#include<stdlib.h>

unsigned int** graph;
unsigned int r_size = 0;
unsigned int c_size = 0;

void initgraph()
{
	graph = (unsigned int**)malloc(sizeof(unsigned double*) * r_size);
	for (int i = 0; i < r_size; i++)
	{
		graph[i] = (unsigned int*)malloc(sizeof(unsigned int) * c_size);
	}
	for (int i = 0; i < r_size; i++)
	{
		for (int j = 0; j < c_size; j++)
		{
			graph[i][j] = 0;
		}
	}

}

int main()
{
	unsigned int r_s, c_s;
	scanf("%d%d", &r_s, &c_s);
	r_size = r_s;
	c_size = c_s;
	initgraph();
	unsigned int a, b, c;

	while (1)
	{
		scanf("%d%d%d", &a, &b, &c);

		if (a == -1 && b == -1 && c == -1)
		{
			break;
		}
		graph[a][b] = -1;

	}
	/*
	for (int i = 0; i < r_size; i++)
	{
		for (int j = 0; j < c_size; j++)
		{
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}
	*/
	unsigned int d, e;
	scanf("%d%d", &d, &e);
	printf("%d", graph[d][e]);
	/*
	if (graph[d][e] == -1)
	{
		printf("-1");
	}
	else
	{
		printf("0");
	}
	*/
	return 0;

}
