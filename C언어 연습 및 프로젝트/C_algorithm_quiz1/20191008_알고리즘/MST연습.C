#include <stdio.h>
#include <stdlib.h>

#define VERTEX_NUM 7

int* graph = 0;
int* visited = 0;
int head = 0;
int tail = 0;
int que[VERTEX_NUM];


void enque(int v)
{
	if ((tail + 1) % VERTEX_NUM == head)
	{
		printf("queue full\n");
		return;
	}
	que[tail] = v;
	tail = (tail + 1) % VERTEX_NUM;
}

int deque()
{

	if (head == tail)
	{
		return -999;
	}
	int temp = que[head];
	head = (head + 1) % VERTEX_NUM;
	return temp;
}


void addEdge(int v1, int v2)
{
	graph[v1 * VERTEX_NUM + v2] = 1;
	graph[v2 * VERTEX_NUM + v1] = 1;
}


int search_que(int v)
{
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		if (que[i] == v)
		{
			return 1;
		}
	}
	return 0;
}

void doBFS(int v)
{
	enque(v);
	while (head != tail)
	{
		int k = deque();
		int i = 0;
		if (visited[k] == -1)
		{
			printf("BFS visited %d \n", k);
			visited[k] = 1;
			for (i = VERTEX_NUM * k; i < (k + 1) * VERTEX_NUM; i++)
			{
				if (graph[i] == 1)
				{
					int real_i = i - k * VERTEX_NUM;
					if (visited[real_i] == -1 && search_que(real_i) == 0)
					{
						enque(real_i);
					}
				}
			}
		}
	}
	return;
}


int main(void)
{
	int i;
	graph = (int*)malloc(sizeof(int) * VERTEX_NUM * VERTEX_NUM);
	for (i = 0; i < VERTEX_NUM * VERTEX_NUM; i++)
	{
		graph[i] = 0;
	}

	addEdge(0, 1);
	addEdge(0, 2);
	addEdge(0, 3);
	addEdge(4, 2);
	addEdge(2, 3);

	for (i = 0; i < VERTEX_NUM; i++)
	{
		que[i] = -1;
	}

	visited = (int*)malloc(sizeof(int) * VERTEX_NUM);
	for (int j = 0; j < VERTEX_NUM; j++)
	{
		visited[j] = -1;
	}


	doBFS(2);



	return 0;
}

/*
addedge(0,1,1,0);
addedge(0,2,3,0);
addedge(0,4,5,0);
addedge(1,2,2,0);
addedge(1,4,4,0);
addedge(2,4,6,0);
addedge(2,3,7,0);
addedge(3,4,8,0);
*/