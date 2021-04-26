
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

void main(int argc, char const *argv[]) {
    if (argc < 1) {
        perror("nincs argumentum\n");
        exit(-1);
    }
    pid_t pid = atoi(argv[1]);
    if (kill(pid, SIGALRM) == -1) {
        perror("sikertelen signalozas\n");
   