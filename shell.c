#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char **environ;
int counter = 0;

int main() {
    
    //Initializes the parent/child process id variable (when we first run fork on this variable,
    //it will refer to the parent. Then, the function will rerun with c_pid variable as the 
    //child process.)
    int c_pid;
    
    //initializes the status variable, which will be used later for when the parent process has
    //to wait for the child process to be done executing
    int status;

    
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];

    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    
   // printf("String is %s \n" , "Here");
    while (true) {
        // Print the shell prompt.
        printf("%s", prompt);
        fflush(stdout);
        
        // Read input from stdin and store it in command_line. If there's an
        // error, exit immediately. (If you want to learn more about this line,
        // you can Google "man fgets")
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
        
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }
        
        

      
        int counter = 0;
        char *str;
        int i;
        
        // TODO:
        // 1. Tokenize the command line input (split it on whitespace)
        // SO, line 66 assigns 'str' the tokenized input, based off of delimeters, which in this case is a space(" ") 
        str = strtok(command_line, delimiters);

        // This while loop iterates throughout the parsed string, and adds each token to our array 'arguments', until 
        // the str has been fully iterated through.
        while(str != NULL) {
            arguments[counter] = str;
            str = strtok(NULL, delimiters);
            counter++;
        }
 
        
        // SO, this will call the fork function, which will return twice. The first 'c_pid' will reference the parent process, 
        // and the second 'c_pid' will be the child process
        c_pid = fork();
        
        //Conditional for the child process
        if(c_pid == 0) {  
           printf("Child: I'm the child: %d/n", c_pid);
            
            // 2. Create a child process which will execute the command line input
            //SO, the 'execve' function executes the first element within the parsed input 
           execve(arguments[0], arguments, environ);
        }
        
        //Conditional for the parent process
        else if (c_pid > 0) {         
            printf("Parent: I'm the parent: %d/n", c_pid);
            
            // 3. The parent process should wait for the child to complete
            // SO, the wait function passes in an integer pointer (&status), which points to the
            // memory of the previously initiated status variable
            // 
            // The parent process is waiting for the child process to terminate, which will
            // provoke the status change that the parent is looking for.
            wait(&status);
        }
    }
    
    // This should never be reached.
    return -1;
}
