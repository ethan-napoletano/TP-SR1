 #define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h> /* constantes symboliques pour les droits d’accès */
#include <fcntl.h>
#define Taille 512

void my_cat(char *nom_fichier[], int nb_fichier, int dest){
    char bloc[Taille];
    int nbecrits;
    int nblus;
    for(int i=0;i<nb_fichier;i++){
        lseek(dest,0,SEEK_CUR);
        int fd = open(nom_fichier[i], O_RDONLY);
        if (fd == -1) {
            perror(nom_fichier[i]);
            exit(1);
        }
        nblus = read(fd, bloc, sizeof(bloc));
        while (nblus > 0) {
            nbecrits = write(dest, bloc, nblus);
            nblus = read(fd, bloc, sizeof(bloc));
        }
        if (nblus == -1) {
            perror("Erreur de lecture");
            exit(2);
        }
        if (nbecrits == -1) {
            perror("Erreur d'écriture");            
            exit(3);
        }
        close(fd);
    }
}
void main(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stderr, "Usage: %s source\n", argv[0]);
        exit(1);
    }
    int dest=STDOUT_FILENO;
    int nb_fichier=argc-2;
    char * files[argc-2];

    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],">")==0 && i+1<argc){
            dest = open(argv[i+1],O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR);
            if(dest == -1){
                perror("Erreur ouverture fichier de destination");
                exit(4);
            }
        }
    }
    for(int i=1;i<argc-2;i++){
        files[i-1]=argv[i];
    }
    my_cat(files, nb_fichier, dest);
    exit(0);
}
