#include<stdio.h>
#include<stdlib.h>

int size;

typedef struct node
{
	int v;
	int weight;
	struct node* next;
}node;

typedef struct table
{
	int found;
	int prev;
	int dist;
}table;

node** graph;
table* dtable;

void make_graph()
{
	graph = (node * *)malloc(sizeof(node*) * size);
	for (int i = 0; i < size; i++)
	{
		graph[i] = 0;
	}
}

void make_dtable()
{
	dtable = (table*)malloc(sizeof(table) * size);
	for (int i = 0; i < size; i++)
	{
		dtable[i].found = 0;
		dtable[i].dist = 99999;
		dtable[i].prev = -1;
	}
}


void addedge(int v1, int v2, int _w, int doreverse)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->v = v2;
	new_node->weight = _w;
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
	if (doreverse == 1)
	{
		addedge(v2, v1, _w, 0);
	}
	return;
}

void showdtable()
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d: %d %d %d \n", i, dtable[i].found, dtable[i].dist, dtable[i].prev);
	}
}

void updatedtable(int v)
{
	node* temp = graph[v];
while(temp!=0)
	{
		if(dtable[temp->v])
	}
}

int findnext()
{
	int smallest_vertex = -1;
	int smallest_dist = 99999;
	for (int i = 0; i < size; i++)
	{
		if (dtable[i].found == 0 && dtable[i].dist < smallest_dist)
		{

		}
	}
}

void dodijkstra(int v)
{
	int next = -1;
	dtable[v].dist = 0;

	while ((next = findnext()) != 1)
	{
		if (next == -1)
		{
			showdtable();
			return;
		}
		else
		{
			dtable[next].found = 1;
			updatedtable(next);
		}
	}
}

void dodijkstra(int v)
{
}
int main()
{
	int n;
	scanf_s("%d", &n);
	size = n;
	make_graph();
	make_dtable();
	addedge(0, 1, 1, 1);
	addedge(0, 2, 3, 1);
	addedge(0, 4, 5, 1);
	addedge(1, 2, 2, 1);
	addedge(1, 4, 4, 1);
	addedge(2, 4, 6, 1);
	addedge(2, 3, 7, 1);
	addedge(3, 4, 8, 1);
	dodijkstra(0);
	return 0;
}