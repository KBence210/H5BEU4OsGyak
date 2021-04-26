#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FN "jmdrgg"

void main() {
    int nbytes;
    pid_t childpid;
    char string[] = "Nagy Robert\n";
    char readbuffer[80];
    
    mkfifo(FN, S_IFIFO | 0666);    

    if ((childpid = fork()) == -1) {
            perror("fork hiba");
            exit(1);
    }

    if (childpid == 0) {
        int fd = open(FN, O_WRONLY);
        write(fd, string, sizeof(string));
        close(fd);
        unlink(FN);
    } else {      
        int fd2 = open(FN, O_RDONLY);
        nbytes = read(fd2, &readbuffer, sizeof(readbuffer));
        close(fd2);
        unlink(FN);
        printf("%s", readbuffer);
    }  
}