
#include <pthread.h>                                           
#include <stdlib.h>                                            
#include <stdio.h>                                             
#include <unistd.h>                                            
int potato;                                                    
pthread_mutex_t mtx;                            
pthread_cond_t cond;
int flag;
int alive;
//0=players
//1=new potato
//2=winner
void* pl(void *arg){                                           
	int id= *(int*)arg;                                
	free(arg);                                            
	while(1){
		pthread_mutex_lock(&mtx);
		if(flag==2){
			printf("winner thread w id %d\n",id);
			pthread_mutex_unlock(&mtx);
			break;
		}
		if(potato<0){
			//send signal to monitor
			flag=1;
			pthread_cond_signal(&cond);
		}
		while(flag==1){                                                         pthread_cond_wait(&cond,&mtx);                          }
		 if(flag==2){
			 printf("winner thread w id %d\n",id);
			 pthread_mutex_unlock(&mtx);
			 break;                                                  }
		if(flag==0){
			int subtract=rand()%(100-10+1)+1;
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
        }
	printf("Thread %d exiting.\n", id);
        return NULL;
}

void* mon(){
	while(1){
		pthread_mutex_lock(&mtx);
		while(flag==0){
			pthread_cond_wait(&cond,&mtx);
		}
		potato = rand() % (10000-1000+1) + 1000;
        	printf("potato reset to: %d\n", potato);
		alive--;
		if(alive==1){
			flag=2;
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mtx);
			break;
		}
		flag=0;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mtx);
	}
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
	pthread_cond_init(&cond,NULL);
	flag=0;
	alive=N;
        for (int i=0;i < N;i++){
                int *arg = malloc(sizeof(int));
        *arg = i;
                pthread_create(&tid[i],NULL,pl,arg);
        }
	pthread_t monitor;
	pthread_create(&monitor,NULL,mon,NULL);
        for (int i=0;i<N;i++){
                pthread_join(tid[i],NULL);
        }
	pthread_join(monitor,NULL);
        pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);
        return 0;
}
