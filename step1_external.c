#include "myshell.h"

int exec_process(char *arg0, char *argv[])
{
    int status;
    pid_t pid = fork();

    /* Spawn a child to run the program. */
    if (pid == -1) {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // Child process
    {
        execv(arg0, argv);  
        exit(EXIT_FAILURE);
    }
    else {
        wait(&status); // wait for child to exit
        return status;
    }
}

