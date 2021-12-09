#include<stdio.h>
#include<stdlib.h>

#define sz 100

typedef struct node
{
	int v;
	struct node* next;
}node;

node* head=0;
node** graph;
int row_num = 0;
int col_num = 0;
int visited[sz];
int _head = 0;
int tail = 0;
int top = -1;
int stack[sz];
int queue[sz];
void enque(int _v)
{
	if ((tail + 1) % sz == head)
	{
		return;
	}
	queue[tail] = _v;
	tail = (tail + 1) % sz;
	return;
}

void deque()
{
	if (tail == _head)
	{
		return -1;
	}
	int ret = queue[_head];
	_head = (_head + 1) % sz;
	return ret;

}

void make_graph()
{
	graph = (node**)malloc(sizeof(node*) * row_num);
	for (int i = 0; i < row_num; i++)
	{
		//graph[i] = (node*)malloc(sizeof(node) * col_num);
		graph[i] = 0;
	}
}

int findnext(int v)
{
	node* temp = graph[v];
	while (temp != 0)
	{
		if (visited[temp->v] == 0)
		{
			return temp->v;
		}
		temp = temp->next;
	}
	return -1;
}
void addedge(int v1,int v2)
{
	node* new_node = (node*)malloc(sizeof(node));
	node* temp = graph[v1];
	new_node->v = v2;
	new_node->next = 0;
	if (graph[v1] == 0)
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
	}

}

void dobst(int v)
{
	printf("visited: %d \n", v);
	visited[v] = 1;
	enque(v);

	while ((head != tail))
	{
		int next_vertex = -1;
		next_vertex = findnext(queue[_head]);
		if (next_vertex == -1)
		{
			deque();
		}
		else
		{
			printf("visited: %d \n", next_vertex);
			visited[next_vertex]=1;
			enque(next_vertex);
		}
	}
}
int main()
{
	scanf("%d %d", &row_num,&col_num);
	make_graph();
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
	dobst(1);
	return 0;
}
