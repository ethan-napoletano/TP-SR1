#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {
    int tube[2];
    int n=4;
    if (pipe(tube) == -1) {
        perror("pipe");
        exit(1);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(2);
    }
    if(pid==0){
        close(tube[1]);
        int nblus;
        while(read(tube[0],(void *)&nblus,sizeof(int))>0){
            printf("fils : n=%d\n",n);
        }
        if(nblus==-1){
            perror("read");
            exit(3);
        }
        close(tube[0]);
        exit(0);
    }
    else{
        close(tube[0]);
        for(int i=1;i<n;i++){
            sleep(1);
            if(write(tube[1],(void *)&i,sizeof(int))==-1){
                perror("write");
                exit(4);
            }
            
        }
        int w;
        close(tube[1]);
        wait(&w);
        printf("Pere : fin du fils %d\n",WEXITSTATUS(w));
    }

    return 0;
}