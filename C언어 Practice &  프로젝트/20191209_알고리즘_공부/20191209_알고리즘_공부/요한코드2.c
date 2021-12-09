#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
typedef struct node {
	char c;
	int freq;
	struct node* left;
	struct node* right;
}node;

node* head = 0;
head = (node*)malloc(sizeof(node));

char text[100];
int idx = 0;
int len = 0;

int main() {
	scanf("%s", text);
	char alphabet;
	while (1)
	{
		alphabet = text[idx];
		idx++;
		len = text[idx]-48;
		idx++;
		for (int i = 0; i < len; i++)
		{
			if (text[idx] == '0')
			{
				
			}
			else if (text[idx] == '1')
			{

			}
		}
	}

}
