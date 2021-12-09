#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define sz 100
typedef struct node
{
	int vertex;
	int weight;
	struct node* next;
}node;

typedef struct edge
{
	int from;
	int to;
	int w;
}edge;

edge edges[sz];
node* head = 0;
int visited[sz];
node** graph;
int cycle_detection[sz];

void group(int a, int b)
{
	if (cycle_detection[a] > cycle_detection[b])
	{
		for (int j = 0; j < sz; j++)
		{
			if (cycle_detection[j] == cycle_detection[a])
			{
				cycle_detection[j] = cycle_detection[b];
			}
		}
	}
	else if (cycle_detection[a] < cycle_detection[b])
	{
		for (int j = 0; j < sz; j++)
		{
			if (cycle_detection[j] == cycle_detection[b])
			{
				cycle_detection[j] = cycle_detection[a];
			}
		}
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
	
	int idx=0;
	for (int i = 0; i < 5; i++)
	{
		if (idx == 12)
		{
			break;
		}
		node* temp = graph[i];
		while (temp != 0)
		{
			edges[idx].from = i;
			edges[idx].to = temp->vertex;
			edges[idx].w = temp->weight;
			idx++;
			temp = temp->next;
		}
	}
	for (int i = 0; i < sz-1; i++)
	{
		for (int j = 0; j < sz-i; j++)
		{
			if (edges[j].w > edges[j + 1].w)
			{
				swap(j, j + 1);
			}
			
		}
	}

}
void make_graph(int scan_num)
{
	graph = (node**)malloc(sizeof(node*) * scan_num);
	for (int i = 0; i < scan_num; i++)
	{
		graph[i] = 0;
	}
}

void addedge(int v1, int v2,int w)
{
	node* new_node = (node*)malloc(sizeof(node));
	node* temp = graph[v1];

	new_node->vertex = v2;
	new_node->weight = w;
	new_node->next = 0;

	if (graph[v1] == 0)//head==0
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
		return;
	}
}

void domst()
{
	int i = 0;
	int idx = 0;
	while (idx != 4)
	{
		
		if (cycle_detection[edges[i].from] != cycle_detection[edges[i].to])
		{
			printf("%d ---- %d(%d)", edges[i].from, edges[i].to, edges[i].w);
				idx++;
		}
		group(edges[i].from, edges[i].to);
			i++;
	}
}

int main()
{
	int num;
	scanf("%d", &num);
	make_graph(num);
	addedge(0, 1,1);
	addedge(1, 0,3);
	addedge(0, 2,5);
	addedge(0, 3,7);
	addedge(3, 0,2);
	addedge(2, 0,4);
	addedge(2, 1,6);
	addedge(2, 3,8);
	addedge(1, 2,3);
	addedge(3, 2,6);
	sortedge();
	domst();
}