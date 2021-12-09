/*
B.F.S

층별로 방문하는 탐색법
자신한테 달린 모든 자식을 QUEUE에넣고나면 자신을 POP
그 다음 친구가 또 달린 모든 자식을 QUEUE에넣고 자신을 POP
계층적 구조적으로 내려감

struct node
int vertex
*next

변수
queue[]
head
tail
visited[]
next_vertex

함수

1. addedge함수
2. queue (enque, deque)
3 .show


흐름
addedge후

1. 처음 bfs인수를 결정
2. 그 인수를 visited하고 enque함
3. 이후 while문에서 queue가  빌때까지 하는 데
4. next_vertex를 이용해서 해당 노드에서 미방문 노드를 찾아냄
5. 찾으면 visited해서 enque
6. 못찾으면 더이상 갈곳이없다??->deque

*주의 tail이 먼저가는 놈
*head가 deque되면 따라오는 놈
또한 stack과 달리 enque시 
stack처럼 top++이 아닌
먼저 집어넣고
(tail+1)%sz임

*/
#include<stdio.h>
#include<stdlib.h>
#define sz 100
#define ascii 256

typedef struct node
{
	int vertex;
	struct node* next;
}node;

int visited[sz];
int queue[sz];
int _head = 0;
int tail = 0;
node* head = 0;
node** graph;

void enque(int v)
{
	if ((tail + 1) % sz == _head)
	{
		printf("꽉찻어\n");
		return;
	}
	queue[tail] = v;
	tail = (tail + 1) % sz;
}

int deque()
{
	if(tail == _head)
	{
		printf("비었어\n");
		return -1;
	}
	int ret = queue[_head];
	_head = (_head + 1) % sz;
	return ret;
}
void make_graph(int scan_num)
{
	graph = (node * *)malloc(sizeof(node*) * scan_num);
	for (int i = 0; i < scan_num; i++)
	{
		graph[i] = 0;
	}
}

void addedge(int v1, int v2)
{
	node* new_node = (node*)malloc(sizeof(node));
	node* temp = graph[v1];

	new_node->vertex = v2;
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
int findnext(int v)
{
	//v와 연결된 vertex중 아직 방문안했으면 불러오고
	//없으면 -1을 return해 더이상 연결된 친구중에는 방문안한곳이 없다
	node* temp = graph[v];
	while (temp != 0)
	{
		if (visited[temp->vertex] == 0)
		{
			//visited[temp->vertex] = 1;
			return temp->vertex;
		}
		temp = temp->next;
	}
	return -1; // 놓칠수 있는 부분 ->return -1해주어야함
}
void dobfs(int v)
{
	printf("visited %d \n", v);
	visited[v] = 1;
	enque(v);
	while (_head != tail)
	{
		int next_vertex = -1;
		next_vertex = findnext(queue[_head]);
		if (next_vertex == -1)
		{
			deque();
		}
		else
		{
			printf("visited %d\n", next_vertex);
			visited[next_vertex] = 1;
			enque(next_vertex);
		}
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
	int num;
	scanf("%d", &num);
	make_graph(num);
	addedge(0, 1);
	addedge(1, 0);
	addedge(0, 2);
	addedge(0, 3);
	addedge(3, 0);
	addedge(2, 0);
	addedge(2, 1);
	addedge(2, 3);
	addedge(1, 2);
	addedge(3, 2);
	//show(0);
	//show(1);
	//show(2);
//	show(3);
	//dobfs(1);
	dobfs(2);


}