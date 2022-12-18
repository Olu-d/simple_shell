#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void get_commands(char [], char **);
void create_child(char **argv, char *envp[], char *prog_name);
size_t getlen(char []);
/**
 * main - Function creates a simple interactive shell.
 * @argc: Variable holding the number of args passed to the main function.
 * @argv: A pointer to an array of strings(the arguments passed to the
 * function.
 * @envp: Pointer to array holding system's environment variables.
 *
 * Description: Function creates a simple interactive shell.
 *
 * Return: 0 if successful.
 */
int main(int argc, char *argv[], char *envp[])
{
	pid_t child;
	size_t line, size;
	int status, same;
	static char *prog_name;
	char *lineptr;

	prog_name = argv[0];
	size = 0;
	lineptr = NULL;
	while (1)
	{
		dprintf(STDOUT_FILENO, "%s", "#cisfun$");
		line = getline(&lineptr, &size, stdin);
		if (line != -1)
		{
			get_commands(lineptr, argv);
			same = strcmp(argv[0], "exit");
			if (same == 0)
				exit(0);
			create_child(argv, envp, prog_name);
		}
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
	int i, j, len;
	size_t strlen;
	char *strcopy;

	len = 0;
	strlen = (getlen(str));
	strcopy = malloc(sizeof(char) * strlen);
	if (strcopy == NULL)
		exit(1);
	while (str[len] != '\0')
	{
		if (str[len] == '\t' || str[len] == '\n')
			strcopy[len] = ' ';
		else
			strcopy[len] = str[len];
		len++;
	}
	i = 0;
	argv[0] = strtok(strcopy, " ");
	while (argv[i] != NULL)
	{
		i++;
		argv[i] = strtok(NULL, " ");
	}
}
/**
 * create_child - Function forks a child process and executes command fed via
 * argv.
 * @argv: Pointer to array containing strings of commands.
 * @envp: Pointer to array containing the system's environmnetal variables.
 * @prog_name: The name of the calling program.
 * Description: Function forks a child process and executes command fed via
 * argv.
 * Return: Nothing.
 */
void create_child(char **argv, char **envp, char *prog_name)
{
	pid_t child, stat;
	int status, exec_status;

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
		{
			dprintf(STDOUT_FILENO, "%s: No such file or directory\n", prog_name);
			exit(100);
		}
	}
	else
	{
		while (stat != child)
			stat = wait(&status);

	}
}
/**
 * getlen - Function calculates the length of a given string.
 * @str: The string whose length we are to calculate.
 *
 * Description: Function calculates the length of a given string.
 * Return: The length of the string.
 */
size_t getlen(char str[])
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
		len++;

	return (len);
}