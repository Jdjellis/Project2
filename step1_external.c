#include "myshell.h"

int exec_external(char *cmd, char *argv[])
{
    int ex;
    int status;
    pid_t pid = fork();

    /* Spawn a child to run the program. */
    if (pid == -1) 
    {
        function_error(argv[0], pid);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // Child process
    {
        execv(cmd, argv);
        exit(EXIT_FAILURE);
    }
    else 
    {
        wait(&status); // wait for child to exit
        if (status == 0)
        {
            ex = EXIT_SUCCESS;
        }
        else
        {
            ex = EXIT_FAILURE;
        }
        return ex;
    }
}

