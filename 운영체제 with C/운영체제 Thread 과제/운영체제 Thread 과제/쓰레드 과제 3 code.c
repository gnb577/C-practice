#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


DWORD WINAPI ThreadFunc(LPVOID n);


DWORD WINAPI ThreadFunc(LPVOID n)
{
    for (int i = 0; i < 1000000000; i++)
    {
        3 + 5 + 8 * 24;
    }
    return 0;
}

int main() {

    printf("이 프로그램은 매번 다른 난수를 생성해서 쓰레드의 wait이 있느냐 없느냐에 따라 어떤 결과 값을 나타내는지를 표현하는 프로그램입니다\n\n");
    Sleep(100);
    srand(time(NULL));
    int random = rand() % 20;

    clock_t start, finish_wait,finish_nowait;
    double duration_wait,duration_nowait;
    DWORD threadId;
    DWORD threadId1;
    

    HANDLE hThrd_wait[20];
    HANDLE hThrd_nowait[20];

    printf("이번 프로그램의 random number는 %d 입니다\n", random);
    start = clock();//현재 시간 반환

    for (int i = 0; i < random; i++) 
    {
        hThrd_wait[i] = CreateThread(NULL,  0, ThreadFunc,(LPVOID)i, 0, &threadId);
    }

    for (int i = 0; i < random; i++)
    {
        hThrd_nowait[i] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)i, 0, &threadId1);
    }

    for (int i = 0; i < random; i++)
    {
        CloseHandle(hThrd_nowait[i]);
    }

    finish_nowait = clock();
    duration_nowait = (double)(finish_nowait - start) / CLOCKS_PER_SEC;
    printf("wait없는 thread의 종료시간은 %f 초입니다\n", duration_nowait);
    
    //위를 보면 wait가 없는 no wait 쓰레드의 경우 waitformultipleobject에 영향을 받지않아 생성하면서 종료하기 때문에 짧은 시간내에 작업이 완료

    WaitForMultipleObjects(random, hThrd_wait, TRUE, INFINITE);
    for (int i = 0; i < random; i++)
    {
        CloseHandle(hThrd_wait[i]);
    }
    // 위를 보면 wait가 있는  wait 쓰레드의 경우 waitformultipleobject에 영향을 받아 
    //  쓰레드가 생성될 때마다 쓰레드 함수에서 지정한 sleep(int i=0;i<1000000;로 만들어낸)때문에 기다리기도 하고 중첩되기도하여 훨씬 많은 시간이 소모됨

    //종료
    finish_wait = clock();
    duration_wait = (double)(finish_wait - start) / CLOCKS_PER_SEC;
    printf("wait있는 thread의 종료시간은 %f 초입니다\n", duration_wait);
    return 0;
}


