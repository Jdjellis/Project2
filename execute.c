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

int execute_shellcmd(SHELLCMD *t)
{
    int  exitstatus;
    int found;

    if (t == NULL) {			// hmmmm, that's a problem
	exitstatus	= EXIT_FAILURE;
    }
    else {				// normal, exit commands
        switch (t->type) {
        case CMD_COMMAND :
            found = search_internal(t->argv);
            //check to see if function was an internal function
            if(found != 0) {
                found = search_external(t->argv);
                // Check to see if it was an external function
                if(found != 0) {
                    // shell script
                }
                break;
            }
            else {
                break;
            }

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
