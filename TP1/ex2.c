#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

//programe quand le pere nattend pas la fin du fils
/*int main(void){
    pid_t pid=fork();
    if(pid==-1){
        perror("fork");
        exit(1);
    }
    if(pid==0){
        execlp("/bin/ls","ls""-al",NULL);
        perror("ls");
        exit(1);
    }
    else{
        execlp("/bin/date","date",NULL);
        perror("date");
        exit(2);
    }

}*/

//quand le pere attend le fils
int main(void){
    pid_t pid=fork();
    if(pid==-1){
        perror("fork");
        exit(1);
    }
    if(pid==0){
        execlp("/bin/ls","ls""-al",NULL);
        perror("ls");
        exit(1);
    }
    else{
        wait(NULL);
        execlp("/bin/date","date",NULL);
        perror("date");
        exit(2);
    }

}