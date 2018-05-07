#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define TRUE 1


int main()
{
char spaces[] = {' ', '\n','>','<','|','\0'};
char* sp = NULL;
char* sw = NULL;
char* sr = NULL;
char* s = NULL;
char* arg[17];
char* barg[17];
int charpos = 0;
int line;
int chin;
int sg = 1;
int fd, fl, mw, mr, mp;
int pipefd[2];
sp = (char*) malloc(80*sizeof(char));
sw = (char*) malloc(80*sizeof(char));
sr = (char*) malloc(80*sizeof(char));
s = (char*) malloc(80*sizeof(char));

while(TRUE)
{
line = -1;
mw = mr = mp = 0;
//sr=0; sw=1;
do
{	
	/* if((strrchr(spaces,(chin = getchar()))) != NULL)
	//if (((chin == ' ') & (strrchr(spaces,(chin = getchar()))) != NULL))
	{
		sg = 1;
	}else sg = 0; */
	//else{
	chin = getchar();
	if(chin == EOF)
	{
		putchar('\n');
		return EXIT_SUCCESS;
	}
	if(strrchr(spaces, chin) == NULL)
	{
		*(s + charpos) = chin;
		charpos++;
	}
	else
	{
		if(!sg){
			arg[++line] = (char*) malloc(80 * sizeof(char));
			arg[line+1] = NULL;
			*(s + charpos) = '\0';
			strcpy(arg[line], s);
			charpos = 0;
			free(s);
	    	s = NULL;
	    	s = (char*) malloc(80*sizeof(char));
	  	//  printf(".%s.\n", arg[line]);
	    }

	    if (chin == '>')
		{ 	
			scanf("%s", sw);
			//printf("\n%s\n", sw);
			mw=1;			
			getchar();
			
			break;
		} 

		if (chin == '<')
		{ 	
			scanf("%[^' ','\n','>','<']", sr);
			mr=1;
		} 
		if (chin == '|')
		{
			if (-1 == pipe(pipefd)) 
			{
				perror("pipe");
				return -1;
			}
			//barg = arg;
			//memcpy(barg, arg, sizeof(arg));

			int i = 0;
			do{
				barg[i] = (char*) malloc(80 * sizeof(char));
				barg[i+1] = NULL;
				strcpy(barg[i], arg[i]);
				free(arg[i]);
				i++;
			}while(i<=line);

			line = -1;
			mp = 1;
		}
	}
	if(strrchr(spaces,chin) != NULL){sg = 1;} else {sg = 0;}
}while(chin != '\n');

pid_t pid = fork();
	if (!pid)
	{ // child branch
		if(mw)
		{
			fd = open(sw, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd == -1){
				perror("open_out");
				return EXIT_FAILURE;
			}
			if(-1 == dup2(fd,STDOUT_FILENO))
			{
				perror("dup2_out");
				return EXIT_FAILURE;
			}
		}
		//printf("mw\n");

		if(mr)
		{
			fl = open(sr, O_RDONLY, 0666);
			if (fl == -1)
			{
				perror("open_in");
				return EXIT_FAILURE;
			}
			if(-1 == dup2(fl,STDIN_FILENO))
			{
				perror("dup2_in");
				return EXIT_FAILURE;
			}
		}
		//printf("mr\n");

		if(mp)
		{
			pid_t pid1 = fork();
			if (pid1 == 0) {
				close(pipefd[0]);
				// Forward STDOUT_FILENO to pipefd[0] 
				if (-1 == dup2(pipefd[1], STDOUT_FILENO)) {
					perror("dup2_barg");
					return EXIT_FAILURE;
				}
				//printf("dup2_barg\n");
				if (-1 == execvp(*barg,barg)) {
					perror("execvp_barg");
					return EXIT_FAILURE;
				}
				//printf("ex_barg\n");
			}
			
			pid_t pid2 = fork();
			if (pid2 == 0) {
				close(pipefd[1]);
				// Forward STDIN_FILENO from pipefd[1]
				if (-1 == dup2(pipefd[0], STDIN_FILENO)) {
					perror("dup2_arg");
					return EXIT_FAILURE;
				}
				//printf("dup2_arg\n");
				//printf("s=%s\n",barg[0]);
				int exarg = execvp(*arg, arg);
				//printf("ex_arg\n");
				if(exarg == -1){
				//if (-1 == execvp(*arg,arg)) {
					perror("execvp_arg");
					return EXIT_FAILURE;
				}
				printf("ex_arg\n");
			}	
			
			close(pipefd[0]);
			close(pipefd[1]);
			wait(NULL);
			wait(NULL);
			return EXIT_SUCCESS;	
		}
		//printf("mp\n");
		//printf("\nmp=%d",mp);
		if(!mp)
		{
		//printf("\nmp=%d",mp);
		int rv = execvp(*arg, arg);
		if (rv == -1)
		{
			perror("execvp");
			return EXIT_FAILURE;
		
		}
		}
		//printf("ex\n");
	}
	// parent branch
	if(mp){
		close(pipefd[0]);
		close(pipefd[1]);
		//wait(NULL);
	}
	pid = wait(NULL);
	//printf("parent\n");
	if (pid == -1)
	{
		perror("wait");
		//return EXIT_FAILURE;
	}
	//close(pipefd[0]);
 	//close(pipefd[1]);
	//return EXIT_SUCCESS;
int i = 0;
//dup2(STDOUT_FILENO,fd);
//printf("wrbrwtb\n");
do{
	free(arg[i]);
	i++;
	//arg[i++] = NULL;
}while(i<=line);

}
}

