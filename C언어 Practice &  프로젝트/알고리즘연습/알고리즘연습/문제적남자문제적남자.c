#include<stdio.h>
#include<stdlib.h>

int* graph;
int solutioncnt=0;
int size;


void makegraph()
{
	graph = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		graph[i] = 0;
	}
}

void cleargraph(int length)
{
	for (int i = 0; i < length; i++)
	{
		graph[i] = 0;
	}
}

unsigned int summation(int length)
{
	unsigned int sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum = 10*sum + graph[i];
	}
	return sum;
}

int isok(int v, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (graph[i] == v)
		{
			return 0;
		}
	}

	unsigned int _sum = summation(length);
	if ((10 * _sum + v) % (length + 1) == 0)
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
	//printf("%d\n", sum(size));
	for (int i = 0; i < size; i++)
	{
		printf("%d", graph[i]);
	}
	printf("\n");
}

void checknext(int length)
{
	for(int i = 0; i < size; i++)
	{
		cleargraph(length);
		if (isok(i, length) == 1)
		{
			graph[length] = i;
			if (length == size - 1)
			{
				printsolution();
			}

			else
			{
				checknext(length + 1);
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
		if (isok(i, 1) == 1)
		{
			checknext(1);
		}
	}
	
}