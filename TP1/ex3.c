#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define NBMOTSMAX 20

int Decoupe(char Chaine[], char *pMots[])
{
  char *p;
  int NbMots=0;

  p=Chaine;	/* On commence par le début */
  /* Tant que la fin de la chaîne n'est pas atteinte et qu'on ne déborde pas */
  while ((*p)!='\0' && NbMots<NBMOTSMAX)
  {
    while ((*p)==' ' && (*p)!='\0') p++; /* Recherche du début du mot */
    if ((*p)=='\0') break;	/* Fin de chaîne atteinte */
    pMots[NbMots++]=p;		/* Rangement de l'adresse du 1er caractère du mot */
    while ((*p)!=' ' && (*p)!='\0') p++; /* Recherche de la fin du mot */
    if ((*p)=='\0') break;	/* Fin de chaîne atteinte */
    *p='\0';			/* Marquage de la fin du mot */
    p++;			/* Passage au caractère suivant */
  }
  pMots[NbMots]=NULL;		/* Dernière adresse */
  return NbMots;
}

int main(int argc, char* argv[]){
    char * tab[NBMOTSMAX+1];
    int i;
    for(i=1;i<argc;i++){
        char * cmd = argv[i];
        Decoupe(cmd,tab);
        pid_t pid=fork();
        if(pid==-1){
            perror("fork");
            exit(1);
        
        }
        if(pid){
            printf("[%d] J'ai délégué %s a %d. Jattend sa fin...\n",getpid(),cmd,pid);
            wait(NULL);
            printf("%d terminé\n",pid);
            
            
        }
        else{
            printf("[%d]: je lance : %s\n",getpid(),cmd);
            execvp(tab[0],tab);
            
        }

    }
    return 0;
}



