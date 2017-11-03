#include "myshell.h"

int search_external(char *argv[]) 
{
	char *plist = strdup(PATH);
	char *pch;
	char *cmd;

	int arglen = strlen(argv[0]);
	int found;
	int ex; // returned variable

    // Check if argv[0] contains a slash character. Otherwise, search in PATH variable
    if (strchr(argv[0], '/') !=NULL)
    {
        ex = exec_external(argv[0], argv);
        ex = exec_shellscript(argv[0]);
    }
	else 
	{
		pch = strtok(plist,":");
		while (pch != NULL && found != 0)
		{
			cmd = path_append(pch, argv[0], arglen);

			found = access(cmd, F_OK);

			free(cmd);
			pch = strtok(NULL, ":");
		}

		if (found == 0) {
			ex = exec_external(cmd, argv);
			if (ex!= 0) {
				ex = exec_shellscript(cmd);
			}
		}
		else
		{
			ex = EXIT_FAILURE;
		}
	}
	return ex;
}
