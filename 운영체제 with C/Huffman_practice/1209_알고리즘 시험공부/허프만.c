/*
travesal
add
create
show
findleast


*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define sz 100
#define ascii 256
char buf[100][100];
int buf_cnt[ascii];
char decode_buf[ascii];
char make_code[100];
char tempstring[100];
char code[ascii][100];
typedef struct node
{
	char c;
	int freq;
	struct node* next;
	struct node* left;
	struct node* right;
}node;

node* head = 0;

node* createnode(int _c, int _freq)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->freq = _freq;
	new_node->c = _c;
	new_node->next = 0;
	new_node->left = 0;
	new_node->right = 0;
	return new_node;
}

void add(int _c, int _freq)
{
	node* new_node = createnode(_c, _freq);

}
int main()
{
	scanf("%s", tempstring);
	

}

/*
3a200b11c201$00001101#
*/