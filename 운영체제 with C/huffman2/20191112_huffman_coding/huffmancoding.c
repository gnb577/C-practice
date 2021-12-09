#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//전역변수와 지역변수의 차이
//전역변수 자동으로 0으로 초기화, 지역변수는 쓰레기값
//지역변수는 stack영역, 전역변수는 heap영역
//stack영역은 크기가 작아서
//메모리를 크게 사용하고 싶으면 전역변수,(heap 영역)을 사용

int char_cnt[256];
char codebuf[200];
int codebuf_idx = -1;

typedef struct node {
	char c;
	int frequency;
	struct node* next;
	struct node* left;
	struct node* right;
}node;

node* head = 0;

void traverseHtree(node* n, char _code)
{
	codebuf_idx++;
	codebuf[codebuf_idx] = _code;
	codebuf[codebuf_idx + 1] = 0;

	if (n->left == 0 && n->right == 0)
	{
		//내가 맨 마지막 노드 == 문자가 담겨있는 노드
		printf("%c ------> %s\n", n->c, codebuf);
	}
	else
	{
		//내 밑에 node가 더있으면 코드를 추가해서 내려보낸다
		traverseHtree(n->left, '0');
		traverseHtree(n->right, '1');
	}
	//돌아갈 때는 내가 받았던 코드를 삭제하고
	codebuf[codebuf_idx] = 0;
	codebuf_idx--;
}
// 노드를 할당받아서 필요한 정보를 넣고
// 생성된 노드의 주소를 반환하는 함수 

node* createnode(char _c, int _frequency)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->c = _c;
	new_node->frequency = _frequency;
	new_node->next = 0;
	new_node->left = 0;
	new_node->right = 0;

	return new_node;

}

void addsll(node* new_node)
{
	node* temp = head;
	//sll이 비어있는 경우
	if (head == 0)
	{
		head = new_node;
		return;
	}

	//sll의 끝을 찾아서 맨 끝에 추가

	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_node;

	return;
}



void show_table()
{
	for (int i = 0; i < 256; i++)
	{
		unsigned char k;
		k = i;
		printf("%d-------->%d\n", i, char_cnt[i]);
	}
}

//sll에서 빈도수가 가장 작은 노드를 찾아내고
//sll에서 분리해서 그 주소를 반환
node* findleast()
{
	node* temp = head;
	int leastcnt = 1000;
	node* leastone = 0;

	//빈도수가 가장 작은 노드를 찾아낸다
	while (temp != 0)
	{
		if (temp->frequency < leastcnt)
		{
			leastcnt = temp->frequency;
			leastone = temp;
		}
		temp = temp->next;
	}
	//leastone을 sll에서 분리해서
	//주소를 반환
	if (head == leastone) // 대가리를 분리함
	{
		//node* temp = head;
		head = head->next;
		
	}
	else
	{
		//leastone을 가리키는 바로 앞의 노드를 찾자
		temp = head;
		while (temp->next != leastone)
		{
			temp = temp->next;
		}
		//현재 temp가 leastone->prev 와 같음
		temp->next = leastone->next;
	}

	leastone->next = 0;
	return leastone;
}


int main()
{
	FILE* f;
	char buf[1000];

	memset(char_cnt, 0, sizeof(int) * 256);
	for (int i = 0; i < 256; i++)
	{
		printf("%d-------->%d\n", i, char_cnt[i]);
	}
	//fopen
	f = fopen("alice.txt", "rt");
	if (f == 0)
	{
		printf("unable to open alice.txt");
		return;
	}
	while (1)
	{
		int i;
		char* temp = fgets(buf, 1000, f); // 100byte만 읽겟다
		if (temp == 0)
		{
			break;
		}

		for (i = 0; i < strlen(buf); i++)
		{
			char_cnt[buf[i]]++;
		}
		printf("%s", buf);
	}
	show_table();
	//fclose
	fclose(f);

	for (int i = 0; i < 256; i++)
	{
		//빈도수 테이블을 sll로 만든다
		if (char_cnt[i] > 0) //나타나지 않은 글자는 안하려고
		{
			addsll(createnode(i, char_cnt[i]));
		}
	}
	while (1)
	{
		//제일 작은 두 개를 묶는 과정
		if (head->next == 0) // root노드만 남은 상황
		{
			break;
		}
		node* a = findleast();
		node* b = findleast();
		node* c = creatnode(' ', a->frequency + b->frequency);
		c->left = a;
		c->right = b;
		addsll(c);
	}

	//head가 가리키는 허프만 트리 타고 내려가면서
	//각 종말 node의 허프만 코드를 만들어 낸다.
	traverseHtree(head->left, '0');
	traverseHtree(head->right, '1');
	

	
	return 0;
}

