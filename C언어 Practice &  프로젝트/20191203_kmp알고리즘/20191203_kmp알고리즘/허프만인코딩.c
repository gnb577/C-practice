#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
	char c;
	int fre;
	struct node* next;
	struct node* right;
	struct node* left;
	char family;
}node;

node* head = 0;
int char_cnt = 0;
int buf_cnt[256];
char code[256][100];
char make_code[100];
int codeidx = -1;

int idx = 0;
char alpha;
int len = 0;
char arr[100];

node* createnode(char _c, int _f)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->c = _c;
	new_node->fre = _f;
	new_node->family = _c;
	new_node->next = new_node->left = new_node->right = 0;
	return new_node;
}

void addsll(node* new_node)
{
	if (head == 0)
	{
		head = new_node;
		return;
	}
	else
	{
		node* temp = head;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
}