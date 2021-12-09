/*
DIJKSTRA 알고리즘

struct node
struct dijkstra
found
distance
prev

필요변수

graph[]
dtable[]

필요함수
addedge
dijkstra함수
※주의 최초 distance를 0으로 주는 것은 좋으나 found는 하지말아야한다
※ 그렇지않으면 최초 distance가 0인 것이 findnext에서 걸러져 나머지99999끼리 비교가됨
findnext -> 현 dtable 중 found되지 않았으면서 가장 최단거리찾기
update-> 가장 최단거리를 가진 vertex를 인자로 보내 그 친구와 연결된 친구들중 found되지 않았으면 그 친구까지의 거리 > 나 + 나와 그친구의 weight이면 최신화 시킴 
또한 prev를 나로 지정
별도의 함수없이 전부끝나면 종료

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
	graph = (node * *)malloc(sizeof(node*) * scan_num);
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

void showdtable()
{
	for(int i = 0; i < sz; i++)
	{
		if (dtable[i].distance == 99999)
		{
			continue;
		}
		printf("%d: %d %d %d\n", i, dtable[i].found, dtable[i].distance, dtable[i].prev);
	}
}

void updatedtable(int v)
{
	node* temp = graph[v];
	while (temp != 0)
	{
		if (dtable[temp->vertex].found == 0 && dtable[temp->vertex].distance > dtable[v].distance + temp->weight)
		{
			dtable[temp->vertex].distance = dtable[v].distance + temp->weight;
			dtable[temp->vertex].prev = v;
		}
		temp = temp->next;
	}
}

int findnext2()
{
	int i;
	int smallest_distance=99999;
	int smallest_vertex=-1;
	for (int i = 0; i < sz; i++)
	{
		if (dtable[i].distance < smallest_distance && dtable[i].found==0)
		{
			smallest_vertex = i;
			smallest_distance = dtable[i].distance;
		}
	}
	return smallest_vertex; 
}
void dijkstra2(int v)
{
	dtable[v].distance = 0;
	//dtable[v].found = 1;
	int next_vertex = -1;
	while ((next_vertex = findnext2()) != -1)
	{
		dtable[next_vertex].found = 1;
		updatedtable(next_vertex);
	}
	showdtable();

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