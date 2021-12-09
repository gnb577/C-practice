#include <stdio.h>
#include <stdlib.h>

#define VERTEX_NUM 5

struct vertex
{
	int vertex_num;
	struct vertex* next;
};

struct vertex graph[VERTEX_NUM];

/*
   v1과 v2사이에 edge를 놓는다.
   역방향 고려 불필요
*/
void _putEdge(int v1, int v2)
{
	// 1. 이미 v2가 붙어 있는지 확인.
	struct vertex* cur = graph[v1 - 1].next;
	while (cur != 0)
	{
		if (cur->vertex_num == v2)
		{
			return;
		}
		cur = cur->next;
	}

	// 2. 없으면, v2를 만들어서 추가
	struct vertex* new_one = (struct vertex*)malloc(sizeof(struct vertex));
	new_one->vertex_num = v2;
	new_one->next = 0;

	cur = graph[v1 - 1].next;
	if (cur == 0)
	{
		graph[v1 - 1].next = new_one;
	}
	else
	{
		while (cur->next != 0)
		{
			cur = cur->next;
		}
		cur->next = new_one;
	}

	return;

}

/*
  v1과 v2사이에 edge가 있음을 표시
*/
void addEdge(int v1, int v2)
{
	_putEdge(v1, v2);
	_putEdge(v2, v1);
}


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
	// vertex array에 vertex num을 채워넣는다.
	int i;
	for (i = 0; i < VERTEX_NUM; i++)
	{
		graph[i].vertex_num = i + 1;
		graph[i].next = 0;
	}

	// vertex 1과 vertex 3 사이에는 
	// edge가 있다.
	// 주의: 1->3 과 3->1도 추가
	addEdge(1, 3);
	addEdge(1, 2);
	addEdge(1, 4);
	addEdge(3, 4);
	addEdge(3, 5);
	addEdge(2, 4);
	addEdge(4, 5);
	showAdjacentVertex(3);

	return 0;
}