#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <time.h>
#include <dirent.h>

void Affiche_inode(struct stat * Infos){

     char *type;

    // Déterminer le type de fichier
    if (S_ISREG(Infos->st_mode)) {
        type = "fichier ordinaire";
    } else if (S_ISDIR(Infos->st_mode)) {
        type = "répertoire";
    } else if (S_ISLNK(Infos->st_mode)) {
        type = "lien symbolique";
    } else if (S_ISCHR(Infos->st_mode)) {
        type = "périphérique de caractère";
    } else if (S_ISBLK(Infos->st_mode)) {
        type = "périphérique de bloc";
    } else if (S_ISLNK (Infos->st_mode)){
        type = "lien symbolique";
    } else if (S_ISSOCK(Infos->st_mode)){
        type = "socket";
    }else{
        type= "autre";
    }
    printf("%s, taille %ld, date der modif: %s",type,Infos->st_size, ctime(&(Infos->st_mtime)));
}


int main(int argc, char* argv[]){
     if(argc < 2){
        fprintf(stderr,"Usage %s fichier[...] \n",argv[0]);
        exit(1);
    }
    struct stat infos;
    if(argc == 2)
    {
        DIR* rep=opendir(argv[1]);
        if(rep==NULL){
        perror("echec opendir");
        exit(2);
        }
        struct dirent * entree;
        while((entree = readdir(rep))!= NULL){
            if (lstat(entree->d_name, &infos)==-1){
                perror("Echec lstat");
                exit(2);
            }
            printf("%-10s ",entree->d_name);
            Affiche_inode(&infos);
        }
        closedir(rep);
    }else
    {
        for(int i=1; i<argc;i++){
            if (lstat(argv[i], &infos)==-1){
                perror("Echec lstat");
                exit(2);
            }   
            printf("%-10s ",argv[i]);
            Affiche_inode(&infos);
        }
    }
    return 0;
}