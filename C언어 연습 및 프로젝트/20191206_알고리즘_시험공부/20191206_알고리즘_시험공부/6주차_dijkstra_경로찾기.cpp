#include<stdio.h>
#include<stdlib.h>

#define sz 4
#define sz2 5
#define sz3 8

typedef struct vertex
{
	int found; //��θ� ã�Ѵ���?
	int dist; // dist
	int prev_row;
	int prev_col;
}vertex;

