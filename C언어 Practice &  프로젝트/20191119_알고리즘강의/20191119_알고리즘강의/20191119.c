#include<stdio.h>

int main()
{
	char toWrite = 0;

	FILE* f;
	//11110000�� 8byte�� ��
	//f = fopen("data", "wt");
	//fprintf(f, "11110000");
	//fclose(f);

	//binary mode
	//11110000�� 1byte�� ��
	f = fopen("data", "wb");
	toWrite = 0xf0;

	//text�� fprint , binarty�� fwrite
	//toWrite ���ۿ���(�ּ�)
	//1����Ʈ ¥����
	//1����
	//����f������
	//� �ָ�,�����Ʈ��,���,��� ���Ͽ���
	fwrite(&toWrite, 1, 1, f);
	fclose(f);

}