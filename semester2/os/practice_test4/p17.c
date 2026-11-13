//Write a C program that reads a number N and creates 2 threads. One of the threads will generate an even number and will append it to an array that is passed as a parameter to the thread. The other thread will do the same, but using odd numbers. Implement a synchronization between the two threads so that they alternate in appending numbers to the array, until they reach the maximum length N.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
pthread_mutex_t mtx;
pthread_cond_t cond;
int flag=0;
int n;
int i=0;
//0-even
//1-odd

void* even(void *arg){
	int *arr=(int*)arg;
	while(1){
		pthread_mutex_lock(&mtx);
		while(flag==1){
			pthread_cond_wait(&cond,&mtx);
		}
		if(i>=n){
			flag=1;
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mtx);
			break;
		}
		int nr=rand()%(100-0+1);
		while(nr%2!=0)
			nr=rand()%(100-0+1);
		arr[i++]=nr;
		printf("even wrote %d at index %d\n", nr, i - 1);
		flag=1;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mtx);

	}
	return NULL;
}

void* odd(void *arg){
	int *arr=(int*)arg;
         while(1){
                pthread_mutex_lock(&mtx);
                while(flag==0){
                        pthread_cond_wait(&cond,&mtx);
                }
                if(i>=n){
			flag=0;
                 	pthread_cond_signal(&cond);
		 	pthread_mutex_unlock(&mtx);
                        break;
                }
                int nr=rand()%(100-0+1);
                while(nr%2==0)
                        nr=rand()%(100-0+1);
                arr[i++]=nr;
		printf("odd wrote %d at index %d\n", nr, i - 1);
		flag=0;
		pthread_cond_signal(&cond);
                pthread_mutex_unlock(&mtx);

        }
	return NULL;
}

int main(){
	printf("input n:");
	scanf("%d",&n);
	int array[n];
	srand(getpid());
	pthread_t t1,t2;
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_create(&t1,NULL,even,&array);
	pthread_create(&t2,NULL,odd,&array);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("vector:");
	for(int i=0;i<n;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);
	return 0;
}
