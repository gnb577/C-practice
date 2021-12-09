#include<stdio.h>

#define VERTEX_NUM 5


typedef struct node
{
	int num;
	struct vertex* next;
}node;

node *graph[VERTEX_NUM];

void addEdge(int v1, int v2,int doReverse )
{
	//�̹� v2�� �ִ��� Ȯ��
	//������ v2�� ���� �߰�
	node* new_node = (node*)malloc(sizeof(node));
	node* temp = graph[v1];
	new_node->num = v2;
	new_node->next = 0;


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
		
		if (doReverse == 1)
		{
			addEdge(v2, v1, 0);
		}
		return;
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
}

int main()
{
	int i;
	for (i = 0; i < VERTEX_NUM; i++)
	{
		graph[i].num = i + 1;
		graph[i].next = 0;
	}

	addEdge(0, 1,1);// 1�� 3 vertex���̿� edge �߰��ϱ� 1->3 3->1��� �߰��ؾߵ� undirected�� �ƴϴ���
	addEdge(0, 2, 1);
	addEdge(0, 4, 1);
	addEdge(1, 2, 1);
	addEdge(2, 3, 1);
	addEdge(2, 4, 1);
	addEdge(3, 4, 1);
	showAdjacentVertex(1);
	return 0;
}