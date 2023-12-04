
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
#define command_path "/bin/"

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


int main() {
    char input[INPUT_SIZE];

    // show welcome message
    display_welcome();
    while (1) {
        // show prompt message
        display_prompt();

        // read user input
        char* input_error = fgets(input, sizeof(input), stdin);
        // making sure the user input is correct

        // remove the newline char at the end of the input
        input[strcspn(input, "\n")] = '\0';

        // exit if the user types 'exit' or in case of input error
        if (input_error == NULL || strcmp(input, "exit") == 0) {
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
            if (strlen(input)){
                strcat(command_path, input);
                int exec_error = execlp(command_path, input, (char *)NULL);
                if (exec_error == -1) {
                    perror("Error executing command");
                    exit(EXIT_FAILURE);
                }
                // the case execlp fails
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS); // the case of an empty command : input = ""
        }
        
        else {
            // parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}