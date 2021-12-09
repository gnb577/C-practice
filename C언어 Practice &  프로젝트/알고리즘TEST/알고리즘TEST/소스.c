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
node** graph = 0;
int queue[100];
int top = -1;
int _head = 0;
int tail = 0;
void enque(int v)
{
	if (_head == (tail+1) % vertex_num)
	{
		return;
	}
	queue[tail] = v;
	tail = (tail + 1) % vertex_num;
	return;
}

int deque()
{
	if (_head == tail)
	{
		return -1;
	}
	int ret = queue[_head];
	_head = (_head + 1) % vertex_num;
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

void addsll(int v1, int v2, int k)
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
	printf("%d ", v + 1);
	visited[v] = 1;
	enque(v);
	int next_vertex = -1;
	while (_head != tail)
	{
		if (_head == tail)
		{
			break;
		}
		next_vertex = findnext(queue[_head]);
		if (next_vertex == -1)
		{
			deque();
		}
		else
		{
			printf("%d ", next_vertex + 1);
			visited[next_vertex] = 1;
			enque(next_vertex);
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
		addsll(data1 - 1, data2 - 1, 1);
	}
	dodfs(start_num - 1);
}
/*
4 5 1
1 2
1 3
2 3
2 1
4 1
1 3 2
*/