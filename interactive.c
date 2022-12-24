#include "shell.h"
/**
 * interactive - Function handles interactive shell
 * @argv: Pointer to array of args passed to the program
 * @env: Pointer to array containing environment variables
 * Return: Nothing
 */
void interactive(char **argv, char **env)
{
	static char *prog_name;
	char *lineptr, *strcpy;
	int line, same, _env;
	size_t size;

	lineptr = NULL;
	size = 0;
	prog_name = argv[0];
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
			create_child(argv, env, prog_name);
		}
		else if (line == EOF)
			free(lineptr), exit(0);
		else
			continue;
	}
}
