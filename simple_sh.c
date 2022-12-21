#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char *get_commands(char [], char **);
void create_child(char **argv, char *envp[], char *prog_name);
size_t getlen(char []);
void printenv(char **);
/**
 * main - Function creates a simple interactive shell.
 * @argc: Variable holding the number of args passed to the main function.
 * @argv: A pointer to an array of strings(the arguments passed to the
 * function.
 * @env: Pointer to array holding system's environment variables.
 *
 * Description: Function creates a simple interactive shell.
 *
 * Return: 0 if successful.
 */
int main(__attribute__((unused)) int argc, char *argv[], char *env[])
{
	size_t size;
	int line, same, _env;
	static char *prog_name;
	char *lineptr, *strcpy;

	prog_name = argv[0];
	size = 0;
	lineptr = NULL;
	while (1)
	{
		dprintf(STDOUT_FILENO, "%s", "$ ");
		line = getline(&lineptr, &size, stdin);
		if (line == 1)
		{
			continue;
		}
		else if (line != -1)
		{
			strcpy = get_commands(lineptr, argv);
			if (argv[0] == NULL)
				continue;
			same = strcmp(argv[0], "exit");
			_env = strcmp(argv[0], "env");
			if (same == 0)
			{
				free(strcpy);
				free(lineptr);
				exit(0);
			}
			else if (_env == 0)
			{
				printenv(env);
				continue;
			}
			create_child(argv, env, prog_name);
		}
		else if (line == EOF)
		{
			dprintf(STDOUT_FILENO, "\n");
			free(lineptr);
			exit(0);
		}
		else
			continue;
	}
	if (strcpy != NULL)
		free(strcpy);
	if (lineptr != NULL)
		free(lineptr);
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
char *get_commands(char str[], char **argv)
{
	int i, len;
	size_t strlen;
	static char *strcopy;

	len = 0;
	strlen = (getlen(str));
	strlen++;
	strcopy = malloc(sizeof(char) * strlen);
	if (strcopy == NULL)
		exit(1);
	while (str[len] != '\0')
	{
		if (str[len] == '\t' || str[len] == '\n')
		{
			strcopy[len] = ' ';
		}
		else
		{
			strcopy[len] = str[len];
		}
		len++;
	}
	strcopy[len] = '\0';
	i = 0;
	argv[i] = strtok(strcopy, " ");
	while (argv[i] != NULL)
	{
		i++;
		argv[i] = strtok(NULL, " ");
	}
	return (strcopy);
}
/**
 * create_child - Function forks a child process and executes command fed via
 * argv.
 * @argv: Pointer to array containing strings of commands.
 * @env: Pointer to array containing the system's environmnetal variables.
 * @prog_name: The name of the calling program.
 * Description: Function forks a child process and executes command fed via
 * argv.
 * Return: Nothing.
 */
void create_child(char **argv, char **env, char *prog_name)
{
	pid_t child, stat;
	int status, exec_status, len;

	len = 0;
	stat = -1;
	child = fork();
	if (child < 0)
	{
		dprintf(STDOUT_FILENO, "Error: Unable to create child process\n");
		exit(99);
	}
	else if (child == 0)
	{
		exec_status = execve(*argv, argv, env);
		if (exec_status == -1)
		{
			while (argv[len] != NULL)
				len++;
			dprintf(STDOUT_FILENO, "%s: %d: %s: not found\n", prog_name, len, *argv);
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
/**
 * printenv - Function prints the environment variables.
 * @env: Pointer to the array containing the environment variables.
 *
 * Description: Function prints the environment variables.
 *
 * Return: Nothing.
 */
void printenv(char **env)
{
	int len;

	len = 0;
	while (env[len] != NULL)
	{
		dprintf(STDOUT_FILENO, "%s\n", env[len]);
		len++;
	}
}
