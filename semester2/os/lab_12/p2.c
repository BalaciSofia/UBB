#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int array[6];
pthread_mutex_t mtx;
pthread_cond_t cond;
int flag=0;
//0-generate
//1-verify if sorted
//2-sorted=>terminate
void* f1(){
	while(1){
	pthread_mutex_lock(&mtx);
	if(flag==2){
		pthread_mutex_unlock(&mtx);
		break;
	}
	while(flag!=0 && flag!=2)
		pthread_cond_wait(&cond,&mtx);
	if(flag==2){
		pthread_mutex_unlock(&mtx);
		break;
	}
	//create array
	for(int i=0;i < 5;i++){
		array[i]=rand()%(1000-0+1);
		printf("%4d", array[i]);
	}
	printf("\n");
	flag=1;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

void* f2(){
	while(1){
	pthread_mutex_lock(&mtx);
	while(flag!=1)
		pthread_cond_wait(&cond,&mtx);
	//check if asscending
	flag=2;
	for (int i=0;i < 4;i++){
		if(array[i]>array[i+1]){
			flag=0;
			break;
		}
	}
	if(flag==2){
		//signal that its sorted to terminate
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mtx);
		break;
	}
	//signal that is not sorted
	pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
	}
	return NULL;
}
int main(){
	srand(getpid());
	pthread_t t1,t2;
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&cond,NULL);
	flag=0;
	pthread_create(&t1,NULL,f1,NULL);
	pthread_create(&t2,NULL,f2,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);
	return 0;
}
