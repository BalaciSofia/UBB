#include <thread.h>
#include <stdio.h>
#include <stdlib.h>

FILE *f;
int lines,chars,words;

void* funct(void *arg){
	while(1){
		line=getline()
	}
	return NULL;
}

int main(int argc, char * argv[]){

	if(argc!=3){
		printf("not enough arguments")
		return 0;
	}
	int N=atoi(argv[2]);
	char filename=argv[1];
	f=fopen(filename,"r");
	pthread_t th[N];
	pthread_mutex_t m1;
	pthread_mutex_t m2;
	pthread_mutex_init(&m1,NULL);
	pthread_mutex_init(&m2,NULL);
	for(int i=0;i<N;i++){
		pthread_create(&th[i],NULL,funct,&i);
	}
	for(int i=0;i<N;i++){
		pthread_join(th[i],NULL);
	}
	return 0;
}
