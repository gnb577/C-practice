#include<stdio.h>
#include<Windows.h>

HANDLE hMutex;
int g_var;

DWORD WINAPI MyThread_1(LPVOID arg);
DWORD WINAPI MyThread_2(LPVOID arg);

int main(int argc, char* argv[])
{
	HANDLE hThread[2];
	DWORD ThreadID[2];


	hMutex = CreateMutex(NULL, FALSE, NULL); //���������� �����߾���, mutex�� Ŀ�θ�� ����ȭ���� ���, mutex�� �� ����
											//HANDLE�� ������ �� �� �ְ�, ������ ������.
	
	hThread[0] = CreateThread(NULL, 0, MyThread_1, NULL, 0, &ThreadID[0]);
	hThread[1] = CreateThread(NULL, 0, MyThread_2, NULL, 0, &ThreadID[1]);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);//���� �� ���� ��ٸ� ����

	CloseHandle(hMutex); // �ü������ mutex�� �ƴ϶� �ٸ� �͵� ���ư��ϱ�
						//�׸� �������� �ʱ� ���� �ִ��� �� ¥�ߵ�

	return 0;
	
}

DWORD WINAPI MyThread_1(LPVOID arg)
{

	for (;;)
	{
		WaitForSingleObject(hMutex, INFINITE); //entry
		g_var = 1;
		//Sleep(1);
		printf("Thread 1 : g_var = %d\n", g_var);
		ReleaseMutex(hMutex); //exit
	}
	return 0;

}

DWORD WINAPI MyThread_2(LPVOID arg)
{


	for (;;)
	{
		WaitForSingleObject(hMutex, INFINITE); //entry
		g_var = 2;
		//Sleep(1);
		printf("Thread 2 : g_var = %d\n", g_var);
		ReleaseMutex(hMutex); //exit
	}

	return 0;
}