#include "myshell.h"

int search_external(char *argv[]) 
{
	char *plist = strdup(PATH);
	char *pch;
	char *cmd;

	int arglen = strlen(argv[0]);
	int result;
	int ex; // returned variable

    // Check if argv[0] contains a slash character. Otherwise, search in PATH variable
    if (strchr(argv[0], '/') !=NULL)
    {
        ex = exec_external(argv[0], argv);
    }
	else 
	{
		pch = strtok(plist,":");
		while (pch != NULL && result != 0)
		{
			cmd = path_append(pch, argv[0], arglen);

			result = exec_external(cmd, argv);

			free(cmd);
			pch = strtok(NULL, ":");
		}
		if (result != 0) {
			ex = EXIT_FAILURE;
		}
		else {
			ex = EXIT_SUCCESS;
		}
	}
	return ex;
}
