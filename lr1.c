#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1

int main()
{
char spaces[] = {' ', '\n'};
char *s = NULL;
char *arg[17];
int charpos = 0;
int line;
int chin;
s = (char*) malloc(80*sizeof(char));

while(TRUE)
{
line = -1;
do
{
	chin = getchar();
	if(chin == EOF)
	{
		putchar('\n');
		return EXIT_SUCCESS;
	}
	if(strrchr(spaces, chin) == NULL)
	{
		*(s+charpos) = chin;
	}
	else
	{
		arg[++line] = (char*) malloc(80 * sizeof(char));
		*(s+charpos) = '\0';
		strcpy(arg[line], s);
		charpos = -1;
		free(s);
		s = NULL;
		s = (char*) malloc(80*sizeof(char));
	}
	charpos++;
}while(chin != '\n');

pid_t pid = fork();
	if (!pid)
	{ // child branch
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
do{
	free(arg[i]);
	arg[i++] = NULL;
}while(i<=line);

}
}