
/*
QUESTION 3 :
Gestion de la sortie du shell avec la commande “exit” ou un <ctrl>+d;

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

// function to display a new line in the shell
void disp_NewLine() {
    const char newLineChar[] = "\n\r";
    write(STDOUT_FILENO, newLineChar, sizeof(newLineChar) - 1);
}

int readCommand(char* input){ // read user input and execute exit command

    // read user input
    char* err = fgets(input, INPUT_SIZE, stdin);

    // remove the newline char at the end of the input
    input[strlen(input)-1] = '\0';

    return (err == NULL); // return 1 if there was an error, 0 if not.
}

int execute_cmd(char *command){ // execute user input as a command

    if (strlen(command)){ // check if the input is not empty
        char command_path[]="/bin/";
        strcat(command_path, command);
        execlp(command_path, command, (char *)NULL);
        // in case the execution fails
        perror("Error executing command");
        exit(EXIT_FAILURE);
    }
    else{
        exit(EXIT_SUCCESS); // the case of an empty command : input = ""
    }
}

int main() {
    char command[INPUT_SIZE];

    // show welcome message
    display_welcome();
    while (1) {
        // show prompt message
        display_prompt();

        // "command" receives user input and make sure there is no input error
        int input_error = readCommand(command);
        
        // exit if the user types 'exit' or in case of input error
        if (input_error || strcmp(command, "exit") == 0) {
            if (input_error){
                disp_NewLine();
            }
            enseash_exit();
            break;
        }


        // execute commands that take no arguments
        pid_t pid = fork();

        if (pid == -1) {
            perror("Error forking process");
            exit(EXIT_FAILURE);
        }
        
        else if (pid == 0) {
            // child process
            execute_cmd(command);
            /*
            execution of the command :
            -exits with EXIT_FAILURE if it failed
            -exits with EXIT_SUCCESS if the input was empty : command = ""
            */
        }
        
        else {
            // parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}