#include<stdio.h>
#include<string.h>
#include<math.h>

#define sz 4

//ü����
int chess_board[sz][sz];

//�߰��� �ַ����� ����
int solutioncnt = 0;

//ü������ 0���� �ʱ�ȭ
void initboard()
{

	memset(chess_board, 0, sizeof(int) * sz * sz);
	//���� �ǹ̷� �ʱ�ȭ
#if 0
	int i, j;
	for (i = 0; i < sz; i++)
	{
		for (j = 0; j < sz; j++)
		{
			chess_board[i][j] = 0;
		}
	}
#endif
}


//��ȯ�� 1:��ǥ(_r,_c)�� ���� �� �ִ�
//		 0:�ȵ�
int isok(int _r, int _c)
{
	int i, j;

	// ���� ������ �˻�
	for (i = 0; i < _r; i++)
	{
		if (chess_board[i][_c] != 0)
		{
			//���� ���� �˻��ؼ� ���� �ִٸ� ������ ����
			return 0;
		}
	}

	// ���� ������ �˻�
	for (i = 0; i < _c; i++)
	{
		if (chess_board[_r][i] != 0)
		{
			//���� ���� �˻��ؼ� ���� �ִٸ� ������ ����
			return 0;
		}
	}

	// �밢�� ������ �˻� (���� �밢��)
	for (i = 0; i < _r; i++)
	{
		for (j = 0; j < sz; j++)
		{
			if ((abs(i - _r) == abs(j - _c)) && chess_board[i][j] != 0) // ���� ���� ���̰� �����ϸ鼭  �ش��ڸ��� ���� ���� ���
			{
				return 0;
			}
		}
	}

	return 1;

}

//�� r�� 0���� �ʱ�ȭ
void clearRow(int _r)
{
	//int i;

	memset(&chess_board[_r][0], 0, sizeof(int) * sz);

#if 0
	for (i = 0; i < sz; i++)
	{
		chess_board[_r][i] = 0;
	}
#endif

}

void printsolution()
{
	solutioncnt++;
	printf("-------solution # %d -------\n", solutioncnt);
	int i, j;

	for (i = 0; i < sz; i++)
	{
		for (j = 0; j < sz; j++)
		{
			printf("%d ", chess_board[i][j]);
		}
		printf("\n");
	}
}
//�� _r�� queen�� ���� �� �ִ� ��ġ�� ã�´�

void checknext(int _r)
{
	int i;

	//�� _r�� ��� ���� ���ؼ� ��� ���� ���ؼ�
	for (i = 0; i < sz; i++)
	{
		clearRow(_r);
		//��ǥ(_r,i)�� queen�� ����
		if (isok(_r, i) == 1)
		{
			chess_board[_r][i] = 1;
			if (_r == sz - 1)
			{
				printsolution();// (chess_board���� ���� ��)
			}
			else
			{
				checknext(_r+1);
			}
		}
	}

}

int main()
{

	int c; //���� ��Ÿ���� ����

	initboard();

	for (c = 0; c < sz; c++)
	{
		clearRow(0);
		//(0,0) (0,1) (0,2) (0,3) ������ �˻�
		if (isok(0, c) == 1)
		{
			chess_board[0][c] = 1;
			checknext(1);
		}
	}
	return 0;
}