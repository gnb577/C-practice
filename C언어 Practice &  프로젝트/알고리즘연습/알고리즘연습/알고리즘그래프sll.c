#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


int size;

typedef struct node
{
	int v;
	struct node* next;
}node;

node** graph = NULL;

void make_graph()
{
	graph = (node **)malloc(sizeof(node*) * size);
	for (int i = 0; i < size; i++)
	{
		graph[i] = 0;
	}
}


void addedge(int v1, int v2, int doreverse)
{
	node* new_node = (node*)malloc(sizeof(node));
	node* temp = graph[v1];

	new_node->v = v2;
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
	}
	if (doreverse == 1)
	{
		addedge(v2, v1, 0);
	}
	return;
}

void showadjacent(int _v)
{
	node* temp = graph[_v];
	while (temp != 0)
	{
		printf("%d is adjacent with %d\n",temp->v, _v);
		temp = temp->next;
	}
	
	return;
		
}

int main()
{
	scanf_s("%d", &size);
	make_graph();
	addedge(0, 3,1);
	addedge(0, 2,1);
	addedge(0, 1,1);
	addedge(1, 2,1);
	showadjacent(0);

	return 0;
}