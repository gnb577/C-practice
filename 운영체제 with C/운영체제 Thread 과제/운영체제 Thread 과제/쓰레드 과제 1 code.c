#include<stdio.h>
#include<windows.h>

/* 
��� ���� �� ������ �ٸ��� ���´�
�ƹ��͵� �ȳ��� ���� �ְ� ���ĺ��� ���� ����, ���ڶ� ���� ���� ���� �ִ�
*/


DWORD WINAPI Thread0(PVOID pArg);
DWORD WINAPI Thread1(PVOID pArg);
DWORD WINAPI Thread2(PVOID pArg);

// Double word
int num1[20] = { 0, };
int num2[20] = { 0, };
// ���꿡 ����� ������ (�ǿ�����) �迭



DWORD WINAPI Thread0(PVOID pArg)
{
	int i = 0;
	while (i < 20)
	{
		printf("%d + %d = %d �Դϴ�.\n", num1[i], num2[i], num1[i] + num2[i]);
		i++;
		Sleep(100);
	}
	return 0;
}

//����


DWORD WINAPI Thread1(PVOID pArg)
{
	int i = 0;
	while (i < 20)
	{
		printf("%d - %d = %d �Դϴ�.\n", num1[i], num2[i], num1[i] - num2[i]);
		i++;
		Sleep(100);
	}
	return 0;
}

//�y��

DWORD WINAPI Thread2(PVOID pArg)
{
	int i = 0;
	while (i < 20)
	{
		printf("%d * %d = %d �Դϴ�.\n", num1[i], num2[i], num1[i] * num2[i]);
		i++;
		Sleep(100);
	}
	return 0;
}

//����

int main()
{
	/*

	HANDLE hThread1, hThread2,hThread3; // handle �̿��� h�� ���� arg�� pointer���� p�� ���� �̷������� �ڵ�����
	DWORD dwThreadID1 = 0, dwThreadID2 = 1, dwThreadID3 = 2;

	*/

	HANDLE hThread[3]; // handle �̿��� h�� ���� arg�� pointer���� p�� ���� �̷������� �ڵ�����
	DWORD dwThreadID[3] = { 0,1,2 };

	for (int i = 0; i < 20; i++)
	{
		num1[i] = 3 * i;
		num2[i] = 2 * i;
	}

	int i = 0;

	hThread[0] = CreateThread(NULL, 0, Thread0, (PVOID)0, 0, &dwThreadID[0]);
	hThread[1] = CreateThread(NULL, 0, Thread1, (PVOID)0, 0, &dwThreadID[1]);
	hThread[2] = CreateThread(NULL, 0, Thread2, (PVOID)0, 0, &dwThreadID[2]);
	//thread �����ڵ� �� �������� 3���� �����尡 ���ÿ� ���ư��� �ִ� ��

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);

	while (i < 20)
	{
		printf("main�� ���� �Ǿ����ϴ�\n");
		Sleep(100);
		i++;
	}

	WaitForMultipleObjects(4, hThread, 1, INFINITE); //4���� �����尡 ���� �� ���� ��ٸ�,waitforó���� �����ָ� ���� thread�� ���ο��� �����ؼ� main�� ���������� thread�� ��� ����
	

	return;
}

