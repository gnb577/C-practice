#include<stdio.h>
#include<string.h>
#define VERTEX_NUM 5


typedef struct node
{
	int num;
	struct vertex* next;
	int thisisvertex;
}node;

node* graph[VERTEX_NUM];

void addEdge(int v1, int v2, int doReverse)
{
	//이미 v2가 있는지 확인
	//없으면 v2를 만들어서 추가
	node* new_node = (node*)malloc(sizeof(node));
	node* temp = graph[v1];
	new_node->num = v2;
	new_node->next = 0;


	if (temp == 0)
	{
		graph[v1] = new_node;
		graph[v1]->thisisvertex = 1;
	}
	else
	{
		if(graph[v1]->thisisvertex == 1)
		if (graph[v1]->thisisvertex == 1)
		{
			while (temp->next != 0)
			{

				temp = temp->next;
			}
			temp->next = new_node;

			if (doReverse == 1)
			{

				addEdge(v2, v1, 0);
			}
			else
			{
				return;
			}
		}
		else
		{

		}
	}
}
/*
temp = graph[v1-1].next;
	if (temp == 0)
{
	graph[v1 - 1].next = new_node;
}
else
{
	temp->next = new_node;
}
*/



void showAdjacentVertex(int v)
{
	node* temp = graph[v];
	while (temp != 0)
	{
		printf("%d is the adjacent vertex\n", temp->num);
		temp = temp->next;
	}
}

int main()
{
	int i;
	
	addEdge(0, 1, 1);// 1과 3 vertex사이에 edge 추가하기 1->3 3->1모두 추가해야됨 undirected가 아니더라도
	addEdge(0, 2, 1);
	addEdge(0, 4, 1);
	addEdge(1, 2, 1);
	addEdge(2, 3, 1);
	addEdge(2, 4, 1);
	addEdge(3, 4, 1);
	showAdjacentVertex(1);
	return 0;
}