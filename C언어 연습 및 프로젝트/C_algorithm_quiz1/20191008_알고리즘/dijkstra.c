#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define vertex_num 5
#define edge_num 8


typedef struct node
{
	int weight;
	int num;
	struct node* next;
}node;

typedef struct edge
{
	int from;
	int to;
	int w;
}edge;

typedef struct dijkstra
{
	int found; // K 최단거리 1=YES 0=NO
	int distance;
	int prev;
}dijkstra;

dijkstra dtable[vertex_num];
node* graph[vertex_num];
edge edges[edge_num];

int cycle_detection[vertex_num] = { 0,1,2,3,4 };

void samegroup(int v1, int v2)
{
	int g1 = cycle_detection[v1];
	int g2 = cycle_detection[v2];
	int smaller, bigger;
	if (g1 > g2)
	{
		bigger = g1;
		smaller = g2;
	}
	else
	{
		bigger = g2;
		smaller = g1;
	}
	{
		int i;
		for (i = 0; i < vertex_num; i++)
		{
			if (cycle_detection[i] == bigger)
			{
				cycle_detection[i] = smaller;
			}
		}
	}

}

void addedge(int v1, int v2, int w, int doreverse)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->num = v2;
	new_node->next = 0;
	new_node->weight = w;

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
		addedge(v2, v1, w, 0);
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
	int edges_index = 0;
	for (i = 0; i < vertex_num; i++)
	{
		node* temp = graph[i];
		while (temp != 0)
		{
			edges[edges_index].from = i;
			edges[edges_index].to = temp->num;
			edges[edges_index].w = temp->weight;
			edges_index++;
			temp = temp->next;
		}
	}
	{
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
}

void domst()
{
	int i;
	int mst_edges = 0;
	for (int i = 0; i < edge_num; i++)
	{
		if (cycle_detection[edges[i].from] != cycle_detection[edges[i].to])
		{
			printf("MST edge %d --- %d(%d) \n", edges[i].from, edges[i].to, edges[i].w);
			mst_edges++;
			if (mst_edges == vertex_num - 1)
			{
				return;
			}
			samegroup(edges[i].from, edges[i].to);
		}
	}
}

void initdtable()
{
	int i;
	for (i = 0; i < vertex_num; i++)
	{
		dtable[i].found = 0;
		dtable[i].distance = 99999;
		dtable[i].prev = -1;
	}
}
//최단거리가 알려지지 않은 vertex중에서
//distance가 가장 짧은 vertex를 반환
//return -1은 모든 vertex의 최단거리가 결정된 경우

int finddijkstranextvertex()
{
	int i;
	int smallest_distance= 99999;
	int smallest_vertex= -1;

	for (i = 0; i < vertex_num; i++)
	{
		if (dtable[i].found == 0 && dtable[i].distance < smallest_distance)
		{
			smallest_vertex = i;
			smallest_distance = dtable[i].distance;
		}
	}
	return smallest_vertex;
}

void showdtable()
{
	int i;
	for (i = 0; i < vertex_num; i++)
	{
		printf("%d: %d %d %d \n", i, dtable[i].found, dtable[i].distance, dtable[i].prev);
	}
}

void updatedtable(int v)
{
	node* temp = graph[v];
	while (temp != 0)
	{
		//최단거리가 알려지지 않았고 4
		//기존 알려진 거리보다, v를 통할 경우, 더 가까우면 dtable업데이트
		if (dtable[temp->num].found == 0 && (dtable[temp->num].distance > dtable[v].distance + temp->weight))
		{
			dtable[temp->num].distance = dtable[v].distance + temp->num;
			dtable[temp->num].prev = v;
		}
		temp = temp->next;
	}
}
void dodijkstra(int v)
{
	int next_vertex = -1;
	dtable[v].distance = 0;
	
	while ((next_vertex = finddijkstranextvertex()) != -1)
	{
		dtable[next_vertex].found = 1;//최단거리를 찾음
		updatedtable(next_vertex);
	}
	showdtable();
}

int main()
{
	addedge(0, 1, 1, 1);
	addedge(0, 2, 3, 1);
	addedge(0, 4, 5, 1);
	addedge(1, 2, 2, 1);
	addedge(1, 4, 4, 1);
	addedge(2, 4, 6, 1);
	addedge(2, 3, 7, 1);
	addedge(3, 4, 8, 1);

	//doDFS(0);
	//sortedge();
	//domst();

	initdtable();
	dodijkstra(0);
}

/*

void finddijkstra()
{

void dodijkstra(int v)
{
int next_vertex =-1;
dtable[v].distance=0;

while(next_vertex=finddijkstra()!=-1)
{
dtable[next_vertex].found=1;
update(nextvertex)
}
*/