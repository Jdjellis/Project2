#include "myshell.h"


int run_exit(int argcount, char *argv[])
{
	if (argcount == 1)
	{
		exit(exitstatus);
	}
	else // need to check if digits and report error if not
	{
		exit(atoi(argv[1]));
	}
	
	return EXIT_FAILURE;
}

int run_cd(int argcount, char *argv[]) 
{
	int ex;
	int arglen;
	int result = EXIT_FAILURE;

	char *plist = strdup(CDPATH);
	char *pch;
	char *cmd;

	
	if (argcount == 1)
	{
		result = chdir(HOME);

	}
	else
	{
		if (argv[1][0] == '/')
		{
			result = chdir(argv[1]);
		}
		else
		{
			arglen = strlen(argv[1]);
			pch = strtok(plist,":");
			while (pch != NULL && result != 0)
			{
				cmd = path_append(pch, argv[1], arglen);

				result = chdir(cmd);

				free(cmd);

				pch = strtok(NULL, ":");
			}
		}
	}

	if (result != 0) {
		ex = EXIT_FAILURE;
	}
	else {
		ex = EXIT_SUCCESS;
	}
	return ex;
}

int run_time(int argcount, char *argv[])
{
	argv++;
	argcount--;
	int ex;
	int result;

	struct timeval tv1;
	struct timeval tv2;
	struct timeval res;

	result = gettimeofday(&tv1, NULL);

	if (result == 0)
	{
		execute_args(argcount, argv);
		result = gettimeofday(&tv2, NULL);
		if (result == 0)
		{
			timersub(&tv2, &tv1, &res);
			printf("command '%s' took %dms\n", argv[0], res.tv_usec/1000);
		}
	}
	
	if (result != 0)
	{
		function_error(argv[-1], result);
		ex = EXIT_FAILURE;
	}
	else 
	{
		ex = EXIT_SUCCESS;
	}

	return ex;
}

int exec_internal(int icmd, int argcount, char *argv[]) 
{
	int ex;

	switch (icmd) 
	{
		/*------------------------------------------------------------------------------*/
		//exit
		case 0:
		{
			ex = run_exit(argcount, argv);
			break;
		}

		/*------------------------------------------------------------------------------*/
		// cd
		case 1:
		{
			ex = run_cd(argcount, argv);
			break;
		}

		/*------------------------------------------------------------------------------*/
		// time
		case 2:
		{	
			ex = run_time(argcount, argv);
			break;
		}
		/*------------------------------------------------------------------------------*/
		default:
			ex = NOT_FOUND;
			break;
	}
	return ex;
}

int search_internal(int argcount, char *argv[])
{
	int ex;
	//int arglen = strlen(argv[0]);

	int icmd = NOT_FOUND; //function index
	for (int i = 0; internal_func[i]; i++) {
		if (strcmp(internal_func[i], argv[0]) == 0)
		{
			icmd = i;			// index of the command in the internal commands array
			break;
		}
	}

	ex = exec_internal(icmd, argcount, argv);

	return ex;
}

