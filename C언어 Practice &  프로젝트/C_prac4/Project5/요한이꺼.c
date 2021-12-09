#include <stdio.h>
#include <stdlib.h>
#define VERTEX_NUM 5

typedef	struct vertex {
	int vertex_num;
	struct vertex* next;

}vertex;

struct vertex graph[VERTEX_NUM];

//v1과 v2사이에 edge를 놓는다. 역방향 고려 불필요
void _putEdge(int v1, int v2) {
	// 1. 이미 v2가 붙어있는지 확인
	struct vertex* cur = graph[v1 - 1].next;
	while (cur != 0) {
		if (cur->vertex_num == v2) { //이미v2가 있으면 종료
			return;
		}
		cur = cur->next;
	}

	// 2. 없으면 v2 vertex를 만들어서 추가
	struct vertex* new_one = (vertex*)malloc(sizeof(struct vertex));
	new_one->vertex_num = v2;
	new_one->next = 0;


	cur = graph[v1 - 1].next;
	if (cur == 0) { //2.1.처음추가일때
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

//v1과 v2사이에 edge가 있음을 표시
void addEdge(int v1, int v2) {
	_putEdge(v1, v2); //_가 앞에 붙으면 함부로 쓰는게 아니라는 의미
	_putEdge(v2, v1);
}

int main() {
	//vertex array에 vertex_num을 채워넣는다.
	for (int i = 0; i < VERTEX_NUM; i++) {
		graph[i].vertex_num = i + 1;
		graph[i].next = 0;
	}

	//vertex1과 vertex3사이에는 edge가 있다.
	//주의 1->3과 3->1도 추가
	addEdge(1, 2);
	addEdge(1, 3);
	addEdge(1, 4);
	addEdge(2, 3);

	show_vertex(2);
	return 0;
}