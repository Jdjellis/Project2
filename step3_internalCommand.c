#include "myshell.h"

void exec_internal(int ifunc, char *argv[]) 
{
	switch (id) 
	{
		case 0:
		// exit

		
		case 1:
		// cd

		case 2:
		// time
	}
}

int search_internal(char *argv[])
{
	int ex = EXIT_FAILURE;

	int ifunc = -1; //function index
	for (int i = 0; internal_func[i]; i++) {
		if (strcmp(internal_func[i], argv[0]) == 0)
		{
			ifunc = i;
			ex = EXIT_SUCCESS;
			break;
		}
	}

	exec_internal(ifunc, argv);

	return ex;
}

