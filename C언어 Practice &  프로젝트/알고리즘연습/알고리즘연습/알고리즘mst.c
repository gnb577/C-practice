#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


int size;
int* cycle_detection;
typedef struct node
{
	int v;
	int weight;
	struct node* next;
}node;

typedef struct edge
{
	int from;
	int to;
	int w;
	
}edge;

node** graph;
edge* edges;

void make_cycle_detection()
{
	cycle_detection = (int *)malloc(sizeof(int) * size*(size-1)/2);
	for (int i = 0; i < size*(size-1)/2; i++)
	{
		cycle_detection[i] = i;
	}
}


void make_graph()
{
	graph = (node * *)malloc(sizeof(node*) * size);
	for (int i = 0; i < size; i++)
	{
		graph[i] = 0;
	}
}

void make_edges()
{
	edges = (edge *)malloc(sizeof(edge) * size*(size-1)/2);
	for (int i = 0; i < size*(size-1)/2; i++)
	{
		edges[i].from = -1;
		edges[i].to = -1;
		edges[i].w = -1;
	}
}


void addedge(int v1, int v2, int w, int doreverse)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->v = v2;
	new_node->weight = w;
	new_node->next = 0;

	node* temp = graph[v1];

	if (temp == 0)
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
	if (doreverse == 1)
	{
		addedge(v2, v1, w, 0);
	}
	return;
}



void swap(int a, int b)
{
	edge temp = edges[a];
	edges[a] = edges[b];
	edges[b] = temp;
	return;
}

void samegroup(int a, int b)
{
	int g1, g2;
	g1 = cycle_detection[a];
	g2 = cycle_detection[b];
	int bigger, smaller;
	if (a > b)
	{
		bigger = g1;
		smaller = g2;
	}
	else
	{
		bigger = g2;
		smaller = g1;
	}
	for (int i = 0; i < size * (size - 1) / 2; i++)
	{
		if (cycle_detection[i] == bigger)
		{
			cycle_detection[i] = smaller;
		}
	}
}

void sortedge()
{
	int i;
	int edges_index = 0;
	for (i = 0; i < size; i++)
	{
		node* temp = graph[i];
		while (temp != 0)
		{
			edges[edges_index].from = i;
			edges[edges_index].to = temp->v;
			edges[edges_index].w = temp->weight;
			edges_index++;
			temp = temp->next;
		}
	}
	int x, y;
	for (y = 0; y < size * (size - 1) / 2; y++)
	{
		for (x = 0; x < size * (size - 1) / 2 - 1 - y; x++)
		{
			if (edges[x].w == -1)
			{
				continue;
			}
			else
			{
				if (edges[x].w > edges[x + 1].w)
				{
					swap(x, x + 1);
				}
			}
		}
	}

}

void domst()
{
	int i;
	int mst_edges = 0;
	for (i = 0; i < size * (size - 1) / 2; i++)
	{
		if (cycle_detection[edges[i].from] != cycle_detection[edges[i].to])
		{
			if (edges[i].from == -1)
			{
				continue;
			}
			printf("MST edge %d --- %d(%d) \n", edges[i].from, edges[i].to, edges[i].w);
			mst_edges++;
			if (mst_edges == size - 1)
			{
				return;
			}
			samegroup(edges[i].from, edges[i].to);
		}
	}
}

int main()
{
	int num;
	scanf_s("%d", &num);
	size = num;
	make_graph();
	make_edges();
	make_cycle_detection();
	addedge(0, 1, 1, 0);
	addedge(0, 2, 3, 0);
	addedge(0, 4, 5, 0);
	addedge(1, 2, 2, 0);
	addedge(1, 4, 4, 0);
	addedge(2, 4, 6, 0);
	addedge(2, 3, 7, 0);
	addedge(3, 4, 8, 0);

	sortedge();
	domst();

}
