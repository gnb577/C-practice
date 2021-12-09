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

    printf("�� ���α׷��� �Ź� �ٸ� ������ �����ؼ� �������� wait�� �ִ��� �����Ŀ� ���� � ��� ���� ��Ÿ�������� ǥ���ϴ� ���α׷��Դϴ�\n\n");
    Sleep(100);
    srand(time(NULL));
    int random = rand() % 20;

    clock_t start, finish_wait,finish_nowait;
    double duration_wait,duration_nowait;
    DWORD threadId;
    DWORD threadId1;
    

    HANDLE hThrd_wait[20];
    HANDLE hThrd_nowait[20];

    printf("�̹� ���α׷��� random number�� %d �Դϴ�\n", random);
    start = clock();//���� �ð� ��ȯ

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
    printf("wait���� thread�� ����ð��� %f ���Դϴ�\n", duration_nowait);
    
    //���� ���� wait�� ���� no wait �������� ��� waitformultipleobject�� ������ �����ʾ� �����ϸ鼭 �����ϱ� ������ ª�� �ð����� �۾��� �Ϸ�

    WaitForMultipleObjects(random, hThrd_wait, TRUE, INFINITE);
    for (int i = 0; i < random; i++)
    {
        CloseHandle(hThrd_wait[i]);
    }
    // ���� ���� wait�� �ִ�  wait �������� ��� waitformultipleobject�� ������ �޾� 
    //  �����尡 ������ ������ ������ �Լ����� ������ sleep(int i=0;i<1000000;�� ����)������ ��ٸ��⵵ �ϰ� ��ø�Ǳ⵵�Ͽ� �ξ� ���� �ð��� �Ҹ��

    //����
    finish_wait = clock();
    duration_wait = (double)(finish_wait - start) / CLOCKS_PER_SEC;
    printf("wait�ִ� thread�� ����ð��� %f ���Դϴ�\n", duration_wait);
    return 0;
}


