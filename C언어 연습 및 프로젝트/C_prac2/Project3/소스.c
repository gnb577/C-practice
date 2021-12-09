#include<stdio.h>

#define VERTEX_NUM 5


typedef struct vertex
{
	int num;
	struct vertex *next;
}vertex;

vertex graph[VERTEX_NUM];

void _putEdge(int v1, int v2)
{
	//이미 v2가 있는지 확인
	
	vertex* temp = graph[v1 - 1].next;

	while (temp != 0)
	{
		if (temp->num == v2)
		{
			return;
		}
		if (temp->next == 0)
		{
			break;
		}
		temp = temp->next;
	}

	//없으면 v2를 만들어서 추가
	vertex *new_node = (vertex *)malloc(sizeof(vertex));
	new_node->num = v2;
	new_node->next = 0;

	
	if (temp == 0)
	{
		graph[v1 - 1].next = new_node;
	}
	else
	{
		temp->next = new_node;
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

}

//v1과 v2사이에 edge가 있음
void addEdge(int v1, int v2)
{
	_putEdge(v1, v2);
	_putEdge(v2, v1);

	return;
}
int main()
{
	int i;
	for (i = 0; i < VERTEX_NUM; i++)
	{
		graph[i].num = i + 1;
		graph[i].next = 0;
	}

	addEdge(1, 3);// 1과 3 vertex사이에 edge 추가하기 1->3 3->1모두 추가해야됨 undirected가 아니더라도
	addEdge(1, 2);
	addEdge(1, 4);
	addEdge(3, 4);
	addEdge(3, 5);
	addEdge(2, 4);
	addEdge(4, 5);

	return 0;
}