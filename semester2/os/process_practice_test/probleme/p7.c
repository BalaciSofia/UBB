//Write a C program that creates two child processes. The two child processes will alternate sending random integers between 1 and 10 (inclusively) to one another until one of them sends the number 10. Print messages as the numbers are sent.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int c1tc2[2],c2tc1[2];
	pipe(c1tc2);
	pipe(c2tc1);
	int f1=fork();
	if(f1 == -1)
	{
		perror("error on fork");
		exit(1);
	}
	if(f1 == 0)
	{
		//c1
		close(c2tc1[1]);
		close(c1tc2[0]);
		int num;
		srandom(getpid());
		read(c2tc1[0],&num,sizeof(int));
		printf("child 1 read: %d \n",num);
		while(num!=10){
			num=random()%10+1;
			write(c1tc2[1],&num,sizeof(int));
			if (num == 10)
				break;
			read(c2tc1[0],&num,sizeof(int));
			printf("child 1 read: %d \n",num);
		}
		close(c2tc1[0]);
		close(c1tc2[1]);
		exit(0);
		
	}
	int f2=fork();
	 if(f2 == -1)
        {
                perror("error on fork");
                exit(1);
        }
        if(f2 == 0)
        {
                //c2
                close(c2tc1[0]);
                close(c1tc2[1]);
                int num=0;
		srandom(getpid());
		while(num!=10){
			num=random()%10+1;
			write(c2tc1[1],&num,sizeof(int));
			if (num==10)
				break;
			 read(c1tc2[0],&num,sizeof(int));
			 printf("child 2 read %d \n",num);
		}
		close(c2tc1[1]);
		close(c1tc2[0]);
		exit(0);
        }
	wait(0);
	wait(0);
	return 0;

}

