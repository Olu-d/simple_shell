#include "shell.h"
/**
 * non_interactive - Function is called when shell is not interactive.
 * @argv: Pointer to array containing arguments.
 * @env: Pointer to array containing environment variables.
 * Return: Nothing.
 */
int non_interactive(char **argv, char **env)
{
	static char *prog_name;
	char *lineptr, *strcpy;
	int line, same, _env, status;
	size_t size;

	lineptr = NULL;
	size = 0;
	prog_name = argv[0];
	while (1)
	{
		line = getline(&lineptr, &size, stdin);
		if (line == -1)
			free(lineptr), exit(0);
		strcpy = get_commands(lineptr, argv);
		if (argv[0] == NULL)
		{
			free(strcpy);
			free(lineptr);
			exit(0);
		}
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
			free(strcpy);
			free(lineptr), exit(0);
		}
		status = create_child(argv, env, prog_name);
		free(strcpy);
		free(lineptr);
		return (status);
	}
	return (0);
}
