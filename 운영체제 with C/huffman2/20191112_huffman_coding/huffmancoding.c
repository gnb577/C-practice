#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//���������� ���������� ����
//�������� �ڵ����� 0���� �ʱ�ȭ, ���������� �����Ⱚ
//���������� stack����, ���������� heap����
//stack������ ũ�Ⱑ �۾Ƽ�
//�޸𸮸� ũ�� ����ϰ� ������ ��������,(heap ����)�� ���

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
		//���� �� ������ ��� == ���ڰ� ����ִ� ���
		printf("%c ------> %s\n", n->c, codebuf);
	}
	else
	{
		//�� �ؿ� node�� �������� �ڵ带 �߰��ؼ� ����������
		traverseHtree(n->left, '0');
		traverseHtree(n->right, '1');
	}
	//���ư� ���� ���� �޾Ҵ� �ڵ带 �����ϰ�
	codebuf[codebuf_idx] = 0;
	codebuf_idx--;
}
// ��带 �Ҵ�޾Ƽ� �ʿ��� ������ �ְ�
// ������ ����� �ּҸ� ��ȯ�ϴ� �Լ� 

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
	//sll�� ����ִ� ���
	if (head == 0)
	{
		head = new_node;
		return;
	}

	//sll�� ���� ã�Ƽ� �� ���� �߰�

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

//sll���� �󵵼��� ���� ���� ��带 ã�Ƴ���
//sll���� �и��ؼ� �� �ּҸ� ��ȯ
node* findleast()
{
	node* temp = head;
	int leastcnt = 1000;
	node* leastone = 0;

	//�󵵼��� ���� ���� ��带 ã�Ƴ���
	while (temp != 0)
	{
		if (temp->frequency < leastcnt)
		{
			leastcnt = temp->frequency;
			leastone = temp;
		}
		temp = temp->next;
	}
	//leastone�� sll���� �и��ؼ�
	//�ּҸ� ��ȯ
	if (head == leastone) // �밡���� �и���
	{
		//node* temp = head;
		head = head->next;
		
	}
	else
	{
		//leastone�� ����Ű�� �ٷ� ���� ��带 ã��
		temp = head;
		while (temp->next != leastone)
		{
			temp = temp->next;
		}
		//���� temp�� leastone->prev �� ����
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
		char* temp = fgets(buf, 1000, f); // 100byte�� �аٴ�
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
		//�󵵼� ���̺��� sll�� �����
		if (char_cnt[i] > 0) //��Ÿ���� ���� ���ڴ� ���Ϸ���
		{
			addsll(createnode(i, char_cnt[i]));
		}
	}
	while (1)
	{
		//���� ���� �� ���� ���� ����
		if (head->next == 0) // root��常 ���� ��Ȳ
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

	//head�� ����Ű�� ������ Ʈ�� Ÿ�� �������鼭
	//�� ���� node�� ������ �ڵ带 ����� ����.
	traverseHtree(head->left, '0');
	traverseHtree(head->right, '1');
	

	
	return 0;
}

