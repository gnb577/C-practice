#include<stdio.h>
#include<stdlib.h>

int graph[20][20];
int r_size=0;
int c_size=0;

void initgraph()
{
	for (int i = 0; i < r_size; i++)
	{
		for (int j = 0; j < c_size; j++)
		{
			graph[i][j] = 0;
		}
		printf("\n");
	}

}

int main()
{
	int r_s,c_s;

	scanf_s("%d %d", &r_s,&c_s);
	r_size = r_s;
	c_size = c_s;
	initgraph();
	int a,b,c;

	while(1)
	{
		scanf_s("%d%d%d", &a, &b, &c);

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
	scanf_s("%d%d", &d,&e);
	if (graph[d][e] == -1)
	{
		printf("-1");
	}
	else
	{
		printf("0");
	}
	return 0;
	
}
