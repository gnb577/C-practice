#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUF_SZ 100

typedef struct node
{
	char c;
	int f;
	struct node* next;
	struct node* l;
	struct node* r;
}node;

struct node* head = NULL;
char codeBuf[200];
int codebuf_idx = -1;

struct node* createNode(char _c, int _f);
void buildSLL(struct node* newone);
void cnt_num(char* buf, int* num);
struct node* findLeastFreq(void);
void travelHuff(struct node* n, char _code);


int main(void)
{
	FILE* F;
	char BUF[BUF_SZ];
	int check_num[256];

	memset(BUF, 0, sizeof(char) * BUF_SZ);
	memset(check_num, 0, sizeof(int) * 256);

	F = fopen("Alice.txt", "rt");

	if (F == NULL)
	{
		printf("fuck!\n");
		return 0;
	}

	while (fgets(BUF, sizeof(char) * (BUF_SZ - 1), F) != 0)
	{
		cnt_num(BUF, check_num);
	}
	/*
	   for(int i = 0; i < 256; i++)
	   {
		 if (check_num[i] > 0)
		 {
		   printf("%d(%c)----%d\n", i, (char)i, check_num[i]);
		 }
	   }
	*/

	fclose(F);

	for (int i = 0; i < 256; i++)
	{
		if (check_num[i] > 0)
		{
			buildSLL(createNode(i, check_num[i]));
		}
	}
	//�󵵼� ������ �̾ƿ�
	while (1)
	{
		if (head->next == NULL)
		{
			break;
		}
		struct node* a = findLeastFreq();
		struct node* b = findLeastFreq();
		struct node* c = createNode(' ', a->f + b->f);
		c->l = a;
		c->r = b;
		buildSLL(c);
	}
	// ���� Ʈ���� �������
	// head �� ����Ű�� huffman tree�� Ÿ�� �������鼭 
	// �� ���� node�� huff�ڵ带 ����� ����.

	travelHuff(head->l, '0');
	travelHuff(head->r, '1');

	return 0;
}


//���� �󵵼� ���� �ָ� ã�Ƴ���.
struct node* findLeastFreq(void)
{
	struct node* temp = head;
	int least_cnt = 9999999;
	struct node* least_one = NULL;

	while (temp != 0)
	{
		if (temp->f < least_cnt)
		{
			least_one = temp;
			least_cnt = temp->f;
		}
		temp = temp->next;
	}
	// leastone �� SLL���� ������ �ּҸ� �ش�.
	//�׷��� �Ʒ��� ������ �۾��� �Ұ���

	if (head == least_one)
	{
		head = head->next;
	}
	else
	{
		temp = head;
		while (temp->next != least_one)
		{
			temp = temp->next;
		}
		// [temp] -> [leastone] -> [leastone->next] ����
		// [temp] -> [leastone-> next]       "[least_one]" �� �и� ��
		temp->next = least_one->next;
	}

	least_one->next = NULL;
	return least_one;
}

void cnt_num(char* buf, int* num)
{
	for (int i = 0; i < strlen(buf); i++)
	{
		num[buf[i]]++;
	}
}

struct node* createNode(char _c, int _f)
{
	struct node* newone = (struct node*)malloc(sizeof(struct node));
	newone->c = _c;
	newone->f = _f;
	newone->l = NULL;
	newone->r = NULL;
	newone->next = NULL;

	return newone;
}

void buildSLL(struct node* newone)
{

	struct node* temp = head;
	if (head == NULL)
	{
		head = newone;
		return;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newone;
	}
}

void travelHuff(struct node* n, char _code)
{
	codebuf_idx++;
	codeBuf[codebuf_idx] = _code;
	codeBuf[codebuf_idx + 1] = NULL;

	//�� ������ �� ����
	if (n->l == NULL && n->r == NULL)
	{
		printf("%c ----> %s \n", n->c, codeBuf);
	}
	else
	{
		// �� �ؿ� ��������, �ڵ� �ϳ� �߰���
		travelHuff(n->l, '0');
		travelHuff(n->r, '1');
	}
	//��� �Լ� ������ ���� ���� �ڵ� ������
	codeBuf[codebuf_idx] = NULL;
	codebuf_idx--;
}