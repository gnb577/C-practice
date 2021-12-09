#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int* queue;
int* graph;
int front = 0;
int rear = 0;
int* visited;
int vertex_num;

void enque(int v)
{
	if ((rear + 1) % vertex_num == front)
	{
		return;
	}
	queue[rear] = v;
	rear = (rear + 1) % vertex_num;
	return;
	
}

int deque()
{
	if (rear == front)
	{
		return -999;
	}
	int ret = queue[front];
	front = (front + 1) % vertex_num;
	return ret;
}

void addedge(int v1, int v2)
{
	graph[v1 * vertex_num + v2] = 1;
	graph[v2 * vertex_num + v1] = 1;
}

int search(int v)
{
	for (int i = 0; i < vertex_num; i++)
	{
		if (queue[i] == v)
		{
			return 1;
		}
	}
	return 0;
}

void dobfs(int v)
{
	enque(v);
	int k = 0;
	while (rear == front)
	{
		k = deque();
		visited[k] = 1;
		for (int i = vertex_num * k; i < vertex_num * (k + 1); i++)
		{
			if (graph[i] == 1)
			{
				int real_i = i - k * vertex_num;
				if (visited[real_i] == 0 && search(real_i) == 0)
				{
					enque(real_i);
				}
			}
		}
		
	}
}

void doanswer(int v)
{
	int i = 0;
	for (i = 0; i < vertex_num; i++)
	{
		if (visited[i] == -2)
		{
			break;
		}
	}
	if (visited[i - 1] == v)
	{
		printf("1");
	}
	else
	{
		printf("0");
	}
	return;
}

int main()
{
	int data=0;
	int input1 = 0;
	int input2 = 0;
	int com1 = 0;
	int com2 = 0;

	
	scanf("%d",&data);
	vertex_num = data;
	graph = (int*)malloc(sizeof(int) * vertex_num *vertex_num);
	queue = (int*)malloc(sizeof(int) * vertex_num);
	visited = (int*)malloc(sizeof(int) * vertex_num);
	for (int i = 0; i < vertex_num; i++)
	{
		graph[i] = -2;
	}

	for (int i = 0; i < vertex_num; i++)
	{
		queue[i] = -2;
	}
	for (int i = 0; i < vertex_num; i++)
	{
		visited[i] = -2;
	}

	for (int i = 0; i < vertex_num; i++)
	{
		scanf("%d %d", &input1, &input2);
		if (input1 == -1 && input2 == -1)
		{
			break;
		}
		addedge(input1, input2);
	}
	scanf("%d %d", &com1, &com2);
	dobfs(com1);
	doanswer(com2);
	return 0;
}