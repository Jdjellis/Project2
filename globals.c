#include "myshell.h"

/*
   CITS2002 Project 2 2017
   Name(s):             student-name1 (, student-name2)
   Student number(s):   student-number-1 (, student-number-2)
   Date:                date-of-submission
 */

//  THREE INTERNAL VARIABLES (SEE myshell.h FOR EXPLANATION)
char	*HOME, *PATH, *CDPATH;

char	*argv0		= NULL;		// the program's name
bool	interactive	= false;

// ADDITIONAL GLOBAL VARIABLES
char *internal_func[] = {"exit", "cd", "time", NULL};
int exitstatus;

// ------------------------------------------------------------------------

// Called when argument not found as a external program, internal program, or shell script

char *path_append(char *pch, char *arg, int arglen)
{
	int pathlen = strlen(pch);
	int cmdlen = pathlen + arglen + 2; // extra room for '/' and '/n'
	char *cmd = malloc(cmdlen * sizeof(char)); // an array large enough for the path + program name

	if (cmd != NULL)
	{
		// Build the command
		sprintf(cmd, "%s/%s", pch, arg);
	}

	return cmd;
}

void function_error(char *func, int type)
{
	if (type == NOT_FOUND)
	{
		fprintf(stderr, "-%s: %s: command not found\n", argv0, func);	
	}
	else if (type == -1)
	{
		perror(NULL);
	}
	else
	{
		fprintf(stderr, "-%s: %s: command failed\n", argv0, func);
	}
	
}

void check_allocation0(void *p, char *file, const char *func, int line)
{
    if(p == NULL) {
	fprintf(stderr, "%s, %s() line %i: unable to allocate memory\n",
			file, func, line);
	exit(2);
    }
}

static void print_redirection(SHELLCMD *t)
{
    if(t->infile != NULL)
	printf("< %s ", t->infile);
    if(t->outfile != NULL) {
	if(t->append == false)
	    printf(">");
	else
	    printf(">>");
	printf(" %s ", t->outfile);
    }
}

void print_shellcmd0(SHELLCMD *t)
{
    if(t == NULL) {
	printf("<nullcmd> ");
	return;
    }

    switch (t->type) {
    case CMD_COMMAND :
	for(int a=0 ; a<t->argc ; a++)
	    printf("%s ", t->argv[a]);
	print_redirection(t);
	break;

    case CMD_SEMICOLON :
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
	break;

    default :
	fprintf(stderr, "%s: invalid CMDTYPE in print_shellcmd0()\n", argv0);
	exit(EXIT_FAILURE);
	break;
    }
}
