//20. Write a C program that takes as command line arguments 2 numbers: N and M. The program will simulate a thread race that have to pass through M checkpoints. Through each checkpoint the threads must pass one at a time (no 2 threads can be inside the same checkpoint). Each thread that enters a checkpoint will wait between 100 and 200 milliseconds (usleep(100000) makes a thread or process wait for 100 milliseconds) and will print a message indicating the thread number and the checkpoint number, then it will exit the checkpoint. Ensure that no thread will try to pass through a checkpoint until all threads have been created.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int n,m;
pthread_mutex_t *mtx;
pthread_barrier_t bar;

void* f(void *arg){
	int id=*(int*)arg;
	pthread_barrier_wait(&bar);
	for(int i=0;i < m;i++){
		pthread_mutex_lock(&mtx[i]);
		printf("Thread %d has entered checkpoint %d\n", id, i);
		int sec=rand()%(200-100+1)+100;
		usleep(sec*1000);
		pthread_mutex_unlock(&mtx[i]);
	}
	 printf("Thread %d finished\n", id);
	return NULL;
}

int main(){
	printf("enter n:");
	scanf("%d",&n);
	printf("eneter m: ");
	scanf("%d",&m);
	srand(getpid());
	pthread_barrier_init(&bar, NULL, n);
	
	mtx=malloc(sizeof(pthread_mutex_t)*m);
	for(int i=0;i<m;i++){
		pthread_mutex_init(&mtx[i],NULL);
	}

	pthread_t t[n];
	for (int i ;i < n; i++){
		pthread_create(&t[i],NULL,f,&i);
	}
	for(int i=0;i<n;i++){
		pthread_join(t[i],NULL);
	}
	 for (int i = 0; i < m; i++) {
        	pthread_mutex_destroy(&mtx[i]);
    	}
    	free(mtx);
	pthread_barrier_destroy(&bar);
	return 0;
}
