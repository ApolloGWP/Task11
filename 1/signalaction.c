#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo) {
	if (signo == SIGINT)
		printf("Захвачен сигнал SIGINT!\n");
	else if (signo == SIGTERM)
		printf("Захвачен сигнал SIGTERM!\n");
	else {
		fprintf(stderr, "Неожиданный сигнал!\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}


int main (void) {
	struct sigaction sa;
	//sigset_t newset;
    sa.sa_handler = signal_handler;
     	
	
	if (sigaction(SIGINT, &sa, 0) != 0) {
		fprintf(stderr, "Невозможно обработать SIGINT!\n");
		exit(EXIT_FAILURE);
	}

	if (sigaction(SIGTERM, &sa, 0) != 0) {
		fprintf(stderr, "Невозможно обработать SIGTERM!\n");
		exit(EXIT_FAILURE);
	}

	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGPROF, &sa, 0) != 0) {
		fprintf(stderr, "Невозможно сбросить SIGPROF!\n");
		exit(EXIT_FAILURE);
	}

	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGHUP, &sa, 0) != 0) {
		fprintf(stderr, "Невозможно игнорировать SlGHUP!\n");
		exit(EXIT_FAILURE);
	}
	for (;;) {
		raise(SIGTERM);
		pause();
	}
	return 0;
}
