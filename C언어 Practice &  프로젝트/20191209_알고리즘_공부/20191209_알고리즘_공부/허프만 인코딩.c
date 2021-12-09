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

void travel(node* temp,char _code)
{
	codeidx++;
	make_code[codeidx] = _code;
	make_code[codeidx + 1] = 0;
	if (temp->left == 0 && temp->right == 0)
	{
		strcpy(code[temp->c], make_code);
		printf("%c(%d)-----%s\n",temp->c,temp->fre, code[temp->c]);
		//return;
	}
	else
	{
		travel(temp->left, '0');
		travel(temp->right, '1');
	}
	make_code[codeidx] = 0;
	codeidx--;
}
node* findleast()
{
	int smallest=99999;
	node* small = 0;
	node* temp = head;
	while (temp != 0)
	{
		if (smallest > temp->fre)
		{
			smallest = temp->fre;
			small = temp;
		}
		temp = temp->next;
	}
	if (head == small)
	{
		head = head->next;
	}
	else
	{
		temp = head;
		while (temp->next != small)
		{
			temp = temp->next;
		}
		temp->next = small->next;
	}
	small->next = 0;
	return small;
}
int main()
{
	scanf("%s", arr);
	while (arr[idx]!=0)
	{
		if (buf_cnt[arr[idx]] == 0)
		{
			char_cnt++;
		}
		buf_cnt[arr[idx]]++;
		idx++;
	}
	for (int i = 0; i < 256; i++)
	{
		if (buf_cnt[i] > 0)
		{
			addsll(createnode(i, buf_cnt[i]));
		}
	}
	while (1)
	{
		if (head->next == 0)
		{
			break;
		}
		node* a = findleast();
		node* b = findleast();
		node* c = createnode(' ', a->fre + b->fre);
		if (a->c < b->c)
		{
			c->family = a->c;
		}
		else
		{
			c->family = b->c;
		}
		if (a->family > b->family)
		{
			c->left = b;
			c->right = a;
		}
		else
		{
			c->left = a;
			c->right = b;
		}
		
		addsll(c);
	}
	
	travel(head->left, '0');
	travel(head->right, '1');

	printf("%d", char_cnt);
	node* temp = head;
	for(int i=0;i<256;i++)
	{
		if (buf_cnt[i] > 0)
		{
			printf("%c", i);
			printf("%d", strlen(code[i]));
			printf("%s", code[i]);
		}
	}
	printf("$");
	for (int i = 0; i < idx; i++)
	{
		printf("%s", code[arr[i]]);
	}
	return 0;
}
