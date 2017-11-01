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
    //printf("argcount: %i, argv: %s\n", argcount, argv[0]);
    //printf("searching for internal: %s\n", argv[0]);
    ex = search_internal(argcount, argv);
    // check to see if function was an internal function
    if(ex == NOT_FOUND) 
    {
        //printf("searching for external: %s\n", argv[0]);
        ex = search_external(argv);
        // Check to see if it was an external function
        if(ex == NOT_FOUND) 
        {
            printf("searching for script\n");
            // shell script
        }
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
            exitstatus = execute_args(t->argc, t->argv);
            break;

        /*case CMD_SEMICOLON :
            print_shellcmd0(t->left); printf("; "); print_shellcmd0(t->right);
            break;

        case CMD_AND :
            print_shellcmd0(t->left); printf("&& "); print_shellcmd0(t->right);
            break;

        case CMD_OR :
            print_shellcmd0(t->left); printf("|| "); print_shellcmd0(t->right);
            break;

        case CMD_SUBSHELL :
            printf("( "); print_shellcmd0(t->left); printf(") ");
            print_redirection(t);
            break;

        case CMD_PIPE :
            print_shellcmd0(t->left); printf("| "); print_shellcmd0(t->right);
            break;

        case CMD_BACKGROUND :
            print_shellcmd0(t->left); printf("& "); print_shellcmd0(t->right);
            break;*/

        default :
            fprintf(stderr, "%s: invalid CMDTYPE in print_shellcmd0()\n", argv0);
            exit(EXIT_FAILURE);
            break;
        }
        
        exitstatus	= EXIT_SUCCESS;
    }

    return exitstatus;
}
