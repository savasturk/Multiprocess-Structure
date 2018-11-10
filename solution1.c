#include <sys/types.h> /*Primitive system data types */ 
#include <errno.h> /* Errors */
#include <sys/wait.h> /* Wait for process termination */
#include <stdio.h> /* Input/Output */
#include <unistd.h> /* Symbolic constans */
#include <stdlib.h> /* General utilities */


int main(void)
{
	pid_t cp1;
	pid_t cp2;
	pid_t cp3;
	int password;
	int trying;
	printf("parent process id %d\n", getpid());
	password=getpid();
	cp1 = fork();
	if(cp1==0){
		printf("1st child process id %d (parent:%d)\n",getpid(),getppid());
		FILE *fp=fopen("opsys.txt","w");;
		printf("file was created...\n");
	}
	else if(cp1>0){
		wait(NULL);
		
		cp2 = fork();
		cp3 = fork();
		
		if(cp2>0 && cp3>0)
		{
			sleep(45);
			
			printf("parent process id %d (parent:%d)\n",getpid(),getppid());
			
			printf("program finished...\n");
		}
		else if(cp2==0 && cp3>0)
		{
			
			sleep(5);
			FILE *fp=fopen("opsys.txt","a");
			printf("2nd child process id %d (parent:%d)\nwrite key:\n",getpid(),getppid());
			
			scanf("%d", &trying);
			sleep(10);
			printf("trying:%d\n",trying);
			fprintf(fp,"%d\n",trying);
			
			fclose(fp);
		}
		else if(cp2>0 && cp3==0)
		{
			sleep(30);
			FILE *fp=fopen("opsys.txt","r");
			printf("3rd child process id %d (parent:%d)\n",getpid(),getppid());
			
			fscanf(fp,"%d",&trying);
			sleep(10);
			printf("trying key:%d\n",trying);
			if(trying==password){
				printf("matched...\n");
			}
			else{
				printf("not matched...\n");
			}
			fclose(fp);
		}
		else if(cp2==0 && cp3==0)
		{
			printf("4th child process id %d (parent:%d)\n",getpid(),getppid());
			
			printf("say me password (please wait)...\n");
		}
		else if(cp2<0)
		{
			perror("cp2 fork");
			exit(0);
		}
		else if(cp3<0)
		{
			perror("cp3 fork");
			exit(0);
		}
	}
	else{
		perror("cp1 fork");
		exit(0);
	}
	return(0);
}
