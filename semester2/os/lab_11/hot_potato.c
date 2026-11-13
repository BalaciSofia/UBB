
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int potato;
pthread_mutex_t mtx;


void* f(void *arg){
	int id= *(int*)arg;
	free(arg);
	while(1){
	pthread_mutex_lock(&mtx);
	if(potato<0){
		pthread_mutex_unlock(&mtx);
		break;
	}
	int subtract=rand()%(100-10+1)+10;
	potato=potato-subtract;
	        printf("Thread with id %d has subtracted %d from %d\n", id, subtract,potato );
	if(potato<0) {
		printf("Potato exploded in thread w id: %d \n",id);
		pthread_mutex_unlock(&mtx);
		break;
	}
	pthread_mutex_unlock(&mtx);
	 int time=rand()%(200-100+1)+100;
        usleep(time*1000);
	}
	printf("Thread %d exiting.\n", id);
	return NULL;
}


int main(int argc , char *argv[]){
	if (argc!=2){
		printf("please provide one argument\n");
		return 0;
	}
	int N=atoi(argv[1]);
	srand(getpid());
    	potato = rand() % (10000-1000+1) + 1000;
	printf("Main has generated %d\n", potato);
	pthread_t tid[N];
	pthread_mutex_init(&mtx,NULL);
	for (int i=0;i < N;i++){
		int *arg = malloc(sizeof(int));
        *arg = i;
		pthread_create(&tid[i],NULL,f,arg);
	}
	for (int i=0;i<N;i++){
		pthread_join(tid[i],NULL);
	}
	pthread_mutex_destroy(&mtx);
	return 0;
}

