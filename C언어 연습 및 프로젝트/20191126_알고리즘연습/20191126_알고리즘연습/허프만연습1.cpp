#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int n;
	char c;
	struct node* l;
	struct node* r;
	struct node* link;
}node;

node* head;

int c_index = -1;
char code[100] = { 0, };
int sum = 0;

node* create(char c, int n) {
	node* new = (node*)malloc(sizeof(node));
	new->n = n;
	new->c = c;
	new->l = new->r = new->link = 0;
	return new;
}

void addSLL(node* new) {
	if (head == 0) {
		head = new;
		return;
	}
	else {
		node* temp = head;
		while (temp->link != 0) {
			temp = temp->link;
		}
		temp->link = new;
	}
}

node* findLeast() {
	int least = 99999;
	node* find = 0;
	node* temp = head;

	while (temp != 0) {
		if (temp->n < least) {
			least = temp->n;
			find = temp;
		}
		temp = temp->link;
	}

	if (head == find) head = head->link;
	else {
		node* prev = head;
		while (prev->link != find) 
		{
			prev = prev->link;
		}
		prev->link = find->link;
	}
	find->link = 0;
	return find;
}

void traverse(node* temp, char _code) {
	c_index++;
	code[c_index] = _code;
	code[c_index + 1] = 0;

	if (temp->l == 0 && temp->r == 0) {
		sum = sum + strlen(code);
	}
	else {
		traverse(temp->l, '0');
		traverse(temp->r, '1');
	}
	code[c_index] = 0;
	c_index--;
}

void main() {
	int n, i;
	char c;
	int cnt[256] = { 0, };

	while (1) {
		scanf("%c ", &c);
		scanf("%d\n", &n);
		//if (c == '\n'||c==' ') continue;
		if (n == -1) break;
		cnt[c] = n;
	}

	for (i = 0; i < 256; i++) {
		if (cnt[i] > 0) {
			addSLL(create(i, cnt[i]));
		}
	}

	while (1) {
		if (head->link == 0) break;

		node* s1 = findLeast();
		node* s2 = findLeast();
		node* new = create(' ', s1->n + s2->n);
		new->l = s1;
		new->r = s2;
		addSLL(new);
	}

	traverse(head->l, '0');
	traverse(head->r, '1');
	printf("%d", sum);
}