#include <stdio.h>
#include <pthread.h>
int thread_args[3] = { 0,1,2 };
void* Thread(void* arg) // void *는 규약 포인터(주소)만 가짐 리턴값은 없음
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
		//pthread를 만들겠다 || Thread함수를 쓰레드로 만들겠다.
		//우선순위를 어떻게 가지는지에 따라 Thread가 섞여져서 나올것이다.
	}
	pthread_exit(0);
}