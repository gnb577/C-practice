#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
	char v;
	int freq;
	struct node* left;
	struct node* right;
};
struct node* huffRoot =(node*)malloc(sizeof(node));
struct node* cur=huffRoot;

void traversal(node* cur, char _code)
{
	if (cur->left == 0 && cur->right == 0)
	{
		printf("%c", cur->v);
		cur = huffRoot;
	}
	if (_code == '0') {
		cur = cur->left;
	}
	else if (_code == '1') {
		cur = cur->right;
	}
	else {

	}
}

int main() {
	huffRoot->left = huffRoot->right = 0;
	char text[100] = "3a200b11c201$00001";
	int num = text[0] - '0';
	int textIdx = 0;
	for (int i = 0; i < num; i++)
	{
		char cha = text[++textIdx];
		int cha_len = text[++textIdx] -'0';
		cur = huffRoot;
		for (int i = 0; i < cha_len; i++)
		{
			if (text[textIdx+1] == '0') {
				if (cur->left != 0) {
					cur->left = (node*)malloc(sizeof(node));
					cur->left->left = 0;
					cur->left->right = 0;
				}
				cur = cur->left;
				textIdx++;
			}
			else if (text[textIdx] == '1') {
				if (cur->right != 0) {
					cur->right = (node*)malloc(sizeof(node));
					cur->right->left = 0;
					cur->right->right = 0;
				}
				cur = cur->right;
				textIdx++;

			}
			else {
				printf("CRITICAL ERROr");
			}
		}
		cur->v = cha;
	}
	textIdx++;
	while (text[textIdx] != '#') {
		traversal(cur, text[++textIdx]);
	}
	
}
