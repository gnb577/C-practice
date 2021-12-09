#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
using namespace std;
DWORD __stdcall ThreadFunc(LPVOID Param);
typedef struct stThreadParam
{
	int id;
	int sleeptime;
} ThreadParam;
int main()
{
	HANDLE	hThread[4];
	DWORD	ThreadID[4];
	ThreadParam tp[4];
	for (int i = 0; i < 4; i++)
	{
		tp[i].id = i;
		tp[i].sleeptime = i * 200;
		hThread[i] = CreateThread(NULL, 0, ThreadFunc, &tp[i], 0, &ThreadID[i]);
	}
	WaitForMultipleObjects(4, hThread, TRUE, INFINITE);
	_getch();
	return 0;
}
DWORD WINAPI ThreadFunc(LPVOID Param)
{
	ThreadParam* tp = (ThreadParam*)Param;
	for (int i = 0; i < 10; i++)
	{
		cout << endl;
		cout << "Thread" << tp->id << ":" << i << endl;
		Sleep(tp->sleeptime); //스케쥴링 하는 역할을 함. 나는 쉴테니 다른 친구를 실행해
	}
	return 0;
}