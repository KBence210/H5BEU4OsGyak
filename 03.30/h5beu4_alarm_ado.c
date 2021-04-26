
#include <sys/types.h>
#include <signal.h>

/*
Az átadott process id-t tároljuk, madj megszüntetük egy SIGALRM signállal
*/

void main(int argc, char **argv) {
	int pid;

	if (argc < 1) {
		perror(" Nincs kinek");
		exit(1);
	}

	pid = atoi(argv[1]);

	kill(pid, SIGALRM);
}