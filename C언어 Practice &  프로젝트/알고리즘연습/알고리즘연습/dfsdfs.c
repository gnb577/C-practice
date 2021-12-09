#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	int v;
	struct node* next;
}node;

node** graph;
int* stack;
int* visited;
int top = -1;
int size;



void makegraph()
{
	graph = (node * *)mallloc(sizeof(node*) * size);
	{
		for (int i = 0; i < size; i++)
		{
			graph[i] = 0;
		}
	}
}




void makevisited()
{
	visited = (int *)mallloc(sizeof(int) * size);
	{
		for (int i = 0; i < size; i++)
		{
			visited[i] = 0;
		}
	}
}

void makestack()
{
	stack = (int*)mallloc(sizeof(int) * size);
	{
		for (int i = 0; i < size; i++)
		{
			stack[i] = 0;
		}
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
	node *temp = graph[v];
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
int main()
{

}