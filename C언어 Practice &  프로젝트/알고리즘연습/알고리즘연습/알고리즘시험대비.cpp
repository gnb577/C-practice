#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int **graph;

void addedge()

int main()
{
	int n;
	scanf("%d", &n);
	graph = (int*)malloc(sizeof(int) * n * n);
	for (int i = 0; i < n; i++)
	{
		for (j = 0; j < n; n++)
		{
			graph[i][j] = i * n + j;
 		}
	}
	for (int i = 0; i < n; i++)
	{
		for (j = 0; j < n; n++)
		{
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}
	return 0;
}