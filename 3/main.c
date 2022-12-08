#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int a = 0;

static void signal_handler(int signo) {
	if (signo == SIGUSR1){
		printf("%d. Захвачен сигнал SIGUSR1!\n", a);
		a++;
	}
}

int main(void) {
	int flag = 0;
	pid_t pid;	
	pid = fork();
	while(1){
		if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
			fprintf(stderr, "Невозможно обработать SIGUSeR1!\n");
			exit(EXIT_FAILURE);
		}	
		if (pid == 0) {
			kill(getppid(), SIGUSR1);
			pause();
			printf("Процесс - потомок:\n");
		} 
		if (pid > 0) {
			pause();
			printf("Родительский процесс:\n");
			kill(pid, SIGUSR1);
		} 
		//sleep(1);
	}
	return 0;
}

