#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int countSigInt = 0;

void sigIntHandler(int s) {
    if (s == SIGINT) {
        printf("Megvan SIGINT %d\n", s);
        signal(SIGINT, SIG_DFL); //alapertelmezett kezeles
        countSigInt++;
    }
}

void sigQuitHandler(int s) {
    if (s == SIGQUIT) {
        printf("Megvan SIGQUIT %d", s);
    }
}

void handleSignals() {

    if (signal(SIGINT, sigIntHandler) == SIG_ERR) {
        printf("nem sikerult elkapni");
    }

    if (signal(SIGQUIT, sigQuitHandler) == SIG_ERR) {
        printf("Nem sikerult elkapni");
    }

    while (countSigInt < 2) {
        printf("...\n");
        sleep(1);
    }
}

void main() {
   handleSignals();
}