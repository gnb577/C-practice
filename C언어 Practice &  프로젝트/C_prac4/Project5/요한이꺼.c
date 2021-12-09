#include <stdio.h>
#include <stdlib.h>
#define VERTEX_NUM 5

typedef	struct vertex {
	int vertex_num;
	struct vertex* next;

}vertex;

struct vertex graph[VERTEX_NUM];

//v1�� v2���̿� edge�� ���´�. ������ ��� ���ʿ�
void _putEdge(int v1, int v2) {
	// 1. �̹� v2�� �پ��ִ��� Ȯ��
	struct vertex* cur = graph[v1 - 1].next;
	while (cur != 0) {
		if (cur->vertex_num == v2) { //�̹�v2�� ������ ����
			return;
		}
		cur = cur->next;
	}

	// 2. ������ v2 vertex�� ���� �߰�
	struct vertex* new_one = (vertex*)malloc(sizeof(struct vertex));
	new_one->vertex_num = v2;
	new_one->next = 0;


	cur = graph[v1 - 1].next;
	if (cur == 0) { //2.1.ó���߰��϶�
		graph[v1 - 1].next = new_one;
	}
	else { //2.2
		while (cur->next != 0) {
			cur = cur->next;
		}
		cur->next = new_one;
	}

	return;
}

void show_vertex(int _v) {
	struct vertex* cur = graph[_v - 1].next;
	while (cur != 0) {
		printf("%d ", cur->vertex_num);
		cur = cur->next;
	}
}

//v1�� v2���̿� edge�� ������ ǥ��
void addEdge(int v1, int v2) {
	_putEdge(v1, v2); //_�� �տ� ������ �Ժη� ���°� �ƴ϶�� �ǹ�
	_putEdge(v2, v1);
}

int main() {
	//vertex array�� vertex_num�� ä���ִ´�.
	for (int i = 0; i < VERTEX_NUM; i++) {
		graph[i].vertex_num = i + 1;
		graph[i].next = 0;
	}

	//vertex1�� vertex3���̿��� edge�� �ִ�.
	//���� 1->3�� 3->1�� �߰�
	addEdge(1, 2);
	addEdge(1, 3);
	addEdge(1, 4);
	addEdge(2, 3);

	show_vertex(2);
	return 0;
}