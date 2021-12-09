#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 5
typedef struct graph {
	int n;
	struct graph* link;
}graph;

graph* g[MAX_NUM];

void add(int a, int b) {

	graph* new = (graph*)malloc(sizeof(graph));
	new->n = b;
	new->link = 0;

	if (g[a - 1] == 0) {
		g[a - 1] = new;
		return;
	}

	graph* cur = g[a - 1];

	while (cur != 0) {
		if (cur->n == b) {
			return;
		}
		cur = cur->link;
	}

	new->link = g[a - 1];
	g[a - 1] = new;
}

void put(int a, int b) {
	add(a, b);
	add(b, a);
}

void show() {
	int i;
	for (i = 0; i < MAX_NUM; i++) {
		graph* cur = g[i];
		printf("\n%d ", i + 1);
		while (cur != 0) {
			printf("%d ", cur->n);
			cur = cur->link;
		}
	}
}

int main() {
	put(1, 2);
	put(2, 3);
	put(1, 3);
	
	show();
}