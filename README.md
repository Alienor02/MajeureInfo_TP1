# Lab Report for TPSP1 : ENSEASH Shell

## Overview
This project, titled ENSEASH Shell, is a simple shell implementation developed in C. The shell is designed to execute commands, provide information about their execution, and support various features such as command execution with arguments, exit status display, time measurement, and more.

## Project Structure
The project consists of a single C file, `enseash.c`, implementing the ENSEASH Shell. The code is organized, commented and divided into functions to enhance readability. At the end of the 2nd lab, the main components include:

- **disp_NewLine():** Writes a new line character to the shell.
- **display_welcome():** Displays a welcome message upon launching the shell.
- **display_prompt():** Generates and displays the prompt, including exit status, signal, and execution time.
- **enseash_exit():** Displays a goodbye message when exiting the shell.
- **readCommand():** Reads user input, ensuring no errors occur, and handles the exit command.
- **execute_cmd():** Executes the entered command, capturing information such as exit status and execution time.

## Features
The ENSEASH Shell supports various features as required by the lab specifications:

1. **Welcome Message and Prompt:** Displays a welcome message and provides a user-friendly prompt.

2. **Command Execution:** Executes simple commands entered by the user and returns to the prompt.

3. **Exiting the Shell:** Allows the user to exit the shell by typing 'exit' or using `<Ctrl>+D`.

4. **Displaying Command Status:** Shows the exit code or signal of the previous command in the prompt.

5. **Measuring Command Execution Time:** Utilizes `clock_gettime` to measure the execution time of commands.

6. **Executing Complex Commands:** Handles commands with arguments seamlessly.


These were the features we could implement in time. We couldn't manage to finalize our project at the end of the last lab. The project specifications expected more options, such as :
- **Redirections with `<` and `>`:** Manages input and output redirection.
- **Pipe Redirection with `|`:** Implements pipe redirection to connect the output of one command to the input of another.
- **Running Commands in the Background with `&`:** Supports running commands in the background, displaying immediate prompts.
