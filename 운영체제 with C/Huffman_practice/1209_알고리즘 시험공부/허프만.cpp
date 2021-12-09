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
	int i = 1;
	while (1)
	{
		if (tempstring[i] == '$')
		{
			i++;
			break;
		}
		char alpha = tempstring[i];
		i++;
		buf_cnt[alpha] = tempstring[i] - 48;
		int j = 0;
		while (1)
		{
			i++;
			if (tempstring[i] == '0' || tempstring[i] == '1')
			{
				code[alpha][j] = tempstring[i];
				j++;
			}
			else
			{
				code[alpha][j] = 0;
				break;
			}
		}
		printf("%c(%d°³) ---- %s\n", alpha, buf_cnt[alpha], code[alpha]);
	}
	int k = 0;
	while (1)
	{
		if (tempstring[i] == '#')
		{
			break;
		}
		make_code[k] = tempstring[i];
		make_code[k + 1] = 0;
		i++;
		//printf("%s %s\n", code[0], make_code[k]);
		/*
		for (int m = 0; m < ascii; m++)
		{
			printf("%s %s\n", code[m], make_code[k]);
			if (strcpy(code[m], make_code[k]) == 0)
			{
				printf("%c", m);
				for (int d = 0; d < 100; d++)
				{
					make_code[d] = 0;
				}
				//memset(make_code, 0, sizeof(char) * 100);
				break;
			}
		}
		i++;
		*/
	}

}

/*
3a200b11c201$00001101#
*/