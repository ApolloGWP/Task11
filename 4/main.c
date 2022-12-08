#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int a = 1;

void handler(int signo, siginfo_t *si, void *context) { 
  if (signo == SIGUSR1){
    printf("%d. Захвачен сигнал SIGUSR1(%d).\n",a++, si->si_value.sival_int);
  }
}

int main(void) {
  pid_t pid, cpid;
  int flag;
  struct sigaction sigAction;
  //sigset_t mask;
  //sigset_t oldMask;
  union sigval value;

  sigAction.sa_sigaction = handler;
  //sigAction.sa_mask = mask;
  sigAction.sa_flags = SA_SIGINFO;

  //sigemptyset(&mask);
  //sigaddset(&mask, SIGUSR1);

  if (sigaction(SIGUSR1, &sigAction, 0) != 0) {
    fprintf(stderr, "Невозможно обработать SIGINT!\n");
    exit(EXIT_FAILURE);
  }

  if (signal(SIGTERM, SIG_DFL) == SIG_ERR) {
    fprintf(stderr, "Невозможно обработать SIGINT!\n");
    exit(EXIT_FAILURE);
  }

  pid = fork(); 
  
  if (pid == 0) {
      int i;
      for (i = 0; i < 10;i++){
        pause();  
      }
      pause();
  } 
  
  if (pid > 0) {
    int i;   
    for (i = 0; i < 10; i++){
      //sigprocmask(SIG_BLOCK, &mask, &oldMask);
      value.sival_int = i;
      sigqueue(pid, SIGUSR1, value);
      //sigprocmask(SIG_SETMASK, &oldMask, NULL);
      //sleep(1);
    }
    kill(pid, SIGTERM);
    cpid = wait(&flag);
    printf("Процесс потомок завершился.\n");
  } 
  return 0;
}
