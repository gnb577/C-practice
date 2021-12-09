#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int vertex_num;
int edge_num;
int sum = 0;
typedef struct node
{
	int num;
	int weight;
	struct node* next;
}node;

typedef struct edge
{
	int from;
	int to;
	int w;
}edge;

int cycle[100];
node* graph[100];
edge edges[100];

void samegroup(int v1, int v2)
{
	int g1 = edges[v1].from;
	int g2 = edges[v2].from;
	int smaller, bigger;
	if (g1 > g2)
	{
		bigger = g1;
		smaller = g2;
	}
	else
	{
		smaller = g1;
		bigger = g2;
	}
		for (int i = 0; i < vertex_num; i++)
		{
			if (edges[i].from == bigger)
			{
				edges[i].from = smaller;
			}
		}
}

void addedge(int v1, int v2, int w)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->num = v2;
	new_node->weight = w;
	new_node->next = 0;

	node* temp = graph[v1];
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
}

void swap(int a, int b)
{
	edge temp = edges[a];
	edges[a] = edges[b];
	edges[b] = temp;
}

void sortedge()
{
	int i;
	int edge_count=0;
	for (i = 0; i < vertex_num; i++)
	{
		node* temp = graph[i];
		while (temp != 0)
		{
			
			edges[edge_count].from = i;
			edges[edge_count].to = temp->num;
			edges[edge_count].w = temp->weight;
			if (edge_count == vertex_num-1) //°í¹Î
			{
				return;
			}
			edge_count++;
			temp = temp->next;
			
		}
	}
	int x, y;
	for (y = 0; y < edge_num; y++)
	{
		for (x = 0; x < edge_num - 1 - y; x++)
		{
			if (edges[x].w > edges[x + 1].w)
			{
				swap(x, x + 1);
			}
		}
	}
	
}

int summation(int a)
{
	sum = sum + a;
	return sum;
}

void domst()
{
	int i;
	int edge_number=0;
	
			
	while (edges[].from != edges[].to)
	{
		while()
		sum = summation(edges[].w);
		samegroup(edges[].from,edges[].to);
	}
		
}

int main()
{
	int number;
	int ver1, ver2, wei;
	scanf_s("%d ", &number);
	vertex_num = number;
	edge_num = vertex_num * (vertex_num - 1) / 2;
	int flag = 0;
	for (int i = 0; i < edge_num; i++)
	{
		scanf_s("%d %d %d", &ver1, &ver2, &wei);
		addedge(ver1,ver2,wei);
		if (ver1 == -1 && ver2 == -1 && wei == -1)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		scanf_s("%d %d %d", &ver1, &ver2, &wei);
	}
	for (int i = 0; i < 100; i++)
	{
		cycle[i] = i;
	}

	sortedge();
	domst();
	printf("%d", sum);
	return 0;
}