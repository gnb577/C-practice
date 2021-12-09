#include <stdio.h>
#include <Windows.h>  

DWORD WINAPI Thread0(PVOID pArg);
DWORD WINAPI Thread1(PVOID pArg);
DWORD WINAPI Thread2(PVOID pArg);


int flag = 10;
int count = 0;


DWORD WINAPI Thread0(PVOID pArg) {
    int data;
    while (1)
    {
        // count++; 
        scanf("%d", &data);
        printf("%d thread0\n", data);
        printf("현재 count = %d\n", count);
        count++;
        for (int i = 0; i < 1000000000; i++);
        //count++;
    }

    return 0;
}

DWORD WINAPI Thread1(PVOID pArg) {
    int data;
    while (1)
    {

        // count++;
        scanf("%d", &data);
        printf("%d thread1\n", data);
        printf("현재 count = %d\n", count);
        count++;
        for (int i = 0; i < 1000000000; i++);
        // count++;

    }

    return 0;
}
DWORD WINAPI Thread2(PVOID pArg) {
    int data;
    while (1)
    {

        // count++;
        scanf("%d", &data);
        printf("%d thread2\n", data);
        printf("현재 count = %d\n", count);
        count++;
        for (int i = 0; i < 1000000000; i++);
        // count++;

    }
}

/*

 1. count가 위에 있는 경우
 시작부터 쓰레드 갯수만큼이 count되어 나옴

 2. count가 중간에 있는 경우
 의도한대로 sequence하게 하나씩 출력

 3. count가 delay뒤(끝)에 있는 경우
 delay에 의해 시간이 뒤죽박죽 되어 count도 이상하게 나오는 경향이 있음
 (또한 지연시간으로 인해 count가 10이 되자마자 끝나지 않는 경우도 존재)

*/

int main() {
    printf("이 프로그램은 thread가 입력을 받는 thread일 경우\n");
    printf("어떻게 돌아가는 지 보여주는 프로그램이다.\n");
    printf("각 thread의 주석처리한 count에 따라 다른 결과를 보인다.\n\n");
    HANDLE hThread[3]; // handle 이여서 h를 위의 arg는 pointer여서 p를 붙임 이런식으로 코딩하자
    DWORD dwThreadID[3] = { 0,1,2 };

    hThread[0] = CreateThread(NULL, 0, Thread0, (PVOID)0, 0, &dwThreadID[0]);
    hThread[1] = CreateThread(NULL, 0, Thread1, (PVOID)0, 0, &dwThreadID[1]);
    hThread[2] = CreateThread(NULL, 0, Thread2, (PVOID)0, 0, &dwThreadID[2]);

    int data;

    while (1) {
        if (flag <= count)
            break;
        // count++;
        scanf("%d", &data);
        printf("%d main\n", data);
        printf("현재 count = %d\n", count);
        count++;
        for (volatile int i = 0; i < 1000000000; i++);
        // count++;

    }
    return;
}