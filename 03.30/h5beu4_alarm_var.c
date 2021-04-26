#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void do_nothing();

void main () {
	printf("  varok de meddig?\n");
	
	signal(SIGALRM, do_nothing);
	
	pause();

    printf("  Vegre, itt az alarm \n");
}

void do_nothing() { 
	;
}