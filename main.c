#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

int main(void)
{
	char command[256] = "\0";

	while (1) {
		strcpy(command, "\0");
		printf("maiterm > ");
		fgets(command, sizeof(command), stdin);
		remove_substring(command, "\n");

		if (strcmp(command, "exit") == 0)
			break;

		printf("exit %d\n", exec_command(command));
	}

	_exit(0);
}

pid_t exec_command(char *command)
{
	int waitforpid = strstr(command, " &") == NULL;

	if (!waitforpid)
		remove_substring(command, " &");
	printf("command: %s\n", command);

	pid_t pID = fork();
	int status = 0;

	if (pID == 0) {
		int res = execvp(command, (char *[]){ command, NULL });

		if (res == -1)
			printf("command not found\n");

	} else if (pID < 0) {
		printf("Failed to fork\n");
		_exit(1);
	} else {
		if (waitforpid)
			waitpid(pID, &status, 0);
	}

	return pID;
}

void remove_substring(char *s, const char *toremove)
{
	s = strstr(s, toremove);
	memmove(s, s+strlen(toremove), 1+strlen(s+strlen(toremove)));
}
