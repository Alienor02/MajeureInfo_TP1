
/*
QUESTION 1 :
Display a welcome message, followed by a simple prompt. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INPUT_SIZE 200


//function to display a welcome message
void display_welcome() {
    const char welcome_message[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    write(STDOUT_FILENO, welcome_message, sizeof(welcome_message) - 1);
}

//function to display a prompt message
void display_prompt() {
    const char prompt_message[] = "enseash %% ";
    write(STDOUT_FILENO, prompt_message, sizeof(prompt_message) - 1);
}

//function to display an exit message (for a future version)
void enseash_exit() {
    const char goodbye_message[] = "Au revoir !\n";
    write(STDOUT_FILENO, goodbye_message, sizeof(goodbye_message) - 1);
}


int main() {
    char input[INPUT_SIZE];

    display_welcome();
    while (1) {
        display_prompt();

        // read user input
        fgets(input, sizeof(input), stdin);
    }

    return 0;
}
