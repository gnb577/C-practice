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
	//�̹� v2�� �ִ��� Ȯ��
	
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

	//������ v2�� ���� �߰�
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

//v1�� v2���̿� edge�� ����
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

	addEdge(1, 3);// 1�� 3 vertex���̿� edge �߰��ϱ� 1->3 3->1��� �߰��ؾߵ� undirected�� �ƴϴ���
	addEdge(1, 2);
	addEdge(1, 4);
	addEdge(3, 4);
	addEdge(3, 5);
	addEdge(2, 4);
	addEdge(4, 5);

	return 0;
}