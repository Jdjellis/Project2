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

    /* Spawn a child to run the program. */
    c1pid = fork();

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
	    else if (c2pid == 0)	// CHILD PROCESS 2 (left-most branch)
	    {
	    	// set up stdout to be pipe
	    	close(fd[0]);
	    	
	    	if((ex = dup2(fd[1], STDOUT_FILENO)) == -1)
	    	{
	    		function_error("dup2 c2pid", EXIT_FAILURE);
	    	}
	    	else
	    	{
	    		ex = execute_shellcmd(t->left);
	    	}
	    	exit(ex);
	    }

	    else 	// CHILD PROCESS 1 (right-most branch)
	    {
	    	close(fd[1]);
        	if((ex = dup2(fd[0], STDIN_FILENO)) == -1)
	    	{
	    		function_error("dup2 c1pid", EXIT_FAILURE);
	    		exit(ex);
	    	}
	    	wait(&status); // wait for child process 2 to finish
	        	
	        if (status == 0)
        	{
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
        close(fd[1]);
        close(fd[0]);
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
