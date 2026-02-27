//18. Create a C program that converts all lowecase letters from the command line arguments to uppercase letters and prints the result. Use a thread for each given argument.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char *cuv
}data;
void *functie(void *arg){
	data d=*((data*)arg);
	for (int i=0;i<strlen(d.cuv);i++){
		if(d.cuv[i]<='z' && d.cuv[i]>='a')
			d.cuv[i]-=32;
	}
	return NULL;
}
int main(int argc, char * argv[]){
	int n=argc-1;
	pthread_t t[n];
	data d[n];
	for (int i=0;i<n;i++){
		d[i].cuv=malloc(strlen(argv[i+1])+1);
		strcpy(d[i].cuv,argv[i+1]);
		pthread_create(&t[i],NULL,functie,(void *)&d[i]);		
	}
	for(int i=0;i<n ;i++)
		pthread_join(t[i],NULL);
	for(int i=0;i<n;i++){
		printf("%s ",d[i].cuv);
		free(d[i].cuv);
	}
	printf("\n");
	return 0;
}
