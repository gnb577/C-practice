#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
int vertex_num;
int edge_num;
int start_num;

typedef struct node
{
	int v;
	struct node* next;
}node;

node* head = 0;
int* visited;
node** graph=0;
int stack[100];
int top = -1;

void push(int v)
{
	if (top == vertex_num- 1)
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
		return -1;
	}
	int ret = stack[top];
	top--;
	return ret;
}

void make_graph()
{
	graph = (node**)malloc(sizeof(node*) * vertex_num);
	for (int i = 0; i < vertex_num; i++)
	{
		graph[i] = 0;
	}
}

void make_visited()
{
	visited = (int*)malloc(sizeof(int) * edge_num);
	for (int i = 0; i < vertex_num; i++)
	{
		visited[i] = 0;
	}
}

void addsll(int v1, int v2,int k)
{
	node* new_node = (node*)malloc(sizeof(node));
	node* temp = graph[v1];
	new_node->v = v2;
	new_node->next = 0;
	if (graph[v1] == 0)
	{
		graph[v1] = new_node;
		return;
	}
	else
	{
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
	if (k == 1)
	{
		addsll(v2, v1, 0);
	}
	return;
}

int findnext(int v)
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

int cnt = 0;
void dodfs(int v)
{
	printf("%d ", v+1);
	push(v);
	int next_vertex = -1;
	while(top!=-1)
	{
		next_vertex = findnext(stack[top]);
		if (next_vertex == -1)
		{
			pop();
		}
		else
		{
			printf("%d ", next_vertex+1);
			visited[next_vertex] = 1;
			push(next_vertex);
		}
	}

}
int main()
{
	scanf("%d %d %d", &vertex_num, &edge_num, &start_num);
	make_graph();
	make_visited();
	int data1, data2;
	for (int i = 0; i < edge_num; i++)
	{
		scanf("%d %d", &data1, &data2);
		addsll(data1 -1 , data2-1,1);
	}

	dodfs(start_num-1);

}