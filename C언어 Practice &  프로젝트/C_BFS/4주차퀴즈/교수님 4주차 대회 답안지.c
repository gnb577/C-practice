#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int VERTEX_NUM;
int data1 = 0;
int data2 = 0;
int* graph = 0;
int* queue = 0;
int front = 0;
int rear = 0;
int* visited = 0;
int mystery = 0;
int* sum;
int a = 0;

/*
 Queue full 이면 단순히 return
*/
void enqueue(int v)
{
	if ((rear + 1) % VERTEX_NUM == front)
	{
		return;
	}
	queue[rear] = v;
	rear = (rear + 1) % VERTEX_NUM;
	return;
}

/*
 Empty queue이면 -999를 return
*/
int dequeue()
{
	if (front == rear)
	{
		return -999;
	}
	int temp = queue[front];
	front = (front + 1) % VERTEX_NUM;
	return temp;
}

void addEdge(int v1, int v2)
{
	graph[v1 * VERTEX_NUM + v2] = 1;
	graph[v2 * VERTEX_NUM + v1] = 1;
}


/*
 queue에 vertex v가 있으면, 1
 없으면 0을 반환
*/
int isInQueue(int v)
{
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		if (queue[i] == v)
		{
			return 1;
		}
	}
	return 0;
}

/*
  v부터 시작해서,,, DFS
*/

int search_que(int v)
{
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		if (queue[i] == v)
		{
			return 1;
		}
	}
	return 0;
}


int doBFS(int v,int a, int b)
{
	int cur_vertex;
	int f;

	// 1. v를 stack에 넣는다.
	enqueue(v);

	// queue가 비어있지 않는 한...
	while (1)
	{
		cur_vertex = dequeue();

		if (cur_vertex == -999)
		{
			return;
		}

		// 1. queue에서 꺼내서 visited
		visited[cur_vertex] = 1;
		if (cur_vertex == a)
		{
			if (visited[b] == 0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

		// 아래 코드는 절대 수정하지 마세요.
		//edge의 갯수
		for (f = cur_vertex * VERTEX_NUM; f < cur_vertex * VERTEX_NUM + VERTEX_NUM; f++)
		{

			if (graph[f] == 1)
			{
				int real_i = f - cur_vertex * VERTEX_NUM;
				int search = isInQueue(real_i);
				if (visited[real_i] == 0 && search == 0)
				{
					enqueue(real_i);
				}
			}

		}
		//------------------------------
		// 여기부터는 수정해도 됩니다.


		// 2. 친구들을 찾아서 queue에 enqueue
		//
		// 위 설명을 구현하시오.
		//
	}
}


int main(void)
{
	int v1, v2;
	int i;
	scanf("%d", &VERTEX_NUM);

	// 그래프 구성
	graph = (int*)malloc(sizeof(int) * VERTEX_NUM * VERTEX_NUM);
	// 초기화
	for (i = 0; i < VERTEX_NUM * VERTEX_NUM; i++)
	{
		graph[i] = 0;
	}

	while (1)
	{
		scanf("%d %d", &v1, &v2);
		if ((v1 == -1) && (v2 == -1))
		{
			break;
		}
		addEdge(v1, v2);
	}

	scanf("%d %d", &data1, &data2);
	// Queue 구성
	queue = (int*)malloc(sizeof(int) * VERTEX_NUM);
	for (i = 0; i < VERTEX_NUM; i++)
	{
		queue[i] = 0;
	}
	visited = (int*)malloc(sizeof(int) * VERTEX_NUM);
	for (i = 0; i < VERTEX_NUM; i++)
	{
		visited[i] = 0;
	}
	sum = (int*)malloc(sizeof(int) * VERTEX_NUM);
	for (i = 0; i < VERTEX_NUM; i++)
	{
		sum[i] = -1;
	}

	// BFS 시작
	int ans = doBFS(0,data1,data2);


	printf("%d", ans);

	return 0;
}

/*
3

0 1

0 2

-1 -1

1 0
*/