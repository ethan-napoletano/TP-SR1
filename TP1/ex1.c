#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void afficher_info_processus() {
    printf("pid : %d\n", getpid());
    printf("ppid : %d\n", getppid());
    printf("pgrp : %d\n", getpgrp());
    printf("login : %s\n", getlogin());
    printf("uid : %d\n", getuid());
    printf("gid : %d\n", getgid());
}

int main(void) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    else if (pid > 0) {
        int info;
        wait(&info); 
        printf("Code de retour du fils : %d\n", WEXITSTATUS(info));
        printf("Processus père :\n");
        afficher_info_processus();
        
    } else if (pid == 0) {
        printf("Processus fils :\n");
       afficher_info_processus();
       
    }
    
    exit(0);

   
} 
