Installation: 
Open command prompt
Navigate to folder containing program files (make, .c, .h)
Enter 'make' to compile the program
Enter './shell' to run program
After usage enter 'make clean' to remove program


Purpose: The purpose of myshell.c is to create a shell using fork() and execvp() that executes commands taken in from the user and processed with parse.c

Usage: After executing the program, the following prompt will appear: "$$$ ". This is where the user enters a string. The string should be composed of words separated by spaces. If a '<' is used, this indicates an input redirection. If a '>' is used, this indicates an output redirection. There must not be a space after the '<' or '>'. Any other words will be stored as arguments in the argumentVector array within the PARAM struct. To run a process in the background, the user must include '&' as the LAST token in the string. If the ampersand character is included in the string but is not the last character or a space is entered after a redirect symbol, you will be prompted to re-enter your command. After entering the string, a process will be forked and executed using execvp. You will then be prompted to enter a new string. To exit the program, please type the string 'exit'.
