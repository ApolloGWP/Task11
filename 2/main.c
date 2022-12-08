#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

char *msg;

static void signal_handler(int signo) {
	if (signo == SIGALRM){
		printf("%s\n", msg);
	}
}

int main(int argc, char **argv) {
	pid_t pid;	
	if (signal(SIGALRM, signal_handler) == SIG_ERR) {
		fprintf(stderr, "Невозможно обработать SIGALRM!\n");
		exit(EXIT_FAILURE);
	}
	msg = argv[2];
	double sec = atof(argv[1]);
	pid = fork();
	if (pid == 0) {
		alarm(sec);
		pause();
	}
	if (pid > 0) {
		printf("Завершение главного потока.\n");
		exit(EXIT_SUCCESS);
	} 
	return 0;
}

