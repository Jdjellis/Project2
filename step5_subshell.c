#include "myshell.h"

int subshell(SHELLCMD *t) 
{
    int ex;
    ex = execute_shellcmd(t);
    return ex;
}

int command(SHELLCMD *t)
{
    int ex = execute_args(t->argc, t->argv);
    return ex;
}

int exec_fork(SHELLCMD *t)
{
	int ex;
	int status;
    pid_t pid = fork();

    /* Spawn a child to run the program. */
    if (pid == -1) 
    {
        function_error("fork()", pid);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)  // Child process
    {
        switch(t->type)
        {
            case CMD_SUBSHELL :
                file_redirection(t);
                ex = subshell(t->left);

            case CMD_COMMAND :
                file_redirection(t);
                ex = command(t);

            default:
                ex = EXIT_FAILURE;
        }
        exit(ex);
    }
    else                // Parent process
    {
        wait(&status);  // wait for child to exit
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
