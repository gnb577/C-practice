#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VERTEX_NUM 7

int* graph1;

int* visited1;
int* visited2;

int* queue;
int* stack;

typedef struct node
{
	int num;
	struct node* next;
}node;

node* graph2;

int top = -1;
int front = 0;
int rear = 0;

void enque(int v)
{
	if ((rear + 1) % VERTEX_NUM == front)
	{
		return;
	}
	queue[rear] = v;
	rear = (rear + 1) % VERTEX_NUM;
	return;
}


int deque()
{
	if (rear == front)
	{
		return -999;
	}
	int ret = queue[front];
	front = (front + 1) % VERTEX_NUM;
	return ret;
}

void push(int v)
{
	if (top == VERTEX_NUM - 1)
	{
		return;
	}
	top++;
	stack[top] = v;
	return;
}

int pop()
{
	if (top == -1)
	{
		return -999;
	}
	int ret = stack[top];
	top--;
	return ret;
}

void addEdge1(int v1, int v2)
{
	graph1[v1 * VERTEX_NUM + v2] = 1;
	graph1[v2 * VERTEX_NUM + v1] = 1;
}

void addEdge2(int v1, int v2)
{
	node* new_node = (node*)malloc(sizeof(node));
	return;
}

int search_queue(int v)
{
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		queue[i] = v;
		return 1;
	}
	return 0;
}

void dobfs(int v)
{
	enque(v);
	while (front != rear)
	{
		int k = deque();
		int i = 0;
		if (visited1[i] == 0)
		{
			printf("bfs is visited %d ", k);
			visited1[k] = 1;
			for (i = VERTEX_NUM * k; i < (k + 1) * VERTEX_NUM; i++)
			{
				if (graph1[i] == 1)
				{
					int real_i = i - k * VERTEX_NUM;
					if (visited1[real_i] == 0 && search_queue(real_i) == 0)
					{
						enque(real_i);
					}
				}
			}
		}
	}
}

int main()
{
	graph1 = (int*)malloc(sizeof(int) * VERTEX_NUM * VERTEX_NUM);
	graph2 = (node*)malloc(sizeof(node) * VERTEX_NUM * VERTEX_NUM);
	for (int i = 0; i < VERTEX_NUM * VERTEX_NUM; i++)
	{
		graph1[i] = 0;
	}

	visited1 = (int*)malloc(sizeof(int) * VERTEX_NUM);
	visited2 = (int*)malloc(sizeof(int) * VERTEX_NUM);
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		visited1[i] = 0;
		visited2[i] = 0;
	}
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		//graph2[i]->num = i;
	}
	queue = (int*)malloc(sizeof(int) * VERTEX_NUM);
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		queue[i] = 0;
	}
	addEdge1(0, 1);
	addEdge1(0, 2);
	addEdge1(0, 3);
	addEdge1(4, 2);
	addEdge1(2, 3);

	dobfs(2);
	return 0;
}