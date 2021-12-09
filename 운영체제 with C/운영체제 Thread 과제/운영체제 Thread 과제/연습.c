#include <stdio.h>
#include <Windows.h>  

DWORD WINAPI Thread1(PVOID pArg);
DWORD WINAPI Thread2(PVOID pArg);
DWORD WINAPI Thread3(PVOID pArg);



DWORD WINAPI Thread1(PVOID pArg) {
    int i = 1;
    int v;
    while (1)
    {
        scanf("%d", &v);
        printf("%d thread 1\n", v);
        for (volatile int s = 0; s < 1000000000; s++);
    }
 
    return 0;
}

DWORD WINAPI Thread2(PVOID pArg) {
    int i = 1;
    int v;
    while (1)
    {
        scanf("%d", &v);
        printf("%d thread 2\n", v);
        for (volatile int s = 0; s < 1000000000; s++);
    }
    
    return 0;
}
DWORD WINAPI Thread3(PVOID pArg) {
    int i = 1;
    int v;
    while (1)
    {
        scanf("%d", &v);
        printf("%d thread 3\n", v);
        for (volatile int s = 0; s < 1000000000; s++);

    }
    return 0;
}

int main() {
    HANDLE hThread1, hThread2, hThread3;
    DWORD dwThreadID1 = 0, dwThreadID2 = 1, dwThreadID3 = 2;
    int i = 1;   int v;


    //Thread¸¦ ¸¸µê
    hThread1 = CreateThread(NULL, 0, Thread1, (PVOID)0, 0, &dwThreadID1);
    CloseHandle(hThread1);

    hThread2 = CreateThread(NULL, 0, Thread2, (PVOID)0, 0, &dwThreadID2);
    CloseHandle(hThread2);

    hThread3 = CreateThread(NULL, 0, Thread3, (PVOID)0, 0, &dwThreadID3);
    CloseHandle(hThread3);

    while (1) {

        scanf("%d", &v);
        printf("%d main\n", v);
        for (volatile int s = 0; s < 1000000000; s++);

    }
    return;
}