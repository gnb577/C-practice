#include<stdio.h>
#include<windows.h>

/* ��� ���� �� ������ �ٸ��� ���´�
�ƹ��͵� �ȳ��� ���� �ְ� ���ĺ��� ���� ����, ���ڶ� ���� ���� ���� �ִ�
*/
DWORD WINAPI Thread1(PVOID pArg);
DWORD WINAPI Thread2(PVOID pArg);
// Double word

DWORD WINAPI Thread1(PVOID pArg)
{
	int i = 1;
	while (i < 20)
	{
		printf("A");
		printf("B");
		printf("C");
		i++;
	}
	return 0;
}

DWORD WINAPI Thread2(PVOID pArg)
{
	int i = 1;
	while (i < 20)
	{
		printf("1");
		printf("2");
		printf("3");
		i++;
	}
	return 0;
}


int main()
{
	HANDLE hThread1, hThread2; // handle �̿��� h�� ���� arg�� pointer���� p�� ���� �̷������� �ڵ�����
	DWORD dwThreadID1 = 0, dwThreadID2 = 1;

	int i = 1;

	hThread1 = CreateThread(NULL, 0, Thread1, (PVOID)0, 0, &dwThreadID1);
	hThread2 = CreateThread(NULL, 0, Thread2, (PVOID)0, 0, &dwThreadID2);
	//thread �����ڵ� �� �������� 3���� �����尡 ���ÿ� ���ư��� �ִ� ��
	//createthread(����(null),�Ҵ罺��(0),�����ּ�,��������,flag(0),������id);

	CloseHandle(hThread1);
	CloseHandle(hThread2);

	while (i < 20)
	{
		printf("m");
		printf("m");
		printf("m");
		i++;
	}
	// �� thread�� ���ο��� �����ؼ� main�� ���������� thread�� ��� ����
	return;
}

