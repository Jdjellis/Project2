#include "myshell.h"

int pipe_setup(int fd[], int feed)
{
	int ex;
	if((ex = dup2(fd[feed], feed)) == -1)
	{
		function_error("close STDOUT", EXIT_FAILURE);
	}
	return ex;
}

int exec_pipe(SHELLCMD *t)
{
	//SET UP PIPE
	int fd[2];
	pipe(fd);

	int ex;
	int status;


    pid_t c1pid;
    pid_t c2pid;

    c1pid = fork();

    /* Spawn a child to run the program. */
    if (c1pid == -1) 
    {
        function_error("fork()", c1pid);
        exit(EXIT_FAILURE);
    }
    else if (c1pid == 0)
    {
    	c2pid = fork();

    	if(c2pid == -1)
	    {
	        function_error("fork()", c2pid);
	        exit(EXIT_FAILURE);
	    }
	    else if (c2pid == 0)
	    {
	    	// CHILD PROCESS 2 (left-most branch)
	    	// set up stdout to be pipe
	    	printf("STDOUT_FILENO: %i\n", STDOUT_FILENO);
	    	ex = pipe_setup(fd, STDOUT_FILENO);
	    	ex = execute_shellcmd(t->left);
	    	exit(ex);
	    }

	    else
	    {
	    	// CHILD PROCESS 1 (right-most branch)
	    	wait(&status); // wait for child process 2 to finish
	    	if (status == 0)
	        {
	        	ex = pipe_setup(fd, STDIN_FILENO);
	        	ex = execute_shellcmd(t->right);
	        }
	        else
	        {
	            ex = EXIT_FAILURE;
	        }
	        exit(ex);
	    }
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
