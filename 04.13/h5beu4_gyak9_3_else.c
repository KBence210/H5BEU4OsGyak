
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

void handleSigalarm();

void main() {
    printf("A program pidje : %d\n",getpid());
    signal(SIGALRM, handleSigalarm);
    pause();
    printf("kibillent\n");
    exit(0);
}

void handleSigalarm() {
    printf("h5bau4\n");
    