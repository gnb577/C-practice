#include <stdio.h>
#include <pthread.h>
int thread_args[3] = { 0,1,2 };
void* Thread(void* arg) // void *�� �Ծ� ������(�ּ�)�� ���� ���ϰ��� ����
{
	int i;
	for (i = 0; i < 5; i++)
		printf("thread %d : %dth iteration\n", *(int*)arg, i);
	pthread_exit(0);
}
void main(void)
{
	int i;
	pthread_t threads[3];
	for (i = 0; i < 3; i++)
	{
		printf("Thread Num %d Create!!\n", i);
		pthread_create(&threads[i], NULL, (void* (*)(void*))Thread, &thread_args[i]);
		//pthread�� ����ڴ� || Thread�Լ��� ������� ����ڴ�.
		//�켱������ ��� ���������� ���� Thread�� �������� ���ð��̴�.
	}
	pthread_exit(0);
}