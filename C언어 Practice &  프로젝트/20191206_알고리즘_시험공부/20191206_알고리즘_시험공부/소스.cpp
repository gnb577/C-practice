#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SZ 100
#define ascii 256

char code[256][100];
char buf[100];
int buf_cnt[ascii];
char decode_buf[ascii] = { 0, };
char make_code[100];
//3a200b11c201$00001101#

int main()
{
	int num;
	char code_code;
	char letter;
	char number;
	int k = 0;
	scanf("%d", &num); //������ �Է� ���� -> �ʿ����
	scanf("%c", &code_code); // (���ĺ��Է�) �������� char�� ��� �Է¹��� ����
	int w = num;
	while (1)
	{
		if (code_code == '$')
		{
			break;
		}

		scanf("%c", &number); //���ĺ� �Է��� ���ڸ� char�� ���� ����
		buf_cnt[code_code] = (int)number; //���ڸ� int������ ��ȯ
		/*
		int buf_counting = 0;
		while(buf_counting != number)
		{
		   buf[k] = code_code;
		   buf_counting++;
		   k++;
		}
		*/
		char _code = code_code; //�� ���ĺ��� ����
		int i = 0;

		while (1)
		{
			num--;
			scanf("%c", &code_code);//�������ʹ� 0�Ǵ� 1�� �Է¹�������
			if (code_code == '$')
			{
				break;
			}
			if (code_code < '0' || code_code > '1')
			{
				code[_code][i] = 0; //���⼭ �ڵ� ���Ḧ �˸��� 0�� �ְ�
				//break�� �Ǹ� �̹� code_code�� ���ĺ����μ� �ۿ�
				break;
			}
			else
			{
				code[_code][i] = code_code;
				i++;
			}
		}
		//printf("%s\n", code[_code]);
	}

	int j = 0;
	int flag = 0;
	int i = 0;
	int cnt = 0;
	while (1)
	{
		scanf("%c", &number);
		if (number == '#')
		{
			break;
		}
		make_code[j] = number; //number�� �߰��ϰ�
		make_code[j + 1] = 0; //null�� ���ڶ��� ����(���ص���)
		//printf("%s\n", make_code); �ڵ尡 ��� �����Ǵ��� Ȯ��
		for (int k = 0; k < 256; k++)
		{
			//��� �ڵ� ���̺��� ������
			if (code[k][0] == 0) //���ۺ��� �ƹ��͵� ����? �� �ڵ����̺��� ����ִ�
			{ //���� ��ŵ
				continue;
			}
			flag = 0;
			i = 0;
			while (1) //�ڵ� ���̺� ���� �ִ� ���߿���
			{
				if (code[k][i] == 0) //�� �ڵ� ���̺��� ���������� �� �ǵ�
				{
					break;
				}
				if (make_code[i] == code[k][i]) //�� �ڵ�� �� �ڵ����̺���� �ڵ带 ���ڸ��� ������
				{
					flag++; //������ flag�÷���
				}
				i++;
			}

			if (i == flag) // ���� flag�� i���� ����? -> ��� ��Ұ� ����
			{
				printf("%c", k);
				for (int i = 0; i < 100; i++) // �ʱ�ȭ ���ְ�
				{
					make_code[i] = 0;
				}
				flag = 0; //
				j = -1; //j=0���� �����ؾߵǴϱ� 
				break;
			}
			//printf("%d %d\n", flag, i);
			/*
			for (int o = 0; o < j+1; o++) //���� makecode�� ���� ��ŭ
			{
			   if (make_code[o] == code[k][o])
			   {
				  flag++;
			   }
			}

			if (j+1 == flag)
			{
			   printf("%c", k);
			   for (int i = 0; i < 100; i++)
			   {
				  make_code[i] = 0;
			   }
			   //flag = 0;
			   j = -1;
			   break;
			}
			*/
		}
		j++; // ���ο� �ڵ带 �޾� ���̺��� �ٽ� Ž����
	}
	return 1;
}