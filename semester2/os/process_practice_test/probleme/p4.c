//Write a C program that runs a bash command (potentially with arguments) received as a command line argument and times its execution.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("no arguments");
		exit(1);
	}
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	int pid=fork();
	if( pid == -1){
		perror("error on fork");
		exit(0);
	}
	else if( pid == 0){
	//in child
	        execvp(argv[1],argv+1);
	}
	wait(0);
	gettimeofday(&t2,NULL);
	printf("Total time = %f seconds\n", (double)(t2.tv_usec - t1.tv_usec) / 1000000 + (double) (t2.tv_sec - t1.tv_sec));
	return 0;
}
