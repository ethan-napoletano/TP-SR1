#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <time.h>

int main(int argc, char* argv[]){
    if(argc !=2){
        fprintf(stderr,"Usage %s REP \n",argv[0]);
        exit(1);
    }

    struct stat infos;
    int nbfichvide=0;

    for(int i=1;i<argc; i++)
    {
        DIR* rep=opendir(argv[i]);
        if(rep==NULL){
        perror("echec opendir");
        exit(2);
        }
        
        struct dirent * entree;
        char des[512];

        while((entree = readdir(rep))!= NULL){
            if (lstat(entree->d_name, &infos)==-1){
                perror("Echec lstat");
                exit(3);
            }
            if (S_ISREG(infos.st_mode) && (infos.st_size == 0))
            {
                printf("%s%s \n",des,entree->d_name);
            }else{
                strcat(des, entree->d_name);
                strcat(des, "/");
            }
            
            
        }
    }

    return 0;
}