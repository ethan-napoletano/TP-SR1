#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 


void lire_n_ieme(int n, int fd){
    int entier;
    if(lseek(fd, (n-1)*sizeof(int), SEEK_SET) == -1){
        perror("Erreur 1");
        exit(3);
    }
    if(read(fd,(void*)&entier,sizeof(int))==-1){
        perror("Erreur 2");
        exit(4);
    }
    printf("l'entier %d est : %d\n",n,entier);
  
}

void ecrire_n_ieme(int n,int entier, int fd){
    if(lseek(fd, (n-1)*sizeof(int), SEEK_SET) == -1){
        perror("Erreur 3");
        exit(3);
    }
    if(write(fd,(void*)&entier,sizeof(int))==-1){
        perror("Erreur 4");
        exit(4);
    }
}

int main(int argc,char* argv[]){
    if(argc <3 || argc >4){
        fprintf(stderr,"Usage %s n fsource | n entier fsource \n",argv[0]);
        exit(1);
    }

    if(argc ==  3){
        int n= atoi(argv[1]);
        int f= open(argv[2],O_RDONLY);
        if(f == -1){
            perror("echec read lire");
            exit(2);
        }
        lire_n_ieme(n,f);
    }else if(argc == 4){
        int n= atoi(argv[1]);
        int entier= atoi(argv[2]);
        int f= open(argv[3],O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        if(f == -1){
            perror("echec read ecrire");
            exit(2);
        }
        ecrire_n_ieme(n,entier,f);
    }

    return 0;
}