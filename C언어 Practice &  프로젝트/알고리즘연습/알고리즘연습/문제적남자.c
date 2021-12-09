#include<stdio.h>
#include<stdlib.h>

int* graph;
int solutioncnt;
int size;
int sum = 0;
void makegraph()
{
	graph = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		graph[i] = 0;
	}
}

void graphclear(int line)
{
	for (int i = 0; i <= line; i++)
	{
		graph[i] = 0;
	}
}

unsigned int number(int line)
{
	unsigned int temp = 0;
	for (int i = 0; i < line; i++)
	{
		temp = 10 * temp + graph[i];
	}
	return temp;
}

unsigned int isok(int v, int line)
{
	for (int i = 0; i < line; i++)
	{
		if (graph[i] == v)
		{
			return 0;
		}
	}
	unsigned int temp = number(line);
	if ((10 * temp + v) % (line + 1) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


void printsolution(void)
{
	solutioncnt++;
	printf("-------------Solution # %d-----------\n", solutioncnt);
	printf("%d\n", number(size));
	for (int i = 0; i < size; i++)
	{
		printf("%d", graph[i]);
	}
	printf("\n");
}

void checknext(int line)
{
	for (int i = 0; i < size; i++)
	{
		if (isok(i, line) == 1)
		{
			graph[line] = i;
			if (line == size - 1)
			{
				printsolution();
			}
			else
			{
				checknext(line + 1);
			}
		}
	}
}

int main()
{
	int n;
	scanf_s("%d", &n);
	size = n;
	makegraph();
	for (int i = 1; i < size; i++)
	{
		graph[0] = i;
		sum = i;
		checknext(1);
	}

}