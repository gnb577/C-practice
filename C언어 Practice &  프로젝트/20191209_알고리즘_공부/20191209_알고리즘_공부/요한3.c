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
}node;

node* head = 0;
int idx=0;
char alpha;
int len = 0;
char text[100] = "a200b11c201$00001110101#";

void travel(node* temp, char _code)
{
	if (_code == '#')
	{
		return;
	}
	if (temp->left == 0 && temp->right == 0)
	{
		printf("%c", temp->c);
		return;
	}
	if (_code == '0')
	{
		idx++;
		travel(temp->left, text[idx]);
	}
	if (_code == '1')
	{
		idx++;
		travel(temp->right,text[idx]);
	}
}
int main()
{
	head = (node*)malloc(sizeof(node));
	head->left = head->right = 0;
	node* temp = head;
	int num = 3;
	while (1)
	{
		alpha = text[idx];
		if (text[idx] == '$')
		{
			break;
		}
		idx++;
		len = text[idx]-48;
		idx++;
		for (int i = 0; i < len; i++)
		{
			if (text[idx] == '0')
			{
				if (temp->left == 0)
				{
					temp->left = (node*)malloc(sizeof(node));
					temp->left->left = 0;
					temp->left->right = 0;
				}
				temp = temp->left;
			}
			else if (text[idx] == '1')
			{
				if (temp->right == 0)
				{
					temp->right = (node*)malloc(sizeof(node));
					temp->right->left = 0;
					temp->right->right = 0;
				}
				temp = temp->right;
			}
			idx++;
		}
		temp->c = alpha;
		temp = head;
	}
	idx++;
	node* head2 = head;
	while (text[idx] != '#')
	{
		travel(head2, text[idx]);
		head2 = head;
	}

}
