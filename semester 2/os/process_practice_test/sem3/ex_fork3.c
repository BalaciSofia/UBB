
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
//singura
int main(int argc, char *argv[]){
	int pid=fork();
	if (pid == -1)
	{
		perror("fork() error:");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) //in child process
	{
		printf("In child process with pid: %d \n", getpid());
	}
	else{
		printf("In parent process with pid: %d \n", getpid());
	}
	return 0;
}
