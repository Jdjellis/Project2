#include "myshell.h"

int subshell(SHELLCMD *t)
{
	int ex;
	int status;
    pid_t pid = fork();

    /* Spawn a child to run the program. */
    if (pid == -1) 
    {
        function_error("subshell", pid);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // Child process
    {
        ex = execute_shellcmd(t);
        exit(ex);
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
