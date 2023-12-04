/*
QUESTION 4 :
Display the return code (or signal) of the previous command in the prompt.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define INPUT_SIZE 200

// function to display a welcome message
void display_welcome() {
    const char welcome_message[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    write(STDOUT_FILENO, welcome_message, sizeof(welcome_message) - 1);
}

// function to display a prompt message
void display_prompt() {
    const char prompt_message[] = "enseash %% ";
    write(STDOUT_FILENO, prompt_message, sizeof(prompt_message) - 1);
}

// function to display an exit message
void enseash_exit() {
    const char goodbye_message[] = "Bye bye...\n";
    write(STDOUT_FILENO, goodbye_message, sizeof(goodbye_message) - 1);
}



//
void execut(char *command){
    char command_path[]="/bin/";
    strcat(command_path, command);
    execlp(command_path, command, (char *)NULL);

    // in case it fails
    perror("Error executing command");
    exit(EXIT_FAILURE);
}

void writeCode(int code, int signal){
    char code_buffer[20];
    char signal_buffer[20];

    sprintf(code_buffer, "%d", code);
    sprintf(signal_buffer, "%d", signal);

    write(STDOUT_FILENO, code_buffer, strlen(code_buffer));
    write(STDOUT_FILENO, signal_buffer, strlen(signal_buffer));
}

int main(){
    int nbChar;
    int status;
    char command[INPUT_SIZE];

    display_welcome();

    while(1){
        display_prompt();

        nbChar = read(STDIN_FILENO, command, INPUT_SIZE);
        command[nbChar-1] = '\0';

        if(strcmp(command, "exit")==0 || strcmp(command, "")==0){
            enseash_exit();
            break;
        }

        pid_t ret = fork();

        if(ret==0){
            execut(command); //child
        }
        else{
            wait(&status); //parent
            if(WIFEXITED(status) != -1){
                writeCode(WEXITSTATUS(status),0);
            }
            else if(WIFSIGNALED(status)){
                writeCode(0,WTERMSIG(status));
            }
        }
    }
    return 0;
}