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
		// stack �����.
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

  v���� �����ؼ�,,, DFS
*/
void doDFS(int v)
{
	int cur_vertex;
	int f;
	// 1. v�� stack�� �ִ´�.
	push(v);

	// stack�� ������� �ʴ� ��...
	while (1)
	{
		cur_vertex = pop();

		if (cur_vertex == -999)
		{
			return;
		}

		// 1. stack���� ������ visited
		visited[cur_vertex] = 1;
		show_path(cur_vertex);


		// 2. ģ������ ã�Ƽ� stack�� push
		for (f = cur_vertex * VERTEX_NUM;
			f < cur_vertex * VERTEX_NUM + VERTEX_NUM;
			f++)
		{
			if (graph[f] == 1) // ģ��
			{
				int real_f = f - cur_vertex * VERTEX_NUM;
				int search_stack = search(real_f);
				if (visited[real_f] == 0 && search_stack == 0/* stack�� ������*/)
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
	// �׷��� ����
	graph = (int*)malloc(sizeof(int) * VERTEX_NUM * VERTEX_NUM);
	// �ʱ�ȭ
	for (i = 0; i < VERTEX_NUM * VERTEX_NUM; i++)
	{
		graph[i] = 0;
	}
	// edge ������ �߰��Ѵ�.
	addEdge(0, 1);
	addEdge(0, 2);
	addEdge(0, 3);
	addEdge(4, 2);
	addEdge(2, 3);

	// stack ����
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

	// DFS ����
	// vertex 0������ �����ؼ� gogogo...
	doDFS(0);
	show_visited();



	return 0;
}