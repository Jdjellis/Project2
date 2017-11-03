#include "myshell.h"

int exec_shellscript(char *cmd)
{
	int ex;
    int status;
    pid_t pid = fork();

    FILE *fp = fopen(cmd, "r");
    int fd = fileno(fp);

    char * args[2];
    args[0] = MYSHELLPATH;
    args[1] = NULL;

    /* Spawn a child to run the program. */
    if (pid == -1) 
    {
        function_error(cmd, pid);
        ex = EXIT_FAILURE;
    }
    else if (pid == 0) // Child process
    {

        if((ex = dup2(fd, STDIN_FILENO)) == -1)
        {
            //function_error("shell script", EXIT_FAILURE);
            fprintf(stderr, "STDIN REPLACEMENT FAILED", EXIT_FAILURE);
            exit(ex);
        }

        if ((access(MYSHELLPATH, F_OK)) == -1)
        {
            fprintf(stderr, "Couldn't find myshell executable: %s\n", MYSHELLPATH);
            exit(EXIT_FAILURE);
        }
        else
        {
            execv(MYSHELLPATH, args);
            exit(EXIT_FAILURE);
        }
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
    }
    return ex;
}
