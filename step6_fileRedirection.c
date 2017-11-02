#include "myshell.h"

void file_redirection(SHELLCMD *t) 
{
	int filein;
	int fileout;

	if (t->infile)
	{
		if((filein = open(t->infile,O_RDONLY)) == -1)
		{
			function_error("open filein", EXIT_FAILURE);
		}
		else 
		{
			if(dup2(filein, STDIN_FILENO) == -1)
			{
				function_error("dup2 filein", EXIT_FAILURE);
			}
			if(close(filein) == -1)
			{
				function_error("close filein", EXIT_FAILURE);
			}
		}
	}

	if (t->outfile)
	{
		if(t->append) 
		{
			fileout = open(t->outfile, O_WRONLY | O_CREAT);
		}
		else
		{
			fileout = open(t->outfile, O_WRONLY | O_CREAT | O_APPEND);	
		}
		if (fileout == -1)
		{
			function_error("open fileout", EXIT_FAILURE);
		}
		else
		{
			if(dup2(fileout, STDOUT_FILENO) == -1)
			{
				function_error("dup2 fileout", EXIT_FAILURE);
			}
			if(close(fileout) == -1)
			{
				function_error("close fileout", EXIT_FAILURE);
			}
		}
	}	
}
