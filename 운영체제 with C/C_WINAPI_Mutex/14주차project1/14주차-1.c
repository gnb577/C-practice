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


	hMutex = CreateMutex(NULL, FALSE, NULL); //전역변수로 생성했었음, mutex는 커널모드 동기화에서 사용, mutex는 곧 권한
											//HANDLE이 있으면 쓸 수 있고, 없으면 못쓴다.
	
	hThread[0] = CreateThread(NULL, 0, MyThread_1, NULL, 0, &ThreadID[0]);
	hThread[1] = CreateThread(NULL, 0, MyThread_2, NULL, 0, &ThreadID[1]);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);//끝날 때 까지 기다릴 거임

	CloseHandle(hMutex); // 운영체제에서 mutex뿐 아니라 다른 것도 돌아가니까
						//그를 방해하지 않기 위해 최대한 잘 짜야됨

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