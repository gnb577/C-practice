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
struct node
{
	int fre;
	char c;
};
struct vertex* head = 0;

struct vertex* create(char _c, int _fre)
{
	struct vertex* new_one = (struct vertex*)malloc(sizeof(struct vertex));
	new_one->next = new_one->right = new_one->left = 0;
	new_one->c = _c;
	new_one->fre = _fre;

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
	struct vertex* Least = 0;
	struct vertex* temp = head;
	int cnt = 99999;

	while (temp != 0)
	{
		if ((temp->fre) < cnt)
		{
			cnt = temp->fre;
			Least = temp;
		}
		temp = temp->next;
	}
	if (Least == head)
	{
		head = head->next;
	}
	else
	{
		temp = head;
		while (temp->next != Least)
		{
			temp = temp->next;
		}
		temp->next = Least->next;
	}
	Least->next = 0;
	return Least;
}
char code_buf[1000];
int code_index = -1;
char* code[256];
void traverse(struct vertex* temp, char _code)
{
	code_index++;
	code_buf[code_index] = _code;
	code_buf[code_index + 1] = 0;

	if (temp->left == 0 && temp->right == 0)
	{
		code[temp->c] = (char*)malloc(strlen(code_buf) + 1);
		strcpy(code[temp->c], code_buf);
	}
	else
	{
		traverse(temp->left, '0');
		traverse(temp->right, '1');
	}
	code_buf[code_index] = 0;
	code_index--;
}
/*void swap(struct node *cur)
{
	struct node temp;
	temp.fre = 0;
	temp.c = '!';
	for (int i = 0; i < 100; i++)
	{
		if(cur.fre >)
	}*/
	//}
void main()
{
	char data[10000] = { 0, };
	int char_cnt[256] = { 0, };
	scanf("%s", &data);
	char ret[100000] = { 0, };
	for (int i = 0; i < strlen(data); i++)
	{
		char_cnt[data[i]]++;
	}
	for (int i = 0; i < 256; i++)
	{
		if (char_cnt[i] > 0)
		{
			buildSLL(create(i, char_cnt[i]));
		}
	}
	int symnum = 0;
	for (int i = 0; i < 256; i++)
	{
		if (char_cnt[i] > 0)
		{
			symnum++;
		}
	}
	while (1)
	{
		struct vertex* _c = (create(' ', 1));
		if (head->next == 0)
		{
			break;
		}
		struct vertex* a = findLeast();
		struct vertex* b = findLeast();
		if (a->c < b->c)
		{
			_c->c = 'a';
			_c->fre = a->fre + b->fre;
		}
		else if (a->c > b->c)
		{
			_c->c = 'b';
			_c->fre = a->fre + b->fre;
		}
		if (a->c < b->c)
		{
			_c->left = a;
			_c->right = b;
		}
		else if (a->c > b->c)
		{
			_c->right = a;
			_c->left = b;
		}

		buildSLL(_c);
	}
	traverse(head->left, '0');
	traverse(head->right, '1');

	ret[0] = symnum + 48;
	int k = 1;
	/*int a = 0;
	struct node *kk=(struct node *)malloc(symnum);
	for (int i = 0; i < 256; i++)
	{
		if (char_cnt[i] > 0)
		{
			kk[a].fre = char_cnt[i];
			kk[a].c = i;
		}
	}*/
	for (int i = 0; i < 256; i++)
	{
		if (code[i] != 0)
		{
			ret[k] = (char)i;
			k = k + 1;
			ret[k] = strlen(code[i]) + 48;
			k = k + 1;
			for (int j = 0; j < strlen(code[i]); j++)
			{
				ret[k] = code[i][j];
				k = k + 1;
			}
		}
	}
	ret[k] = '$';
	k + 1;
	int j = 0;
	for (int j = 0; j < strlen(data); j++)
	{
		for (int i = 0; i < 256; i++)
		{
			if (i == data[j])
			{
				strcat(ret, code[i]);
			}
		}

	}
	strcat(ret, "#");
	printf("%s", ret);
}