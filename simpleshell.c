#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>



 int main()
{
int maxnochar = 20;
char instruct[maxnochar];
char * splitted [5]={NULL,NULL,NULL,NULL,NULL};
int i=0;
int j=0;
int c=0;
int z=0;
int cdres;
int statuswait ;
int forkoutput = 0;
int waitres ;
char arr [10];
char cpy [10]; 
char cwd [20];
 while (1)
{
    int splitindex = 0;
    printf("SimpleShell>> : ");
    fgets(instruct,maxnochar,stdin);
    // fflush(stdin);
    int lastocc = strcspn(instruct,"\n");
    instruct[lastocc] = '\0';
    strcpy(cpy,instruct);
    if (cpy[strlen(cpy)-1] == '&')
    {
        z = 1; 
        cpy[strlen(cpy)-1] = '\0';
        strcpy(instruct,cpy);
        printf("l2ena & w 4eltha \n");
    }    
    char * toks = strtok(instruct," ");
    while (toks != NULL)
    {
        printf("peice : %s\n",toks);
        splitted[splitindex] = strdup(toks);
        splitindex++;
        toks = strtok(NULL," ");
        
    }
    while (c<splitindex)
    {
        printf("splitted : %s\n",splitted[c++]);
    }
    
    if (strcmp(instruct,"exit")==0)
    {
        exit(0);
    }

        if(strcmp(splitted[0],"cd")==0){
        printf("d5l cd\n");
        chdir(splitted[1]);
        if(getcwd(cwd,sizeof(cwd)) != NULL){
            printf("Current Directory is now >> %s \n",cwd);
        }else{
            printf("getcwd error\n Exiting now\n");
            exit(0);
        }}else{
    forkoutput = fork();
    if(forkoutput < 0){
        printf("fork not successfull !\n");
        exit(EXIT_FAILURE);
    }else if(forkoutput == 0){  //return to child
    printf("d5l l child\n");

    
        execvp(splitted[0],splitted);
        printf("execvp not successfull\n");
    }else{ // return to parent
    printf("d5l l parent\n");
      signal(SIGCHLD,handlerfile(forkoutput));
        if(z == 0){
            printf("mfii4 &\n");
            printf("h3ml wait\n");
            waitres = waitpid(forkoutput,statuswait,WUNTRACED);
            printf("child terminated\n");
        }else{
            printf("child running in background with pid : %d\n",forkoutput);
            
        }
        
    }
}
}
return 0;
}

void handlerfile(int u){
    FILE * fileptr = fopen("/home/abobakr/Desktop/logfile.txt","a");
    if (fileptr == NULL)
    {
        printf("Error creating file\n");
    }else{
        fprintf(fileptr,"Child >>  %d  <<Has Been Terminated\n",u);
        fclose(fileptr);
    }
    
}

