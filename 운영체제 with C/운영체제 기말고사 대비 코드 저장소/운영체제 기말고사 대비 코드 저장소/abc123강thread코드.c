#include<stdio.h>
#include<windows.h>

/* 결과 값이 할 때마다 다르게 나온다
아무것도 안나올 때도 있고 알파벳만 나올 때도, 숫자랑 같이 나올 때도 있다
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
	HANDLE hThread1, hThread2; // handle 이여서 h를 위의 arg는 pointer여서 p를 붙임 이런식으로 코딩하자
	DWORD dwThreadID1 = 0, dwThreadID2 = 1;

	int i = 1;

	hThread1 = CreateThread(NULL, 0, Thread1, (PVOID)0, 0, &dwThreadID1);
	hThread2 = CreateThread(NULL, 0, Thread2, (PVOID)0, 0, &dwThreadID2);
	//thread 생성코드 이 지점부터 3개의 쓰레드가 동시에 돌아가고 있는 것
	//createthread(보안(null),할당스택(0),시작주소,전달인자,flag(0),스레드id);

	CloseHandle(hThread1);
	CloseHandle(hThread2);

	while (i < 20)
	{
		printf("m");
		printf("m");
		printf("m");
		i++;
	}
	// 이 thread는 메인에서 생성해서 main이 끝나버리면 thread가 모두 죽음
	return;
}

