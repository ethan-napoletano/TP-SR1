 #define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> /* constantes symboliques pour les droits d’accès */
#include <fcntl.h>
#define Taille 512

 void ecrire_dans_stdout(char nom_fichier[]){
    int fd = open(nom_fichier, O_RDONLY);
    if (fd == -1) {
        perror(nom_fichier);
        exit(1);
    }
    char bloc[Taille];
    int nbecrits;
    int nblus = read(fd, bloc, sizeof(bloc));
    while (nblus > 0) {
        nbecrits = write(STDOUT_FILENO, bloc, nblus);
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

int main(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stderr, "Usage: %s source\n", argv[0]);
        exit(0);
    }
    ecrire_dans_stdout(argv[1]);
    exit(0);
}