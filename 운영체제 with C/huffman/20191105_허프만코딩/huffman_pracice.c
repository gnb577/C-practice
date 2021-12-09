#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct node
{
	char v;
	int cnt;
	struct node* next;
	struct node* prev;
}node;

node* head = 0;
node* tail = 0;
int cnt = 0;

void addedge(char _v)
{
	node* temp = head;
	node* new_node = (node*)malloc(sizeof(node));
	new_node->v = _v;
	new_node->cnt = 1;
	new_node->next=  0;
	new_node->prev = 0;

	if (temp == 0)
	{
		head = new_node;
		tail = new_node;
		cnt++;
		return;
	}
	else
	{
		while (temp->next != 0)
		{
			if (temp->v == _v)
			{
				temp->cnt++;
				free(new_node);
				return;
			}
			temp = temp->next;

		}
		temp->next = new_node;
		tail = new_node;
		new_node->prev = temp;
		cnt++;
	}
	return;
}

void sort(int cnt)
{
	
	//int min_cnt = temp->cnt;
	for (int i = 0; i < cnt; i++)
	{
		node* temp = head;
		while (temp->next != 0)
		{
			if (temp->cnt > temp->next->cnt)
			{
				int cur_count = temp->cnt;
				temp->cnt = temp->next->cnt;
				temp->next->cnt = cur_count;
				char cur_v = temp->v;
				temp->v = temp->next->v;
				temp->next->v = cur_v;
			}
			temp = temp->next;
		}
	}
	return;
}

void sort2(int cnt)
{
	
	node* temp2 = tail;
	for (int i = 0; i < cnt; i++)
	{
		node* temp = head;
		temp2 = temp2->prev;
		if (temp2 == 0)
		{
			return;
		}
		while (temp != temp2->next)
		{
			if (temp->cnt > temp->next->cnt)
			{
				int cur_count = temp->cnt;
				temp->cnt = temp->next->cnt;
				temp->next->cnt = cur_count;
				char cur_v = temp->v;
				temp->v = temp->next->v;
				temp->next->v = cur_v;
				//printf("%d ", temp->v);
			}
			temp = temp->next;
		}
	}
}


void sort3()
{

	node* temp2 = tail;
	while(temp2 != 0)
	{
		node* temp = head;
		temp2 = temp2->prev;
		while (temp->next != temp2)
		{
			if (temp->cnt > temp->next->cnt)
			{
				int cur_count = temp->cnt;
				temp->cnt = temp->next->cnt;
				temp->next->cnt = cur_count;
				char cur_v = temp->v;
				temp->v = temp->next->v;
				temp->next->v = cur_v;
				//printf("%d ", temp->v);
			}
			temp = temp->next;
		}
	}
	return;
}

void show()
{
	node* temp = head;
	while (temp != 0)
	{
		printf("%c ----- %d\n", temp->v, temp->cnt);
		temp = temp->next;
	}
	return;
}
int main()
{	

	FILE* f;
	char buf[100];
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
		char* temp = fgets(buf, 100, f); // 100byte¸¸ ÀÐ°Ù´Ù
		if (temp == 0)
		{
			break;
		}
		for (i = 0; i < strlen(buf); i++)
		{
			addedge(buf[i]);
		}
		//printf("%s", buf);
	}
	//sort(cnt);
	//sort2(cnt);
	//sort3();
	show();
	//fclose
	fclose(f);

	return 0;
}
	
