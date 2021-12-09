#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAX_NUM 5
typedef struct node
{
	int num;
	struct node* next;
}node;

node graph[MAX_NUM];

void addEdge(int v1, int v2)
{
	node* temp = graph[v1].next;
	while (temp != 0)
	{
		if (temp->num == v2)
		{
			return;
		}
		temp = temp->next;
	}
	node* new_node = (node *)malloc(sizeof(struct vertex));
	new_node->num = v2;
	new_node->next = 0;


	temp = graph[v1].next;
	if (cur == 0) { //2.1.처음추가일때
		graph[v1 - 1].next = new_one;
	}
	else { //2.2
		while (cur->next != 0) {
			cur = cur->next;
		}
		cur->next = new_one;
	}

	


	if(temp)
	return;
}

int main()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		graph[i].num = i;
		graph[i].next = 0;
	}
	addEdge(0, 1);

}
