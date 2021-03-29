#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	void exit(int status);
	void abort(void);
	int status;
	int pid;
	
	if ( (pid = fork()) < 0) 
	{
		perror("fork hiba");
	}
	else if (pid == 0)
	{
		exit(7);
	}
	if (wait(&status) != pid)
	{
		 perror("wait hiba");
	}
	if (WIFEXITED(status))
	{
		printf("Normális befejeződés, visszaadott érték = %d\n", WEXITSTATUS(status));
	}
	if ( (pid = fork()) < 0)
	{
		perror("fork hiba");
	}
	else if (pid == 0)
	{
		abort();
	}
	if (wait(&status) != pid)
	{
		perror("wait hiba");
	}
	if (WIFSIGNALED(status))
	{
		printf("Abnormális befejeződés, a szignál sorszmáma = %d\n", WTERMSIG(status))	
	}

	return 0;
}