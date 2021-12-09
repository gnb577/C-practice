#include <stdio.h>
#include <stdlib.h>

int VERTEX_NUM = 7;

int* graph = 0;
int* stack = 0;
int top = -1;
int* visited = 0;

void push(int v)
{
	if (top == VERTEX_NUM - 1)
	{
		// stack full
		return;
	}
	top = top + 1;
	stack[top] = v;
}

int pop()
{
	if (top == -1)
	{
		// stack 비었음.
		return -999;
	}
	int ret = top;
	top = top - 1;
	return stack[ret];
}

void addEdge(int v1, int v2)
{
	graph[v1 * VERTEX_NUM + v2] = 1;
	graph[v2 * VERTEX_NUM + v1] = 1;
}


int search(int num)
{
	int* ret_stack = (int *)malloc(sizeof(int)*VERTEX_NUM*VERTEX_NUM);
	ret_stack = stack;
	int k = 0;
	int flag = 0;
	while(ret_stack[k] != 0)
	{
		if (ret_stack[k] == num)
		{
			flag = 1;
		}
		k++;
	}
	if (flag == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



void show_path(int _vertex_num)
{
	printf("%d ", _vertex_num);
	return;
}

/*

  v부터 시작해서,,, DFS
*/
void doDFS(int v)
{
	int cur_vertex;
	int f;
	// 1. v를 stack에 넣는다.
	push(v);

	// stack이 비어있지 않는 한...
	while (1)
	{
		cur_vertex = pop();

		if (cur_vertex == -999)
		{
			return;
		}

		// 1. stack에서 꺼내서 visited
		visited[cur_vertex] = 1;
		show_path(cur_vertex);


		// 2. 친구들을 찾아서 stack에 push
		for (f = cur_vertex * VERTEX_NUM;
			f < cur_vertex * VERTEX_NUM + VERTEX_NUM;
			f++)
		{
			if (graph[f] == 1) // 친구
			{
				int real_f = f - cur_vertex * VERTEX_NUM;
				int search_stack = search(real_f);
				if (visited[real_f] == 0 && search_stack == 0/* stack에 없으면*/)
				{
					push(real_f);
				}

			}
		}



	}
}

void show_visited()
{
	int num = VERTEX_NUM;
	printf("\n");
	for (int i = 0; i < VERTEX_NUM;i++)
	{
		printf("%d ", visited[i]);
	}
	return;
}

int main(void)
{
	int i;
	// 그래프 구성
	graph = (int*)malloc(sizeof(int) * VERTEX_NUM * VERTEX_NUM);
	// 초기화
	for (i = 0; i < VERTEX_NUM * VERTEX_NUM; i++)
	{
		graph[i] = 0;
	}
	// edge 정보를 추가한다.
	addEdge(0, 1);
	addEdge(0, 2);
	addEdge(0, 3);
	addEdge(4, 2);
	addEdge(2, 3);

	// stack 구성
	stack = (int*)malloc(sizeof(int) * VERTEX_NUM);
	for (i = 0; i < VERTEX_NUM; i++)
	{
		stack[i] = 0;
	}
	visited = (int*)malloc(sizeof(int) * VERTEX_NUM);
	for (i = 0; i < VERTEX_NUM; i++)
	{
		visited[i] = 0;
	}

	// DFS 시작
	// vertex 0번부터 시작해서 gogogo...
	doDFS(0);
	show_visited();



	return 0;
}