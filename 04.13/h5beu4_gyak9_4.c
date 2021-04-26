#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>

void sigtermKezelo() ;

void main(int argc, char const *argv[]) {
    if (argc < 1) {
        perror("nincs argumentum");
        exit(-1);
    }
    int n = atoi(argv[1]);  
    signal(SIGTERM, sigtermKezelo);
    while (true) {
        printf("%d\n", n);
        sleep(3);
    }
}

void sigtermKezelo() {
    signal(SIGTERM, SIG_IGN);
}