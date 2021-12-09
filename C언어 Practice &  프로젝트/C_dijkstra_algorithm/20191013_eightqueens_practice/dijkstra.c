#include <stdio.h>

#define SZ 5

// dijkstra �˰����� ������ ��
// ����ϴ� ���̺��� �� ��
struct dijkstra_table_item
{
	int found;
	int dist;
	int prev_row;
	int prev_col;
};

struct coord
{
	int row;
	int col;
};

// dijkstra �˰��򿡼� ����ϴ� ���̺�
struct dijkstra_table_item dtable[SZ][SZ];


char map[5][5] = {
	{'.','.','.','.','.'},
	{'.','#','#','#','.'},
	{'.','.','#','.','.'},
	{'.','#','#','.','#'},
	{'.','.','#','.','.'}
};

// Dijksta ���̺��� �ʱ�ȭ �Ѵ�.
void initDtable(void)
{
	int i, j;
	for (i = 0; i < SZ; i++)
	{
		for (j = 0; j < SZ; j++)
		{
			dtable[i][j].found = 0;
			dtable[i][j].dist = 2100000000;
			dtable[i][j].prev_row = -1;
			dtable[i][j].prev_col = -1;
		}
	}
}


// ������ ����ؼ� �����ִ� �Լ�
void dispMap(void)
{
	int i, j;
	for (i = 0; i < SZ; i++)
	{
		for (j = 0; j < SZ; j++)
		{
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
}

/*
  (r,c)�� �̿��� (n_r, n_c)�ε�
  [1] ��¥ �̿����� �˻�
  [2] �� �̿����� (r,c)�� ���İ��� �� ������ �˻�
*/
void checkNeighbor(int r, int c, int n_r, int n_c)
{
	// ���� ���� ��ǥ�̹Ƿ� ����
	if (n_r < 0 || n_r >= SZ || n_c < 0 || n_c >= SZ)
	{
		return;
	}
	// ���� �������� ����..
	if (map[n_r][n_c] == '#')
	{
		return;
	}
	if (dtable[n_r][n_c].dist > (dtable[r][c].dist + 1))
	{
		dtable[n_r][n_c].dist = dtable[r][c].dist + 1;
		dtable[n_r][n_c].prev_row = r;
		dtable[n_r][n_c].prev_col = c;
	}
}


/*
   (r,c) ��ġ�� �̿��鿡 ���� �Ÿ� ���� ������Ʈ
*/
void updateNeighbors(int r, int c)
{
	checkNeighbor(r, c, r - 1, c); // ������,
	checkNeighbor(r, c, r + 1, c);  // �Ʒ�����
	checkNeighbor(r, c, r, c - 1); // �޵���
	checkNeighbor(r, c, r, c + 1); // ��������

}

struct coord findSmallestVertex(void)
{
	int sm_dist = 2100000000;
	struct coord sm_coord;
	int i, j;

	sm_coord.row = -1;
	sm_coord.col = -1;

	for (i = 0; i < SZ; i++)
	{
		for (j = 0; j < SZ; j++)
		{
			if (dtable[i][j].found == 0 &&
				dtable[i][j].dist < sm_dist)
			{
				sm_dist = dtable[i][j].dist;
				sm_coord.row = i;
				sm_coord.col = j;
			}
		}
	}
	return sm_coord;
}






int main(void)
{
	// �����ġ
	int start_row = 2;
	int start_col = 1;

	// ������ġ
	int end_row = 4;
	int end_col = 4;

	int tr, tc;  // temp row, temp col


	initDtable();

	// ������ġ�� ���ؼ� �ִܰ�� Ȯ��!!!
	dtable[start_row][start_col].dist = 0;
	dtable[start_row][start_col].found = 1;

	// dijkstra �˰��� ����

	// (start_row, start_col)���� �� �� �ִ�
	// vertex�鿡 ���ؼ� ������Ʈ
	updateNeighbors(start_row, start_col);

	// ���ݱ��� �ִ� ��ΰ� �������� ���� vertex �߿���
	// �ּ� �Ÿ��� ���� vertex�� ����
	while (1)
	{
		struct coord smallest = findSmallestVertex();
		if (smallest.row == -1 && smallest.col == -1)
		{
			break;
		}
		dtable[smallest.row][smallest.col].found = 1;
		updateNeighbors(smallest.row, smallest.col);
	}

	// dtable���� (start_row, start_col)
	// --> (end_row, end_col) ���� ��θ� ������ ǥ��

	tr = end_row;
	tc = end_col;

	while (1)
	{
		int _temp_r, _temp_c;
		map[tr][tc] = '$';

		_temp_r = dtable[tr][tc].prev_row;
		_temp_c = dtable[tr][tc].prev_col;

		tr = _temp_r;
		tc = _temp_c;

		if (tr == -1 && tc == -1)
		{
			break;
		}
	}


	dispMap();
	return 0;
}




