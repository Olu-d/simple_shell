#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * main - This program creates a simple shell.
 * @argc: Number of arguments passed to our main function.
 * @argv: A pointer to an array of strings that holds our arguments.
 * @env: Points to the environment variables
 *
 * Description: Program creates a simple shell.
 *
 * Return: 0 if OK.
 */
int main(int argc, char *argv[], char **env)
{
	char *lineptr;
	pid_t child;
	ssize_t n, line;
	int delim, res, status;
	char *com;

	lineptr = malloc(sizeof(char));
	n = 1;

	while (n)
	{
		child = fork();
		if (child < 0)
		{
			dprintf(STDOUT_FILENO, "Failed to create child process\n");
			exit(99);
		}
		else if (child == 0)
		{
			printf("cisfun#");
			com = "/usr/bin/ls";
			execve(com, argv, NULL);
			line = getline(&lineptr, &n, stdin);
			if (line != -1)
			{
				com = "/usr/bin/ls";
				printf("%s\n", lineptr);
				res = execve(lineptr, argv, env);
				if (res == -1)
					printf("Command %s not found", lineptr);
			}
		}
		else
			wait(&status);
	}
	free(lineptr);
}
