#include "shell.h"
/**
 * interactive - Function handles interactive shell
 * @argv: Pointer to array of args passed to the program
 * @env: Pointer to array containing environment variables
 * Return: Nothing
 */
int interactive(char **argv, char **env)
{
	char *lineptr, *strcpy;
	int line, same, _env, status;
	size_t size;

	lineptr = NULL;
	size = 0;
	while (1)
	{
		dprintf(STDOUT_FILENO, "%s", "$ ");
		line = getline(&lineptr, &size, stdin);
		if (line == 1)
			continue;
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
				free(lineptr), exit(0);
			}
			else if (_env == 0)
			{
				printenv(env);
				continue;
			}
			status = create_child(argv, env);
		}
		else if (line == EOF)
			free(lineptr), exit(0);
	}
	return (status);
}
