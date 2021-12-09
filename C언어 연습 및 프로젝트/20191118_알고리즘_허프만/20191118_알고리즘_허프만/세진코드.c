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
	//빈도수 낮은애 뽑아요
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
	// 이제 트리다 만든거임
	// head 가 가리키는 huffman tree를 타고 내려가면서 
	// 각 종단 node의 huff코드를 만들어 낸다.

	travelHuff(head->l, '0');
	travelHuff(head->r, '1');

	return 0;
}


//가장 빈도수 낮은 애를 찾아낸다.
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
	// leastone 을 SLL에서 꺼내서 주소를 준다.
	//그래서 아래는 꺼내는 작업을 할거유

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
		// [temp] -> [leastone] -> [leastone->next] 에서
		// [temp] -> [leastone-> next]       "[least_one]" 로 분리 함
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

	//맨 끝까지 다 가면
	if (n->l == NULL && n->r == NULL)
	{
		printf("%c ----> %s \n", n->c, codeBuf);
	}
	else
	{
		// 내 밑에 더있으면, 코드 하나 추가요
		travelHuff(n->l, '0');
		travelHuff(n->r, '1');
	}
	//재귀 함수 끝날땐 내가 받은 코드 삭제요
	codeBuf[codebuf_idx] = NULL;
	codebuf_idx--;
}