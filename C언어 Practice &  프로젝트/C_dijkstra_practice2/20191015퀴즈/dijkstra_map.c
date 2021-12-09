#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define sz 5


// ����ϴ� ���̺��� �� ��
typedef struct dijkstra_table_item
{
	int found;
	int dist;
	int prev_row;
	int prev_col;
}node;

typedef struct coord
{
	int row;
	int col;

}coord;


node dtable[sz][sz];

void initdtable()
{
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			dtable[i][j].found = 0;
			dtable[i][j].dist = 2100000000;
			dtable[i][j].prev_row = -1;
			dtable[i][j].prev_col = -1;
		}
	}
}

char map[5][5] =
{
	{'.','.','.','.','.' },
	{'.','#','#','#','.' },
	{'.','.','#','.','.' },
	{'.','#','#','.','#' },
	{'.','.','#','.','.' }
};

//���� ��� �Լ�
void dispmap()
{
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
}


// (r,c)�� �̿� , (n_r,n_c)�ε� 
// ��¥ �̿����� �˻�
// �� �̿����� (r,c)�� ���İ��� �� ������ �˻�
void checkneighbor(int r, int c, int n_r, int n_c)
{
	//���� ���� ��ǥ�̹Ƿ� ����
	if (n_r < 0 || n_r > sz || n_c < 0 || n_c > sz)
	{
		return;
	}
	
	// ���� �������� ����
	if (map[n_r][n_c] == '#')
	{
		return;
	}

	if (dtable[n_r][n_c].dist > (dtable[r][c].dist + 1))
	{
		dtable[n_r][n_c].dist = (dtable[r][c].dist + 1);
			dtable[n_r][n_c].found = 1;
			dtable[n_r][n_c].prev_row = r;
			dtable[n_r][n_c].prev_col = c;
	}
}

// (r,c) ��ġ�� �̿��鿡 ���� �Ÿ� ���� ������Ʈ
void updateneightbors(int r, int c)
{
	checkneighbor(r, c, r - 1, c);
	checkneighbor(r, c, r + 1, c);
	checkneighbor(r, c, r, c - 1);
	checkneighbor(r, c, r ,c + 1);
}


coord findsmallestvertex()
{
	int small_dist = 210000000;
	coord sm_coord;
	int i, j;

	sm_coord.row = -1;
	sm_coord.col = -1;

	for (i = 0; i < sz; i++)
	{
		for (i = 0; j < sz; j++)
		{
			if (small_dist > dtable[i][j].dist  && dtable[i][j].found ==0)
			{
				small_dist = dtable[i][j].dist;
				sm_coord.row=i;
				sm_coord.col = j;
			}
		}
	}
	return sm_coord;
}

int main()
{

	// ��� ��ġ
	int start_row = 2;
	int start_col = 1;


	// ���� ��ġ
	int end_row = 4;
	int end_col = 4;

	int tr, tc; // temp_row, temp_col
	tr = end_row;
	tc = end_col;

	// ������ġ�� ���ؼ� �ִ� ��� Ȯ��!
	dtable[start_row][start_col].found = 1;
	dtable[start_row][start_col].dist = 0;


	// dijkstra�˰��� ����

	// start_row, start_col���� �� �� �ִ� vertex�� ������Ʈ (������ �� �̿��鸸 ������Ʈ�� �����ϴ�)

	updateneighbors(start_row, start_col);
	
	// ���ݱ��� �ִ� ��ΰ� �������� ���� vertex�߿���
	// �ּ� �Ÿ��� ���� vertex�� ����

	while (1)
	{
		coord smallest = findsmallestvertex();
		if (smallest.row == -1 && smallest.col == -1) // ��� �ִ� ��θ� Ȯ������ ���
		{
			break;
		}
		dtable[smallest.row][smallest.col].found = 1;
		updateneighbors(smallest.row, smallest.col);
	}

	while (1)
	{
		int temp_r, temp_c;
		map[tr][tc] = '$';

		temp_r = dtable[tr][tc].prev_row;
		temp_c = dtable[tr][tc].prev_col;

		tr = temp_r;
		tc = temp_c; 
		
		if (tr == -1 && tc == -1)
		{
			break;
		}

	dispmap();
	return 0;
}