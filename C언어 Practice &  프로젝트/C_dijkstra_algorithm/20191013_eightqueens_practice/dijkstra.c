#include <stdio.h>

#define SZ 5

// dijkstra 알고리즘을 수행할 때
// 사용하는 테이블의 한 줄
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

// dijkstra 알고리즘에서 사용하는 테이블
struct dijkstra_table_item dtable[SZ][SZ];


char map[5][5] = {
	{'.','.','.','.','.'},
	{'.','#','#','#','.'},
	{'.','.','#','.','.'},
	{'.','#','#','.','#'},
	{'.','.','#','.','.'}
};

// Dijksta 테이블을 초기화 한다.
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


// 지도를 출력해서 보여주는 함수
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
  (r,c)의 이웃이 (n_r, n_c)인데
  [1] 진짜 이웃인지 검사
  [2] 그 이웃까지 (r,c)를 거쳐가면 더 빠른지 검사
*/
void checkNeighbor(int r, int c, int n_r, int n_c)
{
	// 지도 밖의 좌표이므로 생략
	if (n_r < 0 || n_r >= SZ || n_c < 0 || n_c >= SZ)
	{
		return;
	}
	// 막힌 공간인지 보자..
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
   (r,c) 위치의 이웃들에 대한 거리 정보 업데이트
*/
void updateNeighbors(int r, int c)
{
	checkNeighbor(r, c, r - 1, c); // 윗동네,
	checkNeighbor(r, c, r + 1, c);  // 아랫동네
	checkNeighbor(r, c, r, c - 1); // 왼동네
	checkNeighbor(r, c, r, c + 1); // 오른동네

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
	// 출발위치
	int start_row = 2;
	int start_col = 1;

	// 도착위치
	int end_row = 4;
	int end_col = 4;

	int tr, tc;  // temp row, temp col


	initDtable();

	// 시작위치에 대해서 최단경로 확보!!!
	dtable[start_row][start_col].dist = 0;
	dtable[start_row][start_col].found = 1;

	// dijkstra 알고리즘 수행

	// (start_row, start_col)에서 갈 수 있는
	// vertex들에 대해서 업데이트
	updateNeighbors(start_row, start_col);

	// 지금까지 최단 경로가 결정되지 않은 vertex 중에서
	// 최소 거리를 가진 vertex를 선택
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

	// dtable에서 (start_row, start_col)
	// --> (end_row, end_col) 가는 경로를 지도에 표시

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




