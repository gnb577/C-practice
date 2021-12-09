#include<stdio.h>


#define Vertex_num 7

int* graph;
int* stack;
int* visited;
int top;

void push(int v)
{
	if (top == Vertex_num - 1)
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
	top--;
	return stack[top + 1];
}

void addEdge(int v1, int v2)
{
	graph[v1 * Vertex_num + v2] = 1;
	graph[v2 * Vertex_num + v1] = 1;
}

void doDFS(int v)
{
	int temp_vertex;
	int f;

	push(v);

	while (1)
	{
		temp_vertex = pop();

		if (temp_vertex == -999)
		{
			return;
		}

		visitied[temp_vertex] = 1;

		for (int i = Vertex_num * temp_vertex; i < Vertex_num * (temp_vertex + 1); i++)
		{
			if (graph[i] == 1)
			{
				real_num = i - Vertex_num * temp_vertext;
				if (visited[real_num] == 0)
				{
					push(real_num);
				}
			}
		}
	}
}


int main()
{
	graph = (int*)malloc(sizeof(int) * Vertex_num * Vertex_num);
	stack = (int*)malloc(sizeof(int) * Vertex_num);
	visited = (int*)malloc(sizeof(int) * Vertex_num);

	for (int i = 0; i < Vertex_num; i++)
	{
		stack[i] = 0;
		visited[i] = 0;
	}
	for (int i = 0; i < Vertex_num * Vertex_num; i++)
	{
		graph[i] = 0;
	}

	addEdge(0, 1);
	addEdge(0, 2);
	addEdge(0, 3);
	addEdge(4, 2);
	addEdge(2, 3);
	doDFS(0);

}