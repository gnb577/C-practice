#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct vertex
{
	int fre;
	char c;
	struct vertex* next;
	struct vertex* left;
	struct vertex* right;
};

struct vertex* head = 0;

struct vertex* create(char _c, int _fre)
{
	struct vertex* new_one = (struct vertex*)malloc(sizeof(struct vertex));
	new_one->c = _c;
	new_one->fre = _fre;
	new_one->next = new_one->left = new_one->right = 0;

	return new_one;
}

void buildSLL(struct vertex* new_one)
{
	struct vertex* temp = head;
	if (head == 0)
	{
		head = new_one;
		return;
	}
	else
	{
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_one;
	}

}

struct vertex* findLeast()
{
	struct vertex* temp = head;
	int least = 10000;
	struct vertex* LeastOne = 0;
	while (temp != 0)
	{
		if ((temp->fre) < least)
		{
			least = temp->fre;
			LeastOne = temp;
		}
		temp = temp->next;
	}

	if (head == LeastOne)
	{
		head = head->next;
	}
	else
	{
		temp = head;
		while (temp->next != LeastOne)
		{
			temp = temp->next;
		}
		temp->next = LeastOne->next;
	}
	LeastOne->next = 0;
	return LeastOne;
}
char code_Buf[200];
int codeBuf_index = -1;
char* symCode[256];
char* code[256];
char* temp_;
void traverseH(struct vertex* temp, char _code)
{
	codeBuf_index++;
	code_Buf[codeBuf_index] = _code;
	code_Buf[codeBuf_index + 1] = NULL;

	if (temp->left == 0 && temp->right == 0)
	{
		code[temp->c] = (char*)malloc(sizeof(code_Buf) + 1);
		strcpy(code[temp->c], code_Buf);
	}
	else
	{
		traverseH(temp->left, '0');
		traverseH(temp->right, '1');
	}
	code_Buf[codeBuf_index] = 0;
	codeBuf_index--;

}

void main()
{
	int char_cnt[256] = { 0, };
	char buf[1000];
	int num = 0; int k = 0;
	char data;
	while (1)
	{
		scanf(" %c", &data);
		scanf("%d", &num);
		if (num == -1)
			break;
		char_cnt[data] = num;
	}

	for (int i = 0; i < 256; i++)
	{
		if (char_cnt[i] > 0)
		{
			buildSLL(create(i, char_cnt[i]));
		}
	}
	while (1)
	{
		if (head->next == 0)
		{
			break;
		}
		struct vertex* a = findLeast();
		struct vertex* b = findLeast();
		struct vertex* c = create(' ', a->fre + b->fre);
		c->left = a;
		c->right = b;
		buildSLL(c);
	}
	//scanf("%c", &who);
	traverseH(head->left, '0');
	traverseH(head->right, '1');

}