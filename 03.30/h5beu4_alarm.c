#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#define SECOND 1

void do_nothing();
void do_int();

/*
SIGINT = Interrupt jelzés. PL : Ctrl + c (unixban)
signal() két része van a jelzés és a jelzés kezelő
alarm() SIGALRM jelzést generál megadott masodpercek utan
Ha 0 az alarm akkor az elotte függő alarmokat megszünteti.
SIG_IGN ignorálja a jelzést
pause() megallitja a programot, amig nem jon a signal
*/

void main () {
	int i;
	unsigned int sec = 1;

	signal(SIGINT, do_int);
	//signal(SIGALRM) várja a signalt, nem csinal semmit
	for (i = 1; i < 8; i++) {
		alarm(sec);
		signal(SIGALRM, do_nothing);
		printf("  %d varok de meddig?\n",i);
		pause();
	}
}	

void do_nothing(){ 
	;
}

void do_int() {
	printf(" int jott ");
	signal(SIGINT,SIG_IGN);
}