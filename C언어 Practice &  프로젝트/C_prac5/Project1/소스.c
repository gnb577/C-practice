#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int v;
	struct node* next;
}node;

node* graph[4];

void addEdge(int v1, int v2)
{
	node* new_node = (node*)malloc(sizeof(node));
	node* temp = graph[v1];

	new_node->v = v2; // 앞에 꺼가 뒤에 거를 가리키니까
	new_node->next = 0;

	if (temp == 0) //v1에 아무것도 안 붙어 있을 때
	{
		graph[v1] = new_node;
		return;
	}
	else //v1에 다른 vertex가 붙어 뒤로 이어야 되기때문에 없을 때 까지
	{
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_node;
		return;
	}
}

void showAdjacentVertex(int v)
{
	node* temp = graph[v];
	while (temp != 0)
	{
		printf("%d is the %d's Adjacent Vertex\n", temp->v,v);
		temp = temp->next;
	}
	return;
}

void main()
{
	addEdge(0, 1); // 0->1, 1->0
	addEdge(1, 0); 
	addEdge(0, 2); // 0->2, 2->0
	addEdge(2, 0); 

	showAdjacentVertex(0);
	showAdjacentVertex(1);
}