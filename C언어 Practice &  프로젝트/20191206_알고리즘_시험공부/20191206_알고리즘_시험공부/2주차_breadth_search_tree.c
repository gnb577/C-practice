/*
B.F.S

������ �湮�ϴ� Ž����
�ڽ����� �޸� ��� �ڽ��� QUEUE���ְ��� �ڽ��� POP
�� ���� ģ���� �� �޸� ��� �ڽ��� QUEUE���ְ� �ڽ��� POP
������ ���������� ������

struct node
int vertex
*next

����
queue[]
head
tail
visited[]
next_vertex

�Լ�

1. addedge�Լ�
2. queue (enque, deque)
3 .show


�帧
addedge��

1. ó�� bfs�μ��� ����
2. �� �μ��� visited�ϰ� enque��
3. ���� while������ queue��  �������� �ϴ� ��
4. next_vertex�� �̿��ؼ� �ش� ��忡�� �̹湮 ��带 ã�Ƴ�
5. ã���� visited�ؼ� enque
6. ��ã���� ���̻� �����̾���??->deque

*���� tail�� �������� ��
*head�� deque�Ǹ� ������� ��
���� stack�� �޸� enque�� 
stackó�� top++�� �ƴ�
���� ����ְ�
(tail+1)%sz��

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
		printf("������\n");
		return;
	}
	queue[tail] = v;
	tail = (tail + 1) % sz;
}

int deque()
{
	if(tail == _head)
	{
		printf("�����\n");
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
	//v�� ����� vertex�� ���� �湮�������� �ҷ�����
	//������ -1�� return�� ���̻� ����� ģ���߿��� �湮���Ѱ��� ����
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
	return -1; // ��ĥ�� �ִ� �κ� ->return -1���־����
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
	printf("�� �׷����� %d ->", v);
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