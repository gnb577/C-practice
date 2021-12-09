#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	int v;
	struct node* next;
}node;

node** graph;
int* queue;
int* stack;
int* visited;
int top = -1;
int size;
int front = 0;
int rear = 0;

void makegraph()
{
	graph = (node * *)malloc(sizeof(node*) * size);
	{
		for (int i = 0; i < size; i++)
		{
			graph[i] = 0;
		}
	}
}


void makevisited()
{
	visited = (int*)malloc(sizeof(int) * size);
	{
		for (int i = 0; i < size; i++)
		{
			visited[i] = 0;
		}
	}
}

void makestack()
{
	stack = (int*)malloc(sizeof(int) * size);
	{
		for (int i = 0; i < size; i++)
		{
			stack[i] = 0;
		}
	}
}


void makequeue()
{
	queue = (int*)malloc(sizeof(int) * size);
	{
		for (int i = 0; i < size; i++)
		{
			queue[i] = 0;
		}
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
	}
}

int deque()
{
	if (rear == front)
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

int findnextvertex(int v)
{
	node* temp = graph[v];
	while (temp != 0)
	{
		if (visited[temp->v] == 0)
		{
			return temp->v;
		}
		temp = temp->next;
	}
	return -1;
}

void dodfs(int v)
{
	printf("visited %d\n", v);
	visited[v] = 1;
	push(v);
	while (top != -1)
	{
		int next_vertex = -1;
		next_vertex = findnextvertex(v);
		if (next_vertex == -1)
		{
			pop();
		}
		else
		{
			visited[next_vertex] = 1;
			findnextvertex(next_vertex);
			push(next_vertex);
		}
	}

}
void dodfs(int v)
{
	printf("visited %d\n", v);
	visited[v] = 1;
	enque(v);
	while (front != rear)
	{
		int next_vertex = -1;
		next_vertex = findnextvertex(v);
		if (next_vertex == -1)
		{
			deque();
		}
		else
		{
			visited[next_vertex] = 1;
			findnextvertex(next_vertex);
			enque(next_vertex);
		}
	}

}
int main()
{

}