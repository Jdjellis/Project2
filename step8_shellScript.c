#include "myshell.h"

int exec_shellscript(char *cmd)
{
	int ex;
    int status;
    pid_t pid = fork();
    printf("yay\n");

    FILE *fp = fopen(cmd, "r");
    /* Spawn a child to run the program. */
    if (pid == -1) 
    {
        function_error(cmd, pid);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // Child process
    {
    	stdin = fp;
        char *myshellpath = "/Users/Josh/Documents/__Study/Uni/CITS2002/Project/master/myshell";
        execv(myshellpath, NULL);
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
