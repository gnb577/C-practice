#include<stdio.h>
#include<stdlib.h>
#define sz 100
#define ascii 256

typedef struct node
{
	int vertex;
	int weight;
	struct node* next;
}node;


typedef struct dijkstra
{
	int found; // 최단거리가 알려졌는가 0,1로 no,yes
	int distance;
	int prev;
}dijkstra;


dijkstra* dtable;

int num;
int vertex_num = 0;
int edge_num = 0;

node* head = 0;
node** graph;

void make_graph(int scan_num)
{
	graph = (node**)malloc(sizeof(node*) * scan_num);
	for (int i = 0; i < scan_num; i++)
	{
		graph[i] = 0;
	}
}

void make_dtable()
{
	dtable = (dijkstra*)malloc(sizeof(dijkstra) * sz);
	//dtable = 0;
	for (int i = 0; i < sz; i++)
	{
		dtable[i].found = 0;
		dtable[i].distance = 99999;
		dtable[i].prev = -1;
	}
}

void addedge(int v1, int v2, int w)
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


void dijkstra(int v)
{
	dtable[v].distance = 0;
	int next_vertex = -1;
	while ((next_vertex = findnext()) != -1)
	{
		dtable[next_vertex].found = 1;
		updatedtable(next_vertex);
	}
}

void show(int v)
{
	node* temp = graph[v];
	printf("현 그래프는 %d ->", v);
	while (temp != 0)
	{
		printf("%d ->", temp->vertex);
		temp = temp->next;
	}
}

int main()
{

	scanf("%d", &num);
	make_graph(num);
	make_dtable();
	//make_cycle_detection();
	addedge(0, 1, 1);
	addedge(0, 2, 3);
	addedge(0, 4, 5);
	addedge(1, 2, 2);
	addedge(1, 4, 4);
	addedge(2, 4, 6);
	addedge(2, 3, 7);
	addedge(3, 4, 8);
	dijkstra2(0);

}