#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
char input[256];
char history[100][256];
int historycount=0;

printf("\033[1;33m");
printf("================================\n");
printf("       Welcome to myshell!      \n");
printf("  Type 'help' to get started   \n");
printf("================================\n");
printf("\033[0m");

while(1){
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    printf("\033[1;32mmyshell\033[0m:\033[1;34m%s\033[0m> ", cwd);
    fgets(input,256,stdin);
    input[strcspn(input,"\n")]=0;
    strcpy(history[historycount],input);
    historycount++;
    if(strcmp(input,"exit")==0){break;}

    if(strcmp(input,"!!")==0){
        if(historycount<2){ printf("No previous command\n"); continue;}
        strcpy(input,history[historycount-2]);
        printf("%s\n",input);
    }

    char *args[100];
    int i=0;
    args[i]=strtok(input," ");
    while(args[i]!=NULL){ i++; args[i]=strtok(NULL," "); }
    args[i]=NULL;

    int pipe_index=-1;
    for(int j=0;j<i;j++){
        if(strcmp(args[j],"|")==0){ pipe_index=j; break; }
    }

    if(strcmp(args[0],"cd")==0){
        chdir(args[1]);
    }
    else if(strcmp(args[0],"history")==0){
        for(int j=0;j<historycount;j++)
            printf("%d  %s\n",j+1,history[j]);
    }
    else if(strcmp(args[0],"help")==0){
        printf("Commands:\n");
        printf("  cd <dir>   - change directory\n");
        printf("  history    - show command history\n");
        printf("  help       - show this help\n");
        printf("  exit       - quit the shell\n");
        printf("  clear      - clears the screen\n");
        printf("  !!         - repeats last command\n");
        printf("  any other command runs normally\n");
    }
    else if(strcmp(args[0],"clear")==0){
        printf("\033[2J\033[H");
    }
    else{
        if(pipe_index!=-1){
            char *cmd1[100];
            char *cmd2[100];
            for(int j=0;j<pipe_index;j++) cmd1[j]=args[j];
            cmd1[pipe_index]=NULL;
            int k=0;
            for(int j=pipe_index+1;j<i;j++) cmd2[k++]=args[j];
            cmd2[k]=NULL;

            int fd[2];
            pipe(fd);

            pid_t pid1=fork();
            if(pid1==0){
                dup2(fd[1],STDOUT_FILENO);
                close(fd[0]); close(fd[1]);
                execvp(cmd1[0],cmd1);
                perror(cmd1[0]); exit(1);
            }

            pid_t pid2=fork();
            if(pid2==0){
                dup2(fd[0],STDIN_FILENO);
                close(fd[0]); close(fd[1]);
                execvp(cmd2[0],cmd2);
                perror(cmd2[0]); exit(1);
            }

            close(fd[0]); close(fd[1]);
            wait(NULL); wait(NULL);

        } else {
            pid_t pid=fork();
            if(pid==0){
                execvp(args[0],args);
                perror(args[0]); exit(1);
            } else {
                wait(NULL);
            }
        }
    }
}
return 0;
}




