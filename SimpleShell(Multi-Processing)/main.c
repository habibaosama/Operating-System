#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#define MAX_SIZE 100
#define LIMIT 1024

char * arguments[MAX_SIZE];
char* value[2];
char input[MAX_SIZE];
int pid;
bool iswaiting;
int status;
int cnt =0;

printdir(){
    char cwd[LIMIT];
    if (getcwd(cwd, sizeof(cwd))!=NULL) {
        printf("\nYour Command: %s>> ", cwd);
    }else{
        printf("this directory not found");
    }

}
void changeDirectory(){
    if (arguments[1] == NULL || strcmp(arguments[1],"~")==0) {
        chdir(getenv("HOME"));
        printf("\n");

    }else{

        if (chdir(arguments[1]) == -1) {
            printf(" %s: no such directory\n", arguments[1]);

        }
    }

}
void readingInput (){
    printdir();
    //reading input
    fgets(input,MAX_SIZE,stdin);
    int i=0;
    //loop to remove end of command line
    while(input[i++] != '\n');
}

parseInput() {
    cnt=0;
    if (input[strlen(input) - 1] == '&'){
        input[strlen(input) - 1] = '\0';
        iswaiting = false;
    }
    int i = 0;
    arguments[strlen(input) - 1] = '\0';
    //Argument 0 is the name of the command
    arguments[0] = strtok(input, " \n");
    if (arguments[i] == NULL)
        return 0;

    while (arguments[i] != NULL) {
        cnt++;

        arguments[++i] = strtok(NULL, " \n");
    }

}
void export(){
    char* var=arguments[1];
    value[0]=strtok(arguments[1],"=");
    var=var+ strlen(value[0])+1;
    value[1]=var;
    if(value[1][0]=='\"'){
        value[1]=strtok(value[1],"\"");
        if(cnt>2)
            arguments[cnt-1][strlen(arguments[cnt-1])-1]='\0';
    }

    int i=2;
    while(arguments[i++]!=NULL){
        memset(value[1]+ strlen(value[1]),' ',1);
    }

    //as value[0] is the variable and value[1] is the value
    setenv(value[0],value[1],1);

}
void echo(){
    if(arguments[1][0]=='\"'){
        int i=1;
        arguments[1]=strtok(arguments[1],"\"");


        if(cnt>2)
            arguments[cnt-1][strlen(arguments[cnt-1])-1]='\0';

        while(arguments[i]!=NULL) {
            printf("%s ", arguments[i]);
            i++;
        }
    }
    char* p=strstr(arguments[1],"$");

    if(p) {
        //evaluate
        printf("%s\n", getenv(p+1));

    }
}
///////////////////////////////////////////
void readParse(){
    readingInput ();
    input[strlen(input)-1]='\0';
    parseInput();
}

/////////////////////////////////////////
void executeCommand(){
    // exit shell
    if( strcmp(arguments[0],"exit") == 0 )
    {
        kill(0,SIGKILL);
        // exit(0);
    }
    // fork child process
    pid = fork();
    if(!pid){
        int x = execvp(arguments[0], arguments);

        if( x < 0 )
        {
            perror("Command can't be executed \n");
            exit(x);
        }
        exit(0);
    }else{
        //parent waits
        if(iswaiting) {
            waitpid(pid, &status, WUNTRACED);
            printf("-- Wait is finished successfully , parent will proceed -- \n");
        }
    }

}

//function to log termination into log file when a child signals its termination
void logAction()
{
    FILE* fptr;
    fptr = fopen("log.txt", "a");

    fputs("termination of child\n",fptr);
    fclose(fptr);

}

int main() {
    signal (SIGCHLD, logAction);
    while (1) {
        iswaiting = true;
        readParse();
        if (strcmp(arguments[0], "cd") == 0 ||
            strcmp(arguments[0], "echo") == 0 || strcmp(arguments[0], "export") == 0) {
            if (strcmp(arguments[0], "cd") == 0) {
                changeDirectory();
            } else if (strcmp(arguments[0], "echo") == 0) {
                echo();

            } else if (strcmp(arguments[0], "export") == 0) {
                export();
            }
        } else {
            if(cnt>1) {
                if (arguments[1][0] == '$') {
                    arguments[1] = strtok(arguments[1], "$");
                    char *temp = getenv(arguments[1]);
                    arguments[1] = strtok(temp, " ");
                    //printf("%s\n",arguments[2]);
                    int i = 1;
                    while (arguments[i] != NULL) {
                        arguments[++i] = strtok(NULL, " ");
                    }
                }
            }
            executeCommand();
        }
    }
    return 0;
}
