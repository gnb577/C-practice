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

	new_node->v = v2; // �տ� ���� �ڿ� �Ÿ� ����Ű�ϱ�
	new_node->next = 0;

	if (temp == 0) //v1�� �ƹ��͵� �� �پ� ���� ��
	{
		graph[v1] = new_node;
		return;
	}
	else //v1�� �ٸ� vertex�� �پ� �ڷ� �̾�� �Ǳ⶧���� ���� �� ����
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