#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void get_commands(char [], char **);
void create_child(char **argv, char *envp[]);
/**
 * main - Function creates a simple interactive shell.
 * @argc: Variable holding the number of args passed to the main function.
 * @argv: A pointer to an array of strings(the arguments passed to the function.
 *
 * Description: Function creates a simple interactive shell.
 */
int main(int argc, char *argv[], char *envp[])
{
	pid_t child;
	size_t line, size;
	int status;
	char *coms, *lineptr;

	size = 0;
	lineptr = NULL;
	while (1)
	{
		
		dprintf(STDOUT_FILENO, "%s", "cisfun$");
		line = getline(&lineptr, &size, stdin);
		if (line == -1)
			dprintf(STDOUT_FILENO, "Unable to get line\n"), exit(1);
		get_commands(lineptr, argv);
		create_child(argv, envp);
	}
	return (0);
}
/**
 * get_commands - Function breaks down user input into individual commands.
 * @str: Array holding the user input string.
 * @argv: Pointer to array to be passed to execve.
 *
 * Description: Function breaks down user input into individual tokens.
 *
 * Return: A pointer to an array containing the individual commands.
 */
void get_commands(char str[], char **argv)
{
	int i, j;

	i = 1;
	argv[0] = strtok(str, " ");
	while (argv[i] != NULL)
	{	
		argv[i] = strtok(NULL, " ");
		i++;
	}
	argv[i] = '\0';
}
/**
 * create_child - Function forks a child process and executes command fed via argv
 * @argv: Pointer to array containing strings of commands.
 *
 * Description: Function forks a child process and executes command fed via argv.
 * Return: Nothing.
 */
void create_child(char **argv, char **envp)
{
	pid_t child;
	int status, exec_status;
	char *com;

	child = fork();
	if (child < 0)
	{
		dprintf(STDOUT_FILENO, "Error: Unable to create child process\n");
		exit(99);
	}
	else if (child == 0)
	{
		exec_status = execve(*argv, argv, envp);
		if (exec_status == -1)
			dprintf(STDOUT_FILENO, "Error: exec failed\n"), exit(100);
	}
	else
		while (wait(&status) != child);
}
