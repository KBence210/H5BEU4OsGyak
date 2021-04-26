#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void) {
    int nbytes;
    pid_t childpid;
    char string[] = "XY jmdrgg\n";
    char readbuffer[80];
    int fd[2];
    pipe(fd);
    
    if((childpid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if(childpid == 0) {
        close(fd[0]);
        write(fd[1], string, (strlen(string)+1));
        exit(0);
    } else {      
        close(fd[1]);
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
        printf("kapott string: %s", readbuffer);
    }
    
    return(0);
}