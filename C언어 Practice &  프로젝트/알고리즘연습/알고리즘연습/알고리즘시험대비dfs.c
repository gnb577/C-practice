#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


int size;

int top = -1;
int* stack;
int* visited;

void make_visited()
{
	visited = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		visited[i] = 0;
	}
	return;
}

void make_stack()
{
	stack = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		stack[i] = 0;
	}
	return;
}

void push(int push_num)
{
	if (top == size - 1)
	{
		printf("stack is full\n");
		return;
	}
	top++;
	stack[top] = push_num;
	return;

}

int pop()
{
	if (top == -1)
	{
		printf("stack is empty\n");
		return -999;
	}
	int ret = stack[top];
	top--;
	return ret;
}



typedef struct node
{
	int v;
	struct node* next;
}node;

node** graph = NULL;

void make_graph()
{
	graph = (node * *)malloc(sizeof(node*) * size);
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
	printf("visited %d \n", v);
	visited[v] = 1;
	push(v);
	while ((top==-1) == 0)
	{
		int next_vertex = -1;
		next_vertex = findnextvertex(stack[top]);
		if (next_vertex == -1)
		{
			pop();
		}
		else
		{
			printf("visited %d \n", next_vertex);
			visited[next_vertex] = 1;
			push(next_vertex);
		}
	}

}

void showadjacent(int _v)
{
	node* temp = graph[_v];
	while (temp != 0)
	{
		printf("%d is adjacent with %d\n", temp->v, _v);
		temp = temp->next;
	}

	return;

}

int main()
{
	scanf_s("%d", &size);

	make_visited();
	make_stack();
	make_graph();

	addedge(0, 3, 1);
	addedge(0, 2, 1);
	addedge(0, 1, 1);
	addedge(1, 2, 1);
	showadjacent(0);
	dodfs(0);
	return 0;
}