#include"main.h"

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
	int i, len;
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

