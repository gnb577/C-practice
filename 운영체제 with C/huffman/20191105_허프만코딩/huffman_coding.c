#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//���������� ���������� ����
//�������� �ڵ����� 0���� �ʱ�ȭ, ���������� �����Ⱚ
//���������� stack����, ���������� heap����
//stack������ ũ�Ⱑ �۾Ƽ�
//�޸𸮸� ũ�� ����ϰ� ������ ��������,(heap ����)�� ���

int char_cnt[256];

void show_table()
{
	for (int i = 0; i < 256; i++)
	{
		unsigned char k;
		k = i;
		printf("%d-------->%d\n", i, char_cnt[i]);
	}
}

int main()
{
	FILE* f;
	char buf[1000];

	memset(char_cnt, 0, sizeof(int)*256);
	for (int i = 0; i < 256; i++)
	{
		printf("%d-------->%d\n", i, char_cnt[i]);
	}
	//fopen
	f = fopen("alice.txt","rt");
	if (f == 0)
	{
		printf("unable to open alice.txt");
		return;
	}
	while (1)
	{
		int i;
		char *temp = fgets(buf, 1000, f); // 100byte�� �аٴ�
		if (temp == 0)
		{
			break;
		}
		
		for (i = 0; i < strlen(buf); i++)
		{
			char_cnt[buf[i]]++;
		}
		printf("%s", buf);
	}
	show_table();
	//fclose
	fclose(f);
    
	return 0;
}