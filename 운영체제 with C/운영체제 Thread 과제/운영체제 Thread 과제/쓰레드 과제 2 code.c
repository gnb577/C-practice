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
        printf("���� count = %d\n", count);
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
        printf("���� count = %d\n", count);
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
        printf("���� count = %d\n", count);
        count++;
        for (int i = 0; i < 1000000000; i++);
        // count++;

    }
}

/*

 1. count�� ���� �ִ� ���
 ���ۺ��� ������ ������ŭ�� count�Ǿ� ����

 2. count�� �߰��� �ִ� ���
 �ǵ��Ѵ�� sequence�ϰ� �ϳ��� ���

 3. count�� delay��(��)�� �ִ� ���
 delay�� ���� �ð��� ���׹��� �Ǿ� count�� �̻��ϰ� ������ ������ ����
 (���� �����ð����� ���� count�� 10�� ���ڸ��� ������ �ʴ� ��쵵 ����)

*/

int main() {
    printf("�� ���α׷��� thread�� �Է��� �޴� thread�� ���\n");
    printf("��� ���ư��� �� �����ִ� ���α׷��̴�.\n");
    printf("�� thread�� �ּ�ó���� count�� ���� �ٸ� ����� ���δ�.\n\n");
    HANDLE hThread[3]; // handle �̿��� h�� ���� arg�� pointer���� p�� ���� �̷������� �ڵ�����
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
        printf("���� count = %d\n", count);
        count++;
        for (volatile int i = 0; i < 1000000000; i++);
        // count++;

    }
    return;
}