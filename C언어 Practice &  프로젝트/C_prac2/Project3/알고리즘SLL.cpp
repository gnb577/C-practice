#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct node
{
	int num;
	struct node* next;

};

node *graph[4];


void addEdge(int v1, int v2)
{
	node* new_node = (node*)malloc(sizeof(node));
	node* temp = graph[v1];

	new_node->num = v2;
	new_node->next = 0;
	if (temp == 0)
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

void showAdjacentVertex(int v)
{
	node* temp = graph[v];
	while (temp != 0)
	{
		printf("%d is the adjacent vertext\n", temp->num);
		temp = temp->next;
	}
}
int main()
{
	addEdge(0, 1);
	addEdge(0, 2);
	addEdge(2, 0);
	addEdge(1, 0);

	showAdjacentVertex(0);
}