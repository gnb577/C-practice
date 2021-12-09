#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define sz 100
#define ascii 256


char codebuf[sz];
int codebuf_cnt = 0;
int alpha_cnt[ascii] = { 0, };
int codeidx = -1;

typedef struct node
{
	char c;
	int f;
	struct node* next;
	struct node* left;
	struct node* right;
}node;

node* head = 0;
node* createnode(char _c, char _f)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->c = _c;
	new_node->f = _f;
	new_node->next = 0;
	new_node->left = 0;
	new_node->right = 0;
	return new_node;
}

void addsll(node* _node)
{
	node* new_node = _node;
	if (head == 0)
	{
		head = new_node;
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

node* findleast()
{
	node* temp = head;
	node* least_temp = head;
	node* least_cnt = temp->f;
	while (temp != 0)
	{
		if (temp->f < least_cnt)
		{
			least_temp = temp;
			least_cnt = temp->f;
		}
		temp = temp->next;
	}
	if (head == least_temp)
	{
		head = head->next;
	}
	else
	{
		temp = head;
		while (temp->next != least_temp)
		{
			temp = temp->next;
		}
		node* temp2 = temp->next;
		temp->next = temp2->next;
	}
	return least_temp;
}
/*
void travelhuff(node* _node, char _code)
{
	codeidx++;
	codebuf[codeidx] = _code;
	codebuf[codeidx + 1] = 0;
	if (_node->left == 0 && _node->right == 0)
	{
		return;
	}
	else
	{
		travelhuff(_node->left, '0');
		travelhuff(_node->right, '1');
	}
	codebuf[codeidx] = 0;
	codeidx--;
}
*/
void travelhuff(node* _node, char _code, char _ans)
{
	codeidx++;
	codebuf[codeidx] = _code;
	codebuf[codeidx + 1] = 0;
	int idx = codeidx;
	if (_node->left == 0 && _node->right == 0)
	{
		if (_node->c == _ans)
		{
			printf("%d\n", codeidx + 1);
		}
	}
	else
	{
		travelhuff(_node->left, '0', _ans);
		travelhuff(_node->right, '1', _ans);
	}
	codebuf[codeidx] = 0;
	codeidx--;
}
int main()
{
	char t;
	int u;
	while (1)
	{
		scanf("%c%d\n", &t, &u);
		if (u == -1)
		{
			break;
		}
		addsll(createnode(t, u));
	}
	char ans=1;
	while (ans != NULL)
	{
		scanf("%c", &ans);
	}

	while (1)
	{
		if (head->next == 0)
		{
			break;
		}
		node* a = findleast();
		node* b = findleast();
		node* c = createnode(' ', a->f + b->f);
		//printf("%d\n", a->f);
	//	printf("%d\n", b->f);
		//printf("%d\n", c->f);
		c->left = a;
		c->right = b;
		addsll(c);
	}
	travelhuff(head->left, '0', ans);
	travelhuff(head->right, '1', ans);
}