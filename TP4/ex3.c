#define _POSIX_C_SOURCE 200809L
#define N 4
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <time.h>
#include <dirent.h>


#define _POSIX_C_SOURCE 200809L /* Pour respecter la norme POSIX.1-2017 */
#include <math.h>         /* Pour sqrt */

int est_premier (unsigned long long int n)
{
  if ((n>1) && (n==2 || n==3 || ((n%2)&&(n%3))))
  {
    unsigned long long int i,y;

    y=sqrt(n)+1;
    i=5;
    while(i<y)
    {
      if (n%i == 0)
        return 0;
      i+=2;
      if (n%i == 0)
        return 0;
      i+=4;
    }
    return 1;
  }
  return 0;
}

void TraiterFichier(int tubeF[],int tubeR[],char* repertoire,char* majicnumber){
    if(pipe(tubeF)==-1){
        perror("erreur pipe");
        exit(EXIT_FAILURE);
    }

    int nblus;
    char* lus[1024];
    

    for (int i = 0; i < N; i++)
    {
        pid_t pidTraiterF = fork(); 
        switch(pidTraiterF){
            case -1:
                perror("echec fork");
                exit(EXIT_FAILURE);
                break;

            case 0:/*fils*/
                close(tubeR[0]);
                close(tubeF[1]);


                int len_mj = strlen(majicnumber) + 1;

                while(nblus = read(tubeF[0],(void*)&lus,sizeof(lus))){
                    int f = open(lus,0_RDONLY);

                    }
                }

            
                close(tubeF[0]);
                close(tubeR[0]);
                close(tubeR[1]);
                
                struct stat infos;
                
                DIR* rep=opendir(repertoire);
                if(rep==NULL){
                    perror("echec opendir");
                    exit(2);
                }

                struct dirent * entree;
                char desi[1024];

                while((entree = readdir(rep))!= NULL){

                    strcpy(desi,repertoire);
                    strcat(desi,"/");
                    if (lstat(entree->d_name, &infos)==-1){
                        perror("Echec lstat");
                        exit(2);
                    }

                    if(S_ISREG(infos.st_mode)){
                        strcat(desi, entree->d_name);
                        if(write(tubeF[1], &desi,sizeof(char))==-1){
                            perror("echec write tubeF");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
        }
    }


int main(int argc,char* argv[]){

    if(argc !=3){
        fprintf(stderr,"Usage %d majicnumber Repertoire");
        exit(1);
    }

    int tubeFichier[2];
    int tubeReponse[3];

    if(pipe(tubeReponse)==-1){
        perror("erreur pipe");
        exit(2);
    }

   
    pid_t pid = fork();

    switch(pid){
        case -1:
            perror("echec fork");
                exit(3);
                 break;

            case 0:/*fils*/
                close(tubeReponse[1]);

                break;

            default:
                if(pipe(tubeFichier)==-1){
                    perror("erreur pipe tube Fichier");
                    exit(EXIT_FAILURE);
                }
                
                TraiterFichier(tubeFichier,tubeReponse,argv[2],argv[1]);
                break;

        }
    

    return 0;
}
