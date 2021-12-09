#include<stdio.h>
#include<stdlib.h>

int* visited;
int* stack;
int* queue;
int top = -1;
int rear = 0;
int front = 0;


int size;

typedef struct node
{
	int v;
	struct node* next;
}node;

node** graph;

int size;

void makegraph()
{
	graph = (node**)malloc(sizeof(node*) * size);
	for (int i = 0; i < size; i++)
	{
		graph[i] = 0;
	}
}


void addedge(int v1, int v2, int doreverse)
{
	node* new_node = (node*)malloc(sizeof(node));
	node* temp = graph[v1];

	new_node->v = v2;
	new_node->next = 0;

	if (temp == 0)
	{
		graph[v1] = new_node;
	}
	else
	{
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
	if (doreverse == 1)
	{
		addedge(v2, v1, 0);
	}
	return;
}

void makevisited()
{
	visited = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		visited[i] = 0;
	}
}

void makestack()
{
	stack = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		stack[i] = 0;
	}
}

void makequeue()
{
	queue = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		queue[i] = 0;
	}
}

void enque(int v)
{
	if ((rear + 1) % size == front)
	{
		return;
	}
	else
	{
		queue[rear] = v;
		rear = (rear + 1) % size;
		return;
	}
}

int deque()
{
	if ( rear% size == front)
	{
		return -999;
	}
	else
	{
		int ret = queue[front];
		front = (front + 1) % size;
		return ret;
	}
}


void push(int v)
{
	if (top == size - 1)
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

int findnext(int v)
{
	node* temp = graph[v];
	while (temp != 0)
	{
		if (visitied[temp->v] == 0)
		{
			return temp->v;
		}
		temp = temp->next;
	}
	return -1;
}

void dodfs(int v)
{
	printf("visited %d \n",v);
	visited[v] = 1;
	int next_vertex = -1;
	push(v);
	while (top != -1)
	{
		next_vertex = findnext(v);
		if (next_vertex == -1)
		{
			pop();
		}
		visited[next_vertex] = 1;
		printf("visited %d \n", next_vertex);
		findnextvertex(next_vertex);
		push(next_vertex);
	}
}

int main()
{
	scanf_s("%d", &size);

	makevisited();
	makestack();
	makegraph();
	makequeue();
	addedge(0, 3, 1);
	addedge(0, 2, 1);
	addedge(0, 1, 1);
	addedge(1, 2, 1);
	showadjacent(0);
	dodfs(0);
	return 0;
}