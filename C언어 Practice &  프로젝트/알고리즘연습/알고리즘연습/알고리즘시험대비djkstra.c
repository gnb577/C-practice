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
	int distance;
	int prev;
}table;

node** graph;
table* dtable;

void make_graph()
{
	graph = (node **)malloc(sizeof(node*) * size);
	for (int i = 0; i < size; i++)
	{
		graph[i] = 0;
	}
}

void make_dtable()
{
	dtable = (table *)malloc(sizeof(table) * size);
	for (int i = 0; i < size; i++)
	{
		dtable[i].found = 0;
		dtable[i].distance = 99999;
		dtable[i].prev = -1;
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

int finddijkstranextvertex()
{
	int i;
	int smallest_distance = 99999;
	int smallest_vertex = -1;
	for (i = 0; i < size; i++)
	{
		if (dtable[i].found == 0 && dtable[i].distance < smallest_distance)
		{
			smallest_distance = dtable[i].distance;
			smallest_vertex = i;
		}
	}
	return smallest_vertex;
}

void showdtable()
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d: %d %d %d \n", i, dtable[i].found, dtable[i].distance, dtable[i].prev);
	}
}


void updatedtable(int v)
{
	node* temp = graph[v];
	while (temp != 0)
	{
		if (dtable[temp->v].found == 0 && (dtable[temp->v].distance > dtable[v].distance + temp->weight))
		{
			dtable[temp->v].distance = dtable[v].distance + temp->weight;
			dtable[temp->v].prev = v;
		}
		temp = temp->next;
	}
	printf("--------------------------\n");
	showdtable();
}

void dodijkstra(int v)
{
	int next_vertex = -1;
	dtable[v]. distance = 0;
	while ((next_vertex = finddijkstranextvertex()) != -1)
	{
		dtable[next_vertex].found = 1;
		updatedtable(next_vertex);
	}
	showdtable();

}

int main()
{
	int num;
	scanf_s("%d", &num);
	size = num;
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


}