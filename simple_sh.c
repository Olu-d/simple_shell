#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
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
	if (!isatty(STDIN_FILENO))
		non_interactive(argv, env);
	else
	{
		interactive(argv, env);
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
			perror(prog_name);
			exit(2);
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
