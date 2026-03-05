#define _POSIX_C_SOURCE 200809L
#define  MAX_BASSIN 5
#define N 10
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char* argv[]){

    int tubeRemplir[2], tubeEtat[2];
    int lus,nblus;
    int bassin = 0;
    int un=1,moinun=-1;
    

    if(pipe(tubeRemplir)==-1){
        perror("echec pipe remplir");
        exit(7);
    }
    if(pipe(tubeEtat)==-1){
        perror("echec pipe etat");
        exit(2);
    }


    pid_t pid = fork();

    if(pid == -1)
    {
        perror("echec fork");
        exit(3);
    }
    if(pid == 0)/*fils*/
    {
        close(tubeEtat[0]);
        close(tubeRemplir[1]);

        while(nblus=read(tubeRemplir[0],(void *)&lus,sizeof(int))>0){
            if(lus>0)
            {
                bassin += lus;
                printf("*");
                fflush(stdout);
                if(bassin>=MAX_BASSIN){
                    if(write(tubeEtat[1], &bassin, sizeof(int))==-1){
                        perror("echec write bassin");
                        exit(5);
                    }
                }
            }
            else
            {
                bassin = 0;
                printf("\n");
            }
        
        }

        close(tubeRemplir[0]);
        close(tubeEtat[1]);
        exit(1);
    }
    else/*pere */
    {
        close(tubeEtat[1]);
        close(tubeRemplir[0]);

        int f_flags; /* mode non bloquant pour le tube Etat dans le Pere */
        f_flags = fcntl(tubeEtat[0], F_GETFL); /* Recuperation des flags */
        f_flags |= O_NONBLOCK; /* Positionnement du flag de non blocage */
        fcntl(tubeEtat[0], F_SETFL, f_flags); /* Mise a jour des flags */

        for(int i=1; i<=N; i++){
            sleep(1);
            if(write(tubeRemplir[1], &un, sizeof(int))==-1){
                perror("echec write un");
                exit(4);
            }
            if(nblus=read(tubeEtat[0],(void *)&lus,sizeof(int))>0){
                if(write(tubeRemplir[1], &moinun, sizeof(int))==-1){
                    perror("echec write moinun");
                    exit(5);
                }
            }
        }
        if(nblus ==-1){
            perror("echec read etat pere");
            exit(6);
        }

        close(tubeRemplir[1]);
        close(tubeEtat[0]);
        int codefils;
        wait(&codefils);
        printf("\n");
        printf("[PERE] : mon fils %d est terminer avec le code %d\n",pid,WEXITSTATUS(codefils));
    }

    return 0;
}
