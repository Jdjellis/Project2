#include "myshell.h"

void searchPath(char *argv[]) 
{
	char *plist = strdup(PATH);
	char *pch;

	char* arg0 = argv[0];

	int arglen = strlen(arg0);
	int pathlen;
	int result;

    // Check if arg0 contains a slash character. Otherwise, search in PATH variable
    if (strchr(arg0, '/') !=NULL)
    {
        exec_process(arg0, argv);
    }
	else 
	{
		pch = strtok(plist,":");
		while (pch != NULL && result != 0)
		{
			pathlen = strlen(pch) + arglen + 2;
			char cmd[pathlen];
			strncpy(cmd, pch, pathlen);
			strcat(cmd, "/");
			strncat(cmd, arg0, arglen);

			result = exec_process(cmd, argv);

			pch = strtok(NULL, ":");
		}
		if (result != 0) {
			functionError(arg0);
		}
	}
}
