//Write a C program that receives integers as command line argument. The program will keep a frequency vector for all digits. The program will create a thread for each argument that counts the number of occurences of each digit and adds the result to the frequency vector. Use efficient synchronization.
//
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
int frequency[10];
pthread_mutex_t mtx;

void * functie(void *arg){
	int nr=*(int*)arg;
	int f[10];
	for(int i=0;i<=9;i++)
		f[i]=0;
	while(nr!=0){
		f[nr%10]++;
		nr=nr/10;
	}
	pthread_mutex_lock(&mtx);
	for(int i=0;i<=9;i++){
		frequency[i]+=f[i];
	}
	pthread_mutex_unlock(&mtx);
	return NULL;
}
int main(int argc, char * argv[]){
	int n=argc-1;
	pthread_t t[n];
	pthread_mutex_init(&mtx,NULL);
	int val[n];
	for(int i=0; i < n;i++){
		val[i]=atoi(argv[i+1]);
		pthread_create(&t[i],NULL,functie,&val[i]);
	}
	for(int i=0;i<n;i++){
		pthread_join(t[i],NULL);
	}
	printf("vector:");
	for (int i = 0;i <= 9;i++){
		printf("%d ",frequency[i]);
	}
	printf("\n");
	pthread_mutex_destroy(&mtx);
	return 0;
}
