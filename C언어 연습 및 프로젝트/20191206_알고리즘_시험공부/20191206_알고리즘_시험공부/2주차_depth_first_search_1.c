/*
D.F.S

계속 밑으로 내려가다가 길이 막히면 이전 길로 돌아가서 다른 갈림길로 내려감

struct node 
int vertex
*next

변수
stack[]
top
visited[]
next_vertex


함수

1. addedge함수
2. stack (push, pop)
3 .show


흐름 
addedge후

1. 처음 dfs인수를 결정
2. 그 인수를 visited하고 push함
3. 이후 while문에서 stack이 빌때까지 하는 데
4. next_vertex를 이용해서 해당 노드에서 미방문 노드를 찾아냄
5. 찾으면 visited해서 push
6. 못찾으면 더이상 갈곳이없다??->pop

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

int stack[sz];
int top = -1;
int visited[sz];
node* head = 0;
node** graph;

void push(int v)
{
	if (top == sz - 1)
	{
		printf("꽉 찼음\n");
		return;
	}
	top++;
	stack[top] = v;
}

int pop()
{
	if (top == -1)
	{
		printf("비었음\n");
		return -1;
	}
	int ret = stack[top];
	top--;
	return ret;
}
void make_graph(int scan_num)
{
	graph = (node **)malloc(sizeof(node*)*scan_num);
	for (int i = 0; i < scan_num; i++)
	{
		graph[i] = 0;
	}
}
/*
node* make_new_node(int v1, int v2)
{
	node* new_node = (node*)malloc(sizeof(node));

}
*/
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
void dodfs(int v)
{
	printf("visited %d \n", v);
	visited[v] = 1;
	push(v);
	while (top != -1)
	{
		int next_vertex = -1;
		next_vertex = findnext(stack[top]);
		if (next_vertex == -1)
		{
			pop();
		}
		else
		{
			printf("visited %d\n", next_vertex);
			visited[next_vertex] = 1;
			push(next_vertex);
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
	show(0);
	show(1);
	show(2);
	show(3);
	dodfs(1);
	
}