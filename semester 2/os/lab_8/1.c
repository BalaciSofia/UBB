
int main(int argc, char *argv[])
{
	//argv[1] C -> P
	int p[2];

	if(pipe(p) == -1){
		perror("Error on pipe");
		exit(1);
	}

	int f = fork();
	
	if (f == -1){
		perror("Error on fork");
	}
	else if (f == 0){
		int size=strlen(argv[1]); 
		if( write(p[1],&size,sizeof(int)) == -1){
			perror("Error on write size from child");
		}
		if( write(p[1],argv[1],size * sizeof(char)) == -1){
			perror("Error on write string from the child");
		}
		exit(0);
	}
	else{
		char *recived;
		int size;
		if (read(p[0],&size,sizeof(int)) == -1){
			perror("");
		}
		recived=malloc(sizeof(char)*size;
		read(p[0],recived,sizeof(char) *size);
		wait(NULL);
	}
	return 0;
}
