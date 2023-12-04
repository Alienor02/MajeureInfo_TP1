
/*
QUESTION 5 :
Measurement of the command execution time using the call clock_gettime.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <bits/time.h>


#define INPUT_SIZE 1000
#define STATUS_MESSAGE_SIZE 64


// function to display a welcome message
void display_welcome() {
    const char welcome_message[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    write(STDOUT_FILENO, welcome_message, sizeof(welcome_message) - 1);
}

// function to display a prompt message with the signal or code associated
void display_prompt(int code, int signal, long int time) {
    char prompt_message[50];
    if (code != -1){ // case of an exit
        sprintf(prompt_message, "enseash [exit:%d|%ldms] %% ", code, time);  
    }
    else if (signal != -1){ // case of an interruption by a signal
        sprintf(prompt_message, "enseash [sign:%d|%ldms] %% ", signal, time);
    }
    else { // case without exit or interruption 
        sprintf(prompt_message, "enseash %% ");
    }
    write(STDOUT_FILENO, prompt_message, strlen(prompt_message));

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

//
void execute_cmd(char *command){
    struct timespec startTime, endTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime); // Record start time
    pid_t pid = fork();
    if(pid==0){
    // Child process
    if (strlen(command)){ // check if the input is not empty
        char command_path[]="/bin/";
        strcat(command_path, command);
        execlp(command_path, command, (char *)NULL);

        // in case the execution fails
        perror("Error executing command");
        exit(EXIT_FAILURE);
        }
        display_prompt(-1, -1, 0);
        exit(EXIT_SUCCESS); // the case of an empty command : input = ""
    }
    else{
        // Parent process        
        int status;

        waitpid(pid, &status, 0);
            
        clock_gettime(CLOCK_MONOTONIC, &endTime); // Record end time
        long int execution_time = (endTime.tv_sec - startTime.tv_sec) * 1000 + (endTime.tv_nsec - startTime.tv_nsec) / 1000000;

        // show prompt message with EXITSTATUS or SIGNAL, ready for next input
        if (strlen(command)) { // the case of an empty command has already been handled previously

            display_prompt(WEXITSTATUS(status), WTERMSIG(status), execution_time);
            }
        }
}


int main(){
    char command[INPUT_SIZE];
    display_welcome();
    display_prompt(-1, -1, 0);

    while(1){
        
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
        execute_cmd(command); 
    }
    return 0;
}
