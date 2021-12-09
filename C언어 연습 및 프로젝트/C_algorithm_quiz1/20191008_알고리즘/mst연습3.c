#include <stdio.h>
#include <stdlib.h>

#define VERTEX_NUM 5
#define EDGES_NUM 8
typedef struct vertex {
	int vertex_num;
	int weight;
	struct vertex* next;
}vertex;

typedef struct edge
{
	int from;
	int to;
	int w;
}edge;

edge edges[EDGES_NUM];
vertex* graph[VERTEX_NUM];

int cycle_detection[VERTEX_NUM] = { 0,1,2,3,4 };

int stack[VERTEX_NUM];
int top = -1;
int visited[VERTEX_NUM];

void samegroup(int v1, int v2)
{
	int g1 = cycle_detection[v1];
	int g2 = cycle_detection[v2];
	int smaller, bigger;
	if (g1 > g2)
	{
		bigger = g1;
		smaller = g2;
	}
	else
	{
		bigger = g2;
		smaller = g1;
	}
	{
		int i;
		for (i = 0; i < VERTEX_NUM; i++)
		{
			if (cycle_detection[i] == bigger)
			{
				cycle_detection[i] = smaller;
			}
		}
	}
}
int isStackEmpty() {
	if (top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}
void push(int v) {
	if (top == VERTEX_NUM - 1) {
		return;
	}
	top++;
	stack[top] = v;
}
int pop() {
	if (top == -1) {
		return -1;
	}
	top--;
	return stack[top + 1];
}

void addedge(int v1, int v2, int w, int doReverse) {
	/*
	vertex* cur = graph[v1]->next;
	while (cur != 0) {
		if (cur->vertex_num == v2) {
			return;
		}
		cur = cur->next;
	}
	*/
	vertex* new_one = (vertex*)malloc(sizeof(vertex));
	new_one->vertex_num = v2;
	new_one->next = 0;
	new_one->weight = w;
	vertex* cur = graph[v1];
	cur = graph[v1];
	if (cur == 0) {
		graph[v1] = new_one;
	}
	else {
		while (cur->next != 0) {
			cur = cur->next;
		}
		cur->next = new_one;
	}
	if (doReverse == 1) {
		addedge(v2, v1, w, 0);
	}
}
void show_vertex(int v) {
	vertex* cur = graph[v]->next;
	while (cur != 0) {
		printf("%d->", cur->vertex_num);
		cur = cur->next;
	}
	printf("\n");
}
int findNextVertex(int v) {
	vertex* cur = graph[v]->next;
	while (cur != 0) {
		if (visited[cur->vertex_num] == 0) {
			return cur->vertex_num;
		}
		cur = cur->next;
	}
	return -1;
}
void doDFS(int v) {
	push(v);
	visited[v] = 1;
	printf("%d->", v);

	while (isStackEmpty() == 0) {
		int next_vertex = findNextVertex(stack[top]);
		if (next_vertex == -1) {
			pop();
		}
		else {
			push(next_vertex);
			visited[next_vertex] = 1;
			printf("%d->", next_vertex);
		}
	}
}

void swap_edge(int e1, int e2)
{
	edge temp;
	temp = edges[e1];
	edges[e1] = edges[e2];
	edges[e2] = temp;
}

void sortEdges()
{
	//모든 edge를 edges배열에 추가
	int i;
	int edges_index = 0;
	for (i = 0; i < VERTEX_NUM; i++)
	{
		vertex* temp = graph[i];
		while (temp != 0)
		{
			edges[edges_index].from = i;
			edges[edges_index].to = temp->vertex_num;
			edges[edges_index].w = temp->weight;
			edges_index++;
			temp = temp->next;
		}
	}
	//오름차순으로 정렬,by bubble sort
	{
		int x, y;
		for (y = 0; y < EDGES_NUM; y++)
		{
			for (x = 0; x < EDGES_NUM - 1 - y; x++)
			{
				if (edges[x].w > edges[x + 1].w)
				{
					swap_edge(x, x + 1);
				}
			}
		}
	}
}

void domst()
{
	int i;
	int mst_edges = 0;
	for (int i = 0; i < EDGES_NUM; i++)
	{
		if (cycle_detection[edges[i].from] != cycle_detection[edges[i].to])
		{
			printf("MST edge %d --- %d(%d) \n", edges[i].from, edges[i].to, edges[i].w);
			mst_edges++;
			if (mst_edges == VERTEX_NUM - 1)
			{
				return;
			}
			samegroup(edges[i].from, edges[i].to);
		}
	}
}

int main() {


	addedge(0, 1, 1, 0);
	addedge(0, 2, 3, 0);
	addedge(0, 4, 5, 0);
	addedge(1, 2, 2, 0);
	addedge(1, 4, 4, 0);
	addedge(2, 4, 6, 0);
	addedge(2, 3, 7, 0);
	addedge(3, 4, 8, 0);

	//doDFS(0);
	sortEdges();
	domst();
}

/*
addedge(0,1,1,0);
addedge(0,2,3,0);
addedge(0,4,5,0);
addedge(1,2,2,0);
addedge(1,4,4,0);
addedge(2,4,6,0);
addedge(2,3,7,0);
addedge(3,4,8,0);
*/
/*
	addEdge(0, 1,0, 1);
	addEdge(1, 4, 0,1);
	//addEdge(0, 2, 1);
	addEdge(2, 4, 0,1);
	addEdge(2, 3, 0,1);
	//addEdge(2, 3, 1);
	//addEdge(2, 4, 1);
	//addEdge(3, 4, 1);
	//show_vertex(0);
*/