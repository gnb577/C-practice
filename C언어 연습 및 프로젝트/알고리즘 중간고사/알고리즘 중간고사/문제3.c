#include<stdio.h>
#include<stdlib.h>

int** graph;
int r_size = 0;
int c_size = 0;

void initgraph()
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

int checkneighbor(int _d, int _e)
{
	if (_d >= 0 && _d < r_size && _e >= 0 && _e < c_size)
	{
		if (graph[_d][_e] == 0)
		{
			return 1;
		}
	}
	return 0;
}

int checkneighbors(int d, int e)
{
	int sum = 0;
	sum = sum + checkneighbor(d + 1, e);
	sum = sum + checkneighbor(d - 1, e);
	sum = sum + checkneighbor(d, e + 1);
	sum = sum + checkneighbor(d, e - 1);
	return sum;
}



int main()
{
	int r_s, c_s;

	scanf("%d%d", &r_s, &c_s);
	r_size = r_s;
	c_size = c_s;
	initgraph();
	int a, b, c;

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
	int d, e;
	scanf("%d%d", &d, &e);
	int ans = checkneighbors(d, e);
	printf("%d", ans);

	return 0;

}
