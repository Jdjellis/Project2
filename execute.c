#include "myshell.h"

/*
   CITS2002 Project 2 2017
   Name(s):		student-name1 (, student-name2)
   Student number(s):	student-number-1 (, student-number-2)
   Date:		date-of-submission
 */

// -------------------------------------------------------------------

//  THIS FUNCTION SHOULD TRAVERSE THE COMMAND-TREE and EXECUTE THE COMMANDS
//  THAT IT HOLDS, RETURNING THE APPROPRIATE EXIT-STATUS.
//  READ print_shellcmd0() IN globals.c TO SEE HOW TO TRAVERSE THE COMMAND-TREE

int execute_args(int argcount, char *argv[]) 
{
    int ex;

    // Check to see if function was an internal function
    ex = search_internal(argcount, argv);
    if(ex == NOT_FOUND) 
    {
        // Check to see if it was an external function
        ex = search_external(argv);
    }
    if (ex != EXIT_SUCCESS)
    {
        function_error(argv[0], ex);
        ex = EXIT_FAILURE;
    }
    return ex;
}

int execute_shellcmd(SHELLCMD *t)
{
    int  exitstatus;

    if (t == NULL) {			// hmmmm, that's a problem
	   exitstatus	= EXIT_FAILURE;
    }
    else {				// normal, exit commands
        switch (t->type) 
        {
        case CMD_COMMAND :
            if (t->infile == NULL && t->outfile == NULL)
            {
                exitstatus = execute_args(t->argc, t->argv);
            }
            else
            {
                exitstatus = exec_fork(t);
            }
            break;

        case CMD_SEMICOLON :
            execute_shellcmd(t->left); 
            exitstatus = execute_shellcmd(t->right);
            break;

        case CMD_AND :
            exitstatus = execute_shellcmd(t->left);
            if (exitstatus == EXIT_SUCCESS)
            {
                exitstatus = execute_shellcmd(t->right);
            }
            break;

        case CMD_OR :
            exitstatus = execute_shellcmd(t->left);
            if (exitstatus == EXIT_FAILURE)
            {
                exitstatus = execute_shellcmd(t->right);
            }
            break;

        case CMD_SUBSHELL :
            exitstatus = exec_fork(t);
            break;

        case CMD_PIPE :
            exitstatus = exec_pipe(t);
            break;

        /*case CMD_BACKGROUND :
            print_shellcmd0(t->left); printf("& "); print_shellcmd0(t->right);
            break;*/

        default :
            fprintf(stderr, "%s: invalid CMDTYPE in execute_shellcmd()\n", argv0);
            exit(EXIT_FAILURE);
            break;
        }
    }
    return exitstatus;
}
