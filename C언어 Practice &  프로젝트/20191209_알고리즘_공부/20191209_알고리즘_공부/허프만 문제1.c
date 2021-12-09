#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define ascii 100
#define sz 100

int buf_cnt[ascii];
char code[ascii][sz];
char code2[ascii][sz];
char make_code[sz];
char input[sz];
int code_idx = -1;

typedef struct node
{
	char c;
	int fre;
	struct node* next;
	struct node* right;
	struct node* left;
}node;

node* head = 0;

node* findleast()
{
	node* temp = head;
	int least = 99999;
	node* leastone = 0;
	while (temp != 0)
	{
		if (least > temp->fre)
		{
			least = temp->fre;
			leastone = temp;
		}
		temp = temp->next;
	}
	if (leastone == head)
	{
		head = head->next;
	}
	else
	{
		temp = head;
		while (temp->next != leastone)
		{
			temp = temp->next;
		}
		temp->next = leastone->next;
	}
	leastone->next = 0;
	return leastone;
}

void traversal(node* temp, char _code)
{
	code_idx++;
	make_code[code_idx] = _code;
	make_code[code_idx + 1] = 0;
	if (temp->left == 0 && temp->right == 0)
	{
		strcpy(code2[temp->c], make_code);
		printf("%c %s %s\n", temp->c, code2[temp->c], code[temp->c]);
	}
	else
	{
		traversal(temp->left, '0');
		traversal(temp->right, '1');
	}
	make_code[code_idx] = 0;
	code_idx--;
}

node* createnode(char _c, int _r)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->c = _c;
	new_node->fre = _r;
	new_node->next = new_node->right = new_node->left = 0;
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


int main()
{
	int char_cnt;
	scanf("%d,", &char_cnt);

	scanf("%s", input);
	int i = 0;
	while (1)
	{
		if (input[i] == '$')
		{
			break;
		}
		char something = input[i];
		buf_cnt[input[i]] = input[i + 1] - 48;
		i++;
		int j = 0;
		while (1)
		{
			i++;
			if (input[i] <= '1' && input[i] >= '0')
			{
				code[something][j] = input[i];
				j++;
			}
			else
			{
				break;
			}

		}
	}
	for (int a = 0; a < ascii; a++)
	{
		if (buf_cnt[a] > 0)
		{
			addsll(createnode(a, buf_cnt[a]));
		}
	}
	while (1)
	{
		if (head->next == 0) //root노드까지 끝냈을때
		{
			break;
		}
		node* a = findleast();
		node* b = findleast();
		node* c = createnode(' ', a->fre + b->fre);
		c->left = a;
		c->right = b;
		addsll(c);
	}
	traversal(head->left, '0');
	traversal(head->right, '1');
}