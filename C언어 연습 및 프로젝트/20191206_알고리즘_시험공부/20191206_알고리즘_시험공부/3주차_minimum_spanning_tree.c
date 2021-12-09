/*
M.S.T
Kruskal �˰���

edge�� �������
weight�� ������������ 
vertex-1�� �� �ɶ�����
cycle�� ���ϸ鼭


struct node
struct edge

-from
-to
-w

�ʿ亯��
edges[]
graph[]
cycle_detection[i] = i

�ʿ��Լ�
addedge
sortedge
-make_edge ->from to w�� Ȱ���Ͽ� edge����
-sort_edge -> w����� ���� ->bubblesort

make_group = ������ ��θ��� ���� ���� ���ĺ� or ���ڷ� groupȭ(����ȭ)
domst
������ �ƴҽ�
mst�� �̾��ְ�
����ȭ ��Ŵ

�����̸� pass
edge���� vertex���� -1�̸� ����


*/

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

typedef struct edge
{
	int from;
	int to;
	int w;
}edge;


int num;
int vertex_num=0;
int edge_num = 0;
int cycle_detection[sz];
int visited[sz];
int queue[sz];
int _head = 0;
int tail = 0;

edge edges[sz]; // edge�� �����ϰ� ����Ϸ���
node* head = 0;
node** graph;


void swap(int a, int b)
{
	edge temp;
	temp = edges[a];
	edges[a] = edges[b];
	edges[b] = temp;
}

void make_graph(int scan_num)
{
	graph = (node * *)malloc(sizeof(node*) * scan_num);
	for (int i = 0; i < scan_num; i++)
	{
		graph[i] = 0;
	}
}
void make_cycle_detection()
{
	for (int i = 0; i < sz; i++)
	{
		cycle_detection[i] = i;
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

void sortedge()
{
	int i;
	int idx = 0;
	for (int i = 0; i < edge_num; i++)
	{
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

	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz-i; j++)
		{
			
			if (edges[j].w > edges[j + 1].w)
			{
				swap(j, j + 1);
			}
		}
	}
	for (int i = 0; i < sz; i++)
	{
		if (edges[i].w == 0)
		{
			continue;
		}
		printf("%d ", edges[i].w);
	}
}

void make_group(int a, int b)
{
	if (cycle_detection[a] > cycle_detection[b]) //b�� ����
	{
		for (int i = 0; i < sz; i++)
		{
			if (cycle_detection[i] == cycle_detection[a])
			{
				cycle_detection[i] = cycle_detection[b];
			}
		}
	}
	else if (a < b) //a�� ����
	{
		for (int i = 0; i < sz; i++)
		{
			if (cycle_detection[i] == cycle_detection[b])
			{
				cycle_detection[i] = cycle_detection[a];
			}
		}
	}
		
}

void domst()
{
	int i;
	int idx=0;
	for (i = 0; i < sz; i++)
	{
		if (cycle_detection[edges[i].from] != cycle_detection[edges[i].to])
		{
			printf("mst edge %d --------- %d (%d)\n", edges[i].from, edges[i].to, edges[i].w);
			idx++;
			if (idx == 4)
			{
				return;
			}
			make_group(edges[i].from, edges[i].to);
		}
	}
}

void show(int v)
{
	node* temp = graph[v];
	printf("�� �׷����� %d ->", v);
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
	make_cycle_detection();
	addedge(0, 1, 1);
	addedge(0, 2, 3);
	addedge(0, 4, 5);
	addedge(1, 2, 2);
	addedge(1, 4, 4);
	addedge(2 ,4, 6);
	addedge(2, 3, 7);
	addedge(3, 4, 8);
	sortedge();
	printf("\n");
	domst();
	/*
	addedge(0, 1,);
	addedge(1, 0);
	addedge(0, 2);
	addedge(0, 3);
	addedge(3, 0);
	addedge(2, 0);
	addedge(2, 1);
	addedge(2, 3);
	addedge(1, 2);
	addedge(3, 2);
	*/
	//show(0);
	//show(1);
	//show(2);
	//show(3);
	


}