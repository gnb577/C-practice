#include<stdio.h>
#include<windows.h>

/* 
결과 값이 할 때마다 다르게 나온다
아무것도 안나올 때도 있고 알파벳만 나올 때도, 숫자랑 같이 나올 때도 있다
*/


DWORD WINAPI Thread0(PVOID pArg);
DWORD WINAPI Thread1(PVOID pArg);
DWORD WINAPI Thread2(PVOID pArg);

// Double word
int num1[20] = { 0, };
int num2[20] = { 0, };
// 연산에 사용할 데이터 (피연산자) 배열



DWORD WINAPI Thread0(PVOID pArg)
{
	int i = 0;
	while (i < 20)
	{
		printf("%d + %d = %d 입니다.\n", num1[i], num2[i], num1[i] + num2[i]);
		i++;
		Sleep(100);
	}
	return 0;
}

//덧셈


DWORD WINAPI Thread1(PVOID pArg)
{
	int i = 0;
	while (i < 20)
	{
		printf("%d - %d = %d 입니다.\n", num1[i], num2[i], num1[i] - num2[i]);
		i++;
		Sleep(100);
	}
	return 0;
}

//뻴셈

DWORD WINAPI Thread2(PVOID pArg)
{
	int i = 0;
	while (i < 20)
	{
		printf("%d * %d = %d 입니다.\n", num1[i], num2[i], num1[i] * num2[i]);
		i++;
		Sleep(100);
	}
	return 0;
}

//곱셉

int main()
{
	/*

	HANDLE hThread1, hThread2,hThread3; // handle 이여서 h를 위의 arg는 pointer여서 p를 붙임 이런식으로 코딩하자
	DWORD dwThreadID1 = 0, dwThreadID2 = 1, dwThreadID3 = 2;

	*/

	HANDLE hThread[3]; // handle 이여서 h를 위의 arg는 pointer여서 p를 붙임 이런식으로 코딩하자
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
	//thread 생성코드 이 지점부터 3개의 쓰레드가 동시에 돌아가고 있는 것

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);

	while (i < 20)
	{
		printf("main이 실행 되었습니다\n");
		Sleep(100);
		i++;
	}

	WaitForMultipleObjects(4, hThread, 1, INFINITE); //4개의 쓰레드가 끝날 때 까지 기다림,waitfor처리를 안해주면 위의 thread는 메인에서 생성해서 main이 끝나버리면 thread가 모두 죽음
	

	return;
}

