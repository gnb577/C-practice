#include<stdio.h>
#include<stdlib.h>

unsigned int** graph;
unsigned int r_size;
unsigned int c_size;

void initgraph()
{
	graph = (unsigned int**)malloc(sizeof(unsigned int*) * r_size);
	for (int i = 0; i < r_size; i++)
	{
		graph[i] = (unsigned int*)malloc(sizeof(unsigned int) * c_size);
	}
	for (unsigned int i = 0; i < r_size; i++)
	{
		for (unsigned int j = 0; j < c_size; j++)
		{
			graph[i][j] = 0;
		}
	}
}

int main()
{
	unsigned int r_s, c_s;

	scanf_s("%u %u", &r_s, &c_s);
	r_size = r_s;
	c_size = c_s;
	initgraph();
	int a, b, c;

	while (1)
	{
		scanf_s("%u %u %u", &a, &b, &c);
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
	scanf_s("%u %u", &d, &e);
	printf("%u", graph[d][e]);
	return 0;

}
