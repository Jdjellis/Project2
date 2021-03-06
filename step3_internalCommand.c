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
	int result = 0;

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
				printf("%s\n", cmd);

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

	struct timeval tv1;
	struct timeval tv2;

	ex = gettimeofday(&tv1, NULL);

	if (ex == 0)
	{
		exitstatus = execute_args(argcount, argv);
		if (ex == 0)
		{
			ex = gettimeofday(&tv2, NULL);
			if (ex == 0)
			{
				printf("command '%s' took %dms\n", argv[0], tv2.tv_usec-tv1.tv_usec);
				//printf("%i\n", ex);
			}
		}
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
			printf("%s\n", argv[0]);
			break;
		}
		/*------------------------------------------------------------------------------*/
		default:
			ex = EXIT_FAILURE;
			break;
	}
	return ex;
}

int search_internal(int argcount, char *argv[])
{
	int ex;
	//int arglen = strlen(argv[0]);

	int icmd = -1; //function index
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

