#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


DWORD WINAPI Thread1(PVOID pArg);
DWORD WINAPI Thread2(PVOID pArg);

DWORD WINAPI Thread1(PVOID pArg)
{
    int i = 1;

    for (i = 1; i <= 1000; i++)
    {
        int random_number = rand() % 1000 + 1;
        printf("%d번째 숫자는 %d\n\n", i, random_number);
    }
    Sleep(50);
    return 0;
}

DWORD WINAPI Thread2(PVOID pArg)
{
    int i = 1;


    for (i = 1; i <= 1000; i++)
    {

        int random_char = rand() % 26 + 65;
        printf("%d번째 문자는 %c\n\n", i, random_char);

    }
    Sleep(50);

    return 0;
}

int main()
{
    HANDLE hThread1, hThread2; // handle 이여서 h를 위의 arg는 pointer여서 p를 붙임 이런식으로 코딩하자
    srand(time(NULL));


    DWORD dwThreadID1 = 0, dwThreadID2 = 1;
    hThread1 = CreateThread(NULL, 0, Thread1, (PVOID)0, 0, &dwThreadID1);
    hThread2 = CreateThread(NULL, 0, Thread2, (PVOID)0, 0, &dwThreadID2);


    Sleep(5000);
    return 0;
}