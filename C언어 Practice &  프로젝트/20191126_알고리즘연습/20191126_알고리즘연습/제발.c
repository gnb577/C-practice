#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SZ 100
#define ASCII 256

typedef struct node {
	int n;
	char c;
	struct node* left;
	struct node* right;
	struct node* next;
}node;

node* head = 0;
int buf[SZ];
int buf_cnt[ASCII];
int sum = 0;
int codeidx = -1;
char code[SZ] = { 0, };

node* createnode(int _n, char _c)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->n = _n;
	new_node->c = _c;
	new_node->next = new_node->right = new_node->left = 0;

	return new_node;

}

void addsll(node* _node)
{
	node* new_node = _node;
	node* temp = head;
	if (head == 0)
	{
		head = new_node;
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

node* findleast()
{
	node* find = 0;
	int least = 99999;
	node* temp = head;
	while (temp != 0)
	{
		if (temp->n < least)
		{
			least = temp->n;
			find = temp;
		}
		temp = temp->next;
	}

	if (head == find)
	{
		head = head->next;
	}
	else
	{
		node* temp2 = head;
		while (temp2->next != find)
		{
			temp2 = temp2->next;
		}
		//node* temp2 = temp->next;
		temp2->next = find->next;
	}
	find->next = 0;
	return find;
}

void travel(node* _node, char _code)
{
	codeidx++;
	code[codeidx] = _code;
	code[codeidx + 1] = 0;
	if (_node->left == 0 && _node->right == 0)
	{

		sum = sum + strlen(code);

	}
	else
	{
		travel(_node->left, '0');
		travel(_node->right, '1');
	}
	code[codeidx] = 0;
	codeidx--;
	return;
}

int main()
{
	int num;
	char letter;
	while (1)
	{
		scanf("%c %d\n", &letter, &num);
		if (num == -1)
		{
			break;
		}
		buf_cnt[letter] = num;

	}

	for (int i = 0; i < ASCII; i++)
	{
		if (buf_cnt[i] >= 0)
		{
			addsll(createnode(i, buf_cnt[i]));
		}
	}

	while (head->next != 0)
	{
		node* a = findleast();
		node* b = findleast();
		node* c = createnode(' ', a->n + b->n);
		c->left = a;
		c->right = b;
		addsll(c);
	}
	travel(head->left, '0');
	travel(head->right, '1');
	printf("%d", sum);
}

