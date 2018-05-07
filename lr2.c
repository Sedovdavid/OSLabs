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
char spaces[] = {' ', '\n','>','<','\0'};
char* sw = NULL;
char* sr = NULL;
char* s = NULL;
char* arg[17];
int charpos = 0;
int line;
int chin;
int sg = 1;
int fd, fl, mw, mr;
sw = (char*) malloc(80*sizeof(char));
sr = (char*) malloc(80*sizeof(char));
s = (char*) malloc(80*sizeof(char));

while(TRUE)
{
line = -1;
mw=mr=0;
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
			//printf("\n%s\n", s);
			mw=1;			
			getchar();
			
			break;
		} 

		if (chin == '<')
		{ 	
			scanf("%[^' ','\n','>','<']", sr);
			//printf("\n%s\n", s);
			mr=1;
			
		} 


//	}
	
	//sg = 0;
	}
//sg = 0;
	if(strrchr(spaces,chin) != NULL){sg = 1;} else {sg = 0;}
}while(chin != '\n');

pid_t pid = fork();
	if (!pid)
	{ // child branch
		if(mw)
		{
			fd = open(sw, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd == -1){
				perror("openout");
				return EXIT_FAILURE;
			}
			if(-1 == dup2(fd,STDOUT_FILENO))
		{
			perror("dup2out");
			return EXIT_FAILURE;
		}
		}

		if(mr)
		{
			fl = open(sr, O_RDONLY, 0666);
			if (fl == -1)
			{
				perror("openin");
				return EXIT_FAILURE;
			}
			if(-1 == dup2(fl,STDIN_FILENO))
		{
			perror("dup2in");
			return EXIT_FAILURE;
		}
		}

		

		

		int rv = execvp(*arg, arg);
		if (rv == -1)
		{
			perror("execvp");
			return EXIT_FAILURE;
		}
	}
	// parent branch
	pid = wait(NULL);
	if (pid == -1)
	{
		perror("wait");
		//return EXIT_FAILURE;
	}
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

