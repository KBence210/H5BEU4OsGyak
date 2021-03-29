#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	pid_t fork(void);
	pid_t wait(int *wstatus);
	pid_t waitpid(pid_t pid, int *wstatus, int options);
	int execl(const char *path,const char arg*,...);
	int execlp(const char *file,const char arg*,...);

	if((pid=fork())<0)
	{
		perror("fork error");
	}
	else if(pid==0)
	{
		if(execl("./parent","child",(char*)NULL)<0)
		{
			perror("execl error");
		}
	}
	if(waitpid(pid,NULL,0)<0)
	{
		perror("wait error");
	}
	return 0;
}