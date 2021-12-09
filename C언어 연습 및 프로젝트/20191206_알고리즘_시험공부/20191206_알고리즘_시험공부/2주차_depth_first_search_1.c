/*
D.F.S

��� ������ �������ٰ� ���� ������ ���� ��� ���ư��� �ٸ� ������� ������

struct node 
int vertex
*next

����
stack[]
top
visited[]
next_vertex


�Լ�

1. addedge�Լ�
2. stack (push, pop)
3 .show


�帧 
addedge��

1. ó�� dfs�μ��� ����
2. �� �μ��� visited�ϰ� push��
3. ���� while������ stack�� �������� �ϴ� ��
4. next_vertex�� �̿��ؼ� �ش� ��忡�� �̹湮 ��带 ã�Ƴ�
5. ã���� visited�ؼ� push
6. ��ã���� ���̻� �����̾���??->pop

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
		printf("�� á��\n");
		return;
	}
	top++;
	stack[top] = v;
}

int pop()
{
	if (top == -1)
	{
		printf("�����\n");
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
	show(0);
	show(1);
	show(2);
	show(3);
	dodfs(1);
	
}