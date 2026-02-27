//6. Create a C program that generates N random integers (N given at the command line). It then creates a child, sends the numbers via pipe. The child calculates the average and sends the result back.
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc ,char *argv[]){
	if (argc < 2){
		printf("not enough arguments");
		exit(1);
	}
	int n=atoi(argv[1]);
	int p2c[2];
	int c2p[2];
	int res =pipe(p2c);
	int res2=pipe(c2p);
	if (res == -1){
		perror("pipe error");
		exit(1);
	}
	if (res2 == -1){
		perror("pipe error");
		exit(1);
	}
	int pid=fork();
	if (pid == -1){
		perror("error on fork()");
		exit(1);
	}
	else if (pid == 0){
		close(p2c[1]);
		close(c2p[0]);
		int sum=0;
		double average;
		int nr;
		for (int i=0;i<n;i++)
		{
			read(p2c[0],&nr,sizeof(int));
			sum=sum+nr;
		}
		average=(double)sum/n;
		close(p2c[0]);
		write(c2p[1],&average,sizeof(double));
		close(c2p[1]);
		exit(0);

	}
	close(p2c[0]);
	close(c2p[1]);
	srandom(getpid());
	for (int i=0 ;i < n;i++){
		int num=random()%100;
		printf("Parent generated %d\n",num);
		write(p2c[1],&num,sizeof(int));
	}
	wait(0);
	double rez;
	read(c2p[0],&rez,sizeof(double));
	printf("rezult=%.2f",rez);
	close(p2c[1]);
}
